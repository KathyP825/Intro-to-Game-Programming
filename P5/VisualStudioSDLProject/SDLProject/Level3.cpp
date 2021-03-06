#include "Level3.h"
#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 2

unsigned int level3_data[] = {
    101,  36,  36,  36,  36,  36,  36,  36,  36,  36,  16,  68,  16,  99,
    101,   0,   0,   0,   0,   0,   0,   0,   0,   0,  48,  68,  32,  99,
    101,   0,   0,   0,   0,   0,   0,   0,  35,  36,  36,  68,  32,  99,
    101,   0,   0,   0,   0,   0,   0,  40,   0,   0,   0,  68,  32,  99,
    101,   0,   0,  20,   0,   0,  35,  37,   0,   0,   0,  68,  32,  99,
    101,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 133,  32,  99,
    100,  85,   0,   0,   0,   0,   0,   0,   0,  52,   0,   0,  48,  99,
    100, 100,  84,  84,  84,  84,  84,  84,  84,  84,  84,  84,  84, 100
};


void Level3::Initialize() {
    state.nextScene = -1;
    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);

    GLuint mapTextureID = Util::LoadTexture("pixel_platform_01_tileset_final.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 16, 10);


    /*
    -----------------   Initialize Player    -----------------
    */
    state.player = new Entity();
    state.player->entitytype = PLAYER;
    state.player->position = glm::vec3(2.0f, -5.0f, 0.0f);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.5f;
    state.player->textureID = Util::LoadTexture("characters.png");

    state.player->animRight = new int[2]{ 4, 5 };
    state.player->animLeft = new int[2]{ 4, 5 };
    state.player->animUp = new int[2]{ 4, 5 };
    state.player->animDown = new int[2]{ 4, 5 };

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 2;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 9;
    state.player->animRows = 3;

    state.player->height = 0.9f;
    state.player->width = 0.8f;

    state.player->jumpPower = 6.0f;


    /*
    -----------------   Initialize Enemies    -----------------
    */
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("characters.png");

    for (size_t i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].entitytype = ENEMY;
        state.enemies[i].textureID = enemyTextureID;

        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        state.enemies[i].speed = 1.0f;

        state.enemies[i].animRight = new int[2]{ 9, 10 };
        state.enemies[i].animLeft = new int[2]{ 9, 10 };
        state.enemies[i].animUp = new int[2]{ 9, 10 };
        state.enemies[i].animDown = new int[2]{ 9, 10 };

        state.enemies[i].animIndices = state.enemies[0].animRight;
        state.enemies[i].animFrames = 2;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animCols = 9;
        state.enemies[i].animRows = 3;

        state.enemies[i].height = 0.8f;
        state.enemies[i].width = 0.8f;

        state.enemies[i].aiType = WAITANDGO;
        state.enemies[i].aiState = IDLE;
    }

    state.enemies[0].position = glm::vec3(5.0f, -7.0f, 0.0f);
    state.enemies[1].position = glm::vec3(8.0f, -1.0f, 0.0f);
}


void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);

    for (size_t i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    }

    // if win, switch to Win screen
    if (state.player->position.x >= 11.0f && state.player->position.y <= -6.0f) {
        state.nextScene = 4;
    }
}


void Level3::Render(ShaderProgram* program) {
    GLuint fontTextureID = Util::LoadTexture("pixel_font.png");

    state.map->Render(program);

    for (size_t i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    state.player->Render(program);
}