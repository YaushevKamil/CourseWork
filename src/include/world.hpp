#ifndef WORLD_HPP
#define WORLD_HPP

#include <GL/glew.h>
#include <cmath>
#include <filesystem>
#include <random>
#include <vector>

#include "json_config.hpp"
#include "table.hpp"
#include "texture.hpp"

//#include "bot.hpp"
//#include "obstacle.hpp"
#include "skybox.hpp"

class World {
public:
    World(JSONConfig* config,
          Shader *terrain_shader,
          Shader *bot_shader,
          Shader *plane_shader,
          Shader *skybox_shader,
          GLfloat *accumulation);
    ~World();
    void draw();
private:
    GLfloat *accumulation;

    Table* table;

    Skybox* skybox;
//    Obstacle* plane;
//    Obstacle* grass;
//    std::vector<Bot*> bots;
//    std::vector<Obstacle*> obstacles;

    void loadTable(JSONConfig* config);
    void loadSkybox(JSONConfig* config, Shader *shader);
//    void genereateLife(JSONConfig* config,
//                       Shader* plane_shader,
//                       Shader* terrain_shader,
//                       Shader* bot_shader);
//
    void fillGround(JSONConfig* config, Shader* shader);
//    void fillGrass(JSONConfig* config, Shader* shader);
//    void fillObstacle(JSONConfig* config, Shader* shader);
//    void searchModels(std::vector<std::string> *models, std::string path);
//    void fillBot(JSONConfig* config, Shader* shader);

//    void makeMove();
//    void addBot(GLuint colony, GLuint i, GLuint j);
//    void fightBots(Organism* alpha, Organism* beta);
//    void pairBots(Organism* alpha, Organism* beta);
//    bool checkNeighbor(Organism *bot);
//    void checkGrass(Organism *bot);
//    void generateGrass();
//    void toStep();
//    void WarOrLive();
//    void moveBot(FieldCell* from, FieldCell* to, GLuint i, GLuint j);
//    void feed(Organism* bot, FieldCell* curr);
};

#endif // WORLD_HPP
