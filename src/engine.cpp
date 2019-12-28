#include "include/engine.hpp"
#include "include/input.hpp"

bool Engine::init(const char* configName) {
    bool err1 = readConfig(configName);
    bool err2 = createWindow();
    setupShader();
    setupCamera();
    setupLight();
    setupInput();
    createWorld();

    return err1 && err2;
}

bool Engine::readConfig(const char* configName) {
    config = new JSONConfig(configName);
    bool err = !config->readConfig();
    if (err) {
        std::cout << "ERROR::CONFIG_READ_FAILED" << std::endl;
        delete config;
    }
    return !err;
}

bool Engine::createWindow() {
    window = new Window(config);
    bool err = !window->init();
    if (err) {
        std::cout << "ERROR::WINDOW_INITIALIZATION_FAILED" << std::endl;
        delete window;
    }

    return !err;
}

void Engine::setupShader() {
    botShader     = new Shader(config->bot_vs, config->bot_fs);
    planeShader   = new Shader(config->plane_vs, config->plane_fs);
    skyboxShader  = new Shader(config->skybox_vs, config->skybox_fs);
    terrainShader = new Shader(config->terrain_vs, config->terrain_fs);
}

void Engine::setupCamera() {
    camera = new Camera(config->window_width,
                          config->window_height,
                          glm::vec3(0.0f, 3.0f, 6.0f),
                          terrainShader,
                          botShader,
                          planeShader,
                          skyboxShader);
}

void Engine::setupLight() {
    light = new Light(config->light_position,
                      config->light_ambient,
                      config->light_diffuse,
                      config->light_specular,
                      terrainShader,
                      planeShader,
                      botShader);
}

void Engine::setupInput() {
    input = new Input(window->window, camera);
}

void Engine::createWorld() {
    world = new World(config,
                        terrainShader,
                        botShader,
                        planeShader,
                        skyboxShader,
                        &accumulation);
}

void Engine::startGame() {
    while (!glfwWindowShouldClose(window->window)) {
        GLfloat current_frame = glfwGetTime();
        deltaTime = current_frame - lastFrame;
        lastFrame = current_frame;
        accumulation += deltaTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input->processInput(&deltaTime);
        camera->updateViewProjMatrix();
        world->draw();

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }
}

Engine::~Engine() {
    delete config;
    delete window;
    delete input;
    delete camera;
//    delete light;
//    delete world;
    delete botShader;
    delete planeShader;
    delete skyboxShader;
    delete terrainShader;
}