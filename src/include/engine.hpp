#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "camera.hpp"
#include "input.hpp"
#include "json_config.hpp"
#include "light.hpp"
#include "shader.hpp"
#include "window.hpp"
//#include "world.hpp"

class Engine {
public:
    ~Engine();
    bool init(const char* configName);
    void startGame();
private:
    GLfloat accumulation;
    GLfloat deltaTime;
    GLfloat lastFrame;

    JSONConfig* config;
    Window*     window;
    Input*      input;

    Camera*     m_camera;
    Light*      light;
//    World*      m_world;

    Shader* botShader;
    Shader* planeShader;
    Shader* skyboxShader;
    Shader* terrainShader;

    bool createWindow();
    bool readConfig(const char* configName);
    void setupShader();
    void setupCamera();
    void setupLight();
    void setupInput();
//    void createWorld();
};

#endif // ENGINE_HPP
