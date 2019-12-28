#include "include/json_config.hpp"

JSONConfig::JSONConfig(const char* configPath) :
        filePath(std::string(configPath)) {}

bool JSONConfig::readConfig() {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    boost::property_tree::ptree json_tree;

    try {
        file.open(filePath);
        std::stringstream stream;
        stream << file.rdbuf();
        boost::property_tree::read_json(stream, json_tree);
    } catch (const std::ifstream::failure &e) {
        std::cout << "ERROR::CONFIG::FILE_READ_FAILED:"
                  << std::endl << e.what() << std::endl;
        return false;
    }

    // Window
    window_name   = json_tree.get<std::string>("window.windowName");
    screen_width  = json_tree.get<GLuint>("window.screenWidth");
    screen_height = json_tree.get<GLuint>("window.screenHeight");
    window_width  = json_tree.get<GLuint>("window.windowWidth");
    window_height = json_tree.get<GLuint>("window.windowHeight");
    is_resizable  = json_tree.get<bool>("window.isResizable");
    tableSize     = json_tree.get<GLuint>("window.tableSize");
    cellSize      = json_tree.get<GLuint>("window.cellSize");

    // Shaders
    bot_vs     = json_tree.get<std::string>("shader.bot_vs");
    bot_fs     = json_tree.get<std::string>("shader.bot_fs");
    plane_vs   = json_tree.get<std::string>("shader.plane_vs");
    plane_fs   = json_tree.get<std::string>("shader.plane_fs");
    skybox_vs  = json_tree.get<std::string>("shader.skybox_vs");
    skybox_fs  = json_tree.get<std::string>("shader.skybox_fs");
    terrain_vs = json_tree.get<std::string>("shader.terrain_vs");
    terrain_fs = json_tree.get<std::string>("shader.terrain_fs");

    // Skybox textures
    right_side_texture  = json_tree.get<std::string>("skybox.texture.right");
    left_side_texture   = json_tree.get<std::string>("skybox.texture.left");
    top_side_texture    = json_tree.get<std::string>("skybox.texture.top");
    bottom_side_texture = json_tree.get<std::string>("skybox.texture.bottom");
    front_side_texture  = json_tree.get<std::string>("skybox.texture.front");
    back_side_texture   = json_tree.get<std::string>("skybox.texture.back");

    // Models
    bot     = json_tree.get<std::string>("model.bot");
    plane   = json_tree.get<std::string>("model.plane");
    grass   = json_tree.get<std::string>("model.grass");
    stones  = json_tree.get<std::string>("model.stones");
    trees   = json_tree.get<std::string>("model.trees");

    // Light
    light_position = glm::vec3(json_tree.get<GLfloat>("light.position.X"),
                               json_tree.get<GLfloat>("light.position.Y"),
                               json_tree.get<GLfloat>("light.position.Z"));

    light_ambient  = glm::vec4(json_tree.get<GLfloat>("light.ambient.R"),
                               json_tree.get<GLfloat>("light.ambient.G"),
                               json_tree.get<GLfloat>("light.ambient.B"),
                               json_tree.get<GLfloat>("light.ambient.A"));

    light_diffuse  = glm::vec4(json_tree.get<GLfloat>("light.diffuse.R"),
                               json_tree.get<GLfloat>("light.diffuse.G"),
                               json_tree.get<GLfloat>("light.diffuse.B"),
                               json_tree.get<GLfloat>("light.diffuse.A"));

    light_specular = glm::vec4(json_tree.get<GLfloat>("light.specular.R"),
                               json_tree.get<GLfloat>("light.specular.G"),
                               json_tree.get<GLfloat>("light.specular.B"),
                               json_tree.get<GLfloat>("light.specular.A"));
    return true;
}