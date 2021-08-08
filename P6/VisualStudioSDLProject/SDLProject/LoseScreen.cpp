#include "LoseScreen.h"

void LoseScreen::Initialize() {
    state.nextScene = -1;

    /*
    -----------------   Initialize Player  -----------------
    */
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(0, 0.75f, 0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 3.0f;
    //state.player->isActive = false;
}

void LoseScreen::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.objects, 0, state.enemies, 0);
}

void LoseScreen::Render(ShaderProgram* program) {}