#include "game/application/game.hpp"

const unsigned int GAME_WIDTH = 1920, GAME_HEIGHT = 1080;

GLFWwindow* getGLFWWindow(unsigned int screenWidth, unsigned int screenHeight);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorPosCallback(GLFWwindow* window, double x, double y);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

int main() {
    // TODO: read screen size from a file (remove constants)
    GLFWwindow* window = getGLFWWindow(GAME_WIDTH, GAME_HEIGHT);

    std::shared_ptr<Game> game = Game::GetInstance();
    game->Initialize(window, GAME_WIDTH, GAME_HEIGHT);

    float currentFrame;
    float deltaTime;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window) && game->GetActive()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        game->ProcessInput(deltaTime);
        game->Update(deltaTime);
        game->Render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    Log::Message("Cleaning all resources", LOG_INIT);
    game->CleanUp();
    glfwTerminate();

    return 0;
}

GLFWwindow* getGLFWWindow(unsigned int screenWidth, unsigned int screenHeight) {
    Log::Message("Initializing GLFW", LOG_INIT);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_RESIZABLE, true);
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Cheese thief", nullptr, nullptr);
    if (window == nullptr) {
        Log::Message("Window creation failed", LOG_ERROR);
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Log::Message("Configuring GLFW event callbacks", LOG_INIT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    Log::Message("GLFW initialized", LOG_INIT);

    return window;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    prefix_unused(window);
    Game::GetInstance()->SetRenderSize(width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    prefix_unused(window);
    prefix_unused(scancode);
    prefix_unused(mode);

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            Game::GetInstance()->ProcessKeyboardDown(key, action);
        } else if (action == GLFW_RELEASE) {
            Game::GetInstance()->ProcessKeyboardUp(key, action);
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    prefix_unused(window);
    Game::GetInstance()->ProcessMouseMove(x, y);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    prefix_unused(window);
    prefix_unused(mode);
    Game::GetInstance()->ProcessMouseClick(button, action);
}