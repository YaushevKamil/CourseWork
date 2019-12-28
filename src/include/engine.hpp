#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "camera.hpp"
#include "input.hpp"
#include "json_config.hpp"
#include "light.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "world.hpp"

class Engine {
public:
    ~Engine();
    bool init(const char* configName);
    void startGame();
private:
    GLfloat accumulation;
    GLfloat delta_time;
    GLfloat last_frame;

    JSONConfig* m_config;
    Window*     m_window;
    Input*      m_input;

    Camera*     m_camera;
    Light*      m_light;
    World*      m_world;

    Shader* bot_shader;
    Shader* plane_shader;
    Shader* skybox_shader;
    Shader* terrain_shader;

    bool createWindow();
    bool readConfig(const char* configName);
    void setupShader();
    void setupCamera();
    void setupLight();
    void setupInput();
    void createWorld();
};

#endif // ENGINE_HPP
