#ifndef JSON_CONFIG_HPP
#define JSON_CONFIG_HPP

#include <GL/glew.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <cinttypes>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

struct JSONConfig {
    JSONConfig(const char* configName);
    bool readConfig();

    std::string filePath;

    // Window
    std::string window_name;
    GLuint screen_width;
    GLuint screen_height;
    GLuint window_width;
    GLuint window_height;
    bool is_resizable;
    GLuint tableSize;
    GLuint cellSize;

    // Shaders
    std::string bot_vs;
    std::string bot_fs;
    std::string plane_vs;
    std::string plane_fs;
    std::string skybox_vs;
    std::string skybox_fs;
    std::string terrain_vs;
    std::string terrain_fs;

    // Skybox textures
    std::string right_side_texture;
    std::string left_side_texture;
    std::string top_side_texture;
    std::string bottom_side_texture;
    std::string front_side_texture;
    std::string back_side_texture;

    // Models
    std::string bot;
    std::string plane;
    std::string grass;
    std::string stones;
    std::string trees;

    // Light
    glm::vec3 light_position;
    glm::vec4 light_ambient;
    glm::vec4 light_diffuse;
    glm::vec4 light_specular;
};

#endif  // JSON_CONFIG_HPP