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
    platform_grass   = json_tree.get<std::string>("model.platform_grass");
    platform_ice     = json_tree.get<std::string>("model.platform_ice");
    platform_plastic = json_tree.get<std::string>("model.platform_plastic");
    platform_slate   = json_tree.get<std::string>("model.platform_slate");
    platform_spring  = json_tree.get<std::string>("model.platform_spring");
    platform_wood    = json_tree.get<std::string>("model.platform_wood");
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

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            json_tree.get_child("levels")) {
        std::string name = v.second.get<std::string>("name");
        GLuint size = v.second.get<GLuint>("size");
        levels.push_back(LevelData(name, size, size));
        GLuint i = 0;
        BOOST_FOREACH(boost::property_tree::ptree::value_type &table,
                v.second.get_child("table")) {
            GLuint j = 0;
            BOOST_FOREACH(boost::property_tree::ptree::value_type &row,
                    table.second.get_child("")) {
                GLchar ground = row.second.get<std::string>("g")[0];
                GLchar entity = row.second.get<std::string>("e")[0];
                levels.back().add(i, j, ground, entity);
                //std::cout << ground << " " << entity << std::endl;
                j++;
            }
            i++;
        }
        std::cout << "Ground:" << std::endl;
        for (LevelData level : levels) {
            for (GLuint l = 0; l < level.width; l++) {
                for (GLuint j = 0; j < level.height; j++) {
                    std::cout << level.arr[l][j].ground << " ";
                }
                std::cout << std::endl;
            }
        }
        std::cout << "Entity:" << std::endl;
        for (LevelData level : levels) {
            for (GLuint l = 0; l < level.width; l++) {
                for (GLuint j = 0; j < level.height; j++) {
                    std::cout << level.arr[l][j].entity << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    return true;
}

FieldCell::FieldCell() : ground('E'), entity('E') {}
FieldCell::FieldCell(GLchar ground, GLchar entity)
        : ground(ground), entity(entity) {}

LevelData::LevelData() {}
LevelData::LevelData(std::string name, GLuint width, GLuint height) :
        name(name), width(width), height(height) {
    arr = new FieldCell* [width];
    for (GLuint i = 0; i < width; i++) {
        arr[i] = new FieldCell[height];
    }
}

bool LevelData::add(GLuint i, GLuint j, GLchar g, GLchar e) {
    if ((i < 0 || i >= width) || (j < 0 || j > height)) return false;
    arr[i][j] = FieldCell(g, e);
    return true;
}
