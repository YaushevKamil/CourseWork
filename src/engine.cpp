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
    m_config = new JSONConfig(configName);
    bool err = !m_config->readConfig();
    if (err) {
        std::cout << "ERROR::CONFIG_READ_FALIED" << std::endl;
        delete m_config;
    }
    return !err;
}

bool Engine::createWindow() {
    m_window = new Window(m_config);
    bool err = !m_window->init();
    if (err) {
        std::cout << "ERROR::WINDOW_INITIALIZATION_FALIED" << std::endl;
        delete m_window;
    }

    return !err;
}

void Engine::setupShader() {
    bot_shader     = new Shader(m_config->bot_vs,     m_config->bot_fs);
    plane_shader   = new Shader(m_config->plane_vs,   m_config->plane_fs);
    skybox_shader  = new Shader(m_config->skybox_vs,  m_config->skybox_fs);
    terrain_shader = new Shader(m_config->terrain_vs, m_config->terrain_fs);
}

void Engine::setupCamera() {
    m_camera = new Camera(m_config->window_width,
                          m_config->window_height,
                          glm::vec3(0.0f, 3.0f, 6.0f),
                          terrain_shader,
                          bot_shader,
                          plane_shader,
                          skybox_shader);
}

void Engine::setupLight() {
    m_light = new Light(m_config->light_position,
                        m_config->light_ambient,
                        m_config->light_diffuse,
                        m_config->light_specular,
                        terrain_shader,
                        plane_shader,
                        bot_shader);
}

void Engine::setupInput() {
    m_input = new Input(m_window->window, m_camera);
}

void Engine::createWorld() {
//    m_world = new World(m_config,
//                        terrain_shader,
//                        bot_shader,
//                        plane_shader,
//                        skybox_shader,
//                        &accumulation);
}

void Engine::startGame() {
    while (!glfwWindowShouldClose(m_window->window)) {
        GLfloat current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        accumulation += delta_time;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_input->processInput(&delta_time);
        m_camera->updateViewProjMatrix();
        m_world->draw();

        glfwSwapBuffers(m_window->window);
        glfwPollEvents();
    }
}

Engine::~Engine() {
    delete m_config;
    delete m_window;
    delete m_input;
    delete m_camera;
    delete m_light;
    delete m_world;
    delete bot_shader;
    delete plane_shader;
    delete skybox_shader;
    delete terrain_shader;
}