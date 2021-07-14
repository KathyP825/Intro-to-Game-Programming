#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

enum EntityType {PLAYER, PLATFORM, ENEMY};      // 8.7 -- list of entity types
enum AIType { WALKER, WAITANDGO, PATROL, HOPPER };    // 8.7, 8.8 -- list of AI types, what they do
enum AIState { IDLE, WALKING, ATTACKING, RISE, FALL };      // 8.7 -- list of states AI can be in

class Entity {
public:
    EntityType entitytype;
    AIType aiType;
    AIState aiState;

    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;

    float width = 1.0f;
    float height = 1.0f;

    bool jump = false;
    float jumpPower = 0.0f;
    float speed;

    GLuint textureID;
    glm::mat4 modelMatrix;

    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;

    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    bool isActive = true;

    // used for tracking Win/Lose
    bool isAlive = true;
    int numEnemiesKilled = 0;
    int playerWin = -1;  // -1 = default, 0 = lose, 1 = win

    // collision flags
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;

    Entity();

    bool CheckCollision(Entity* other);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);

    void Update(float deltaTime, Entity* player, Entity* platforms, int platformCount, Entity* enemies, int enemyCount);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);
    
    // function prototypes for AI
    void AI(Entity* player);
    void AIWalker();
    void AIWaitAndGo(Entity* player);
    void AIPatrol();
    void AIHopper();
};