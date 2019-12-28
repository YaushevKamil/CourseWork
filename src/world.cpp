#include "include/world.hpp"

World::World(JSONConfig* config,
             Shader* terrain_shader,
             Shader* bot_shader,
             Shader* plane_shader,
             Shader* skybox_shader,
             GLfloat *accumulation) :
        accumulation(accumulation) {
//    loadTable(config);
    loadSkybox(config, skybox_shader);
//    genereateLife(config, plane_shader, terrain_shader, bot_shader);
}

World::~World() {
//    delete table;
    delete skybox;
//    delete plane;
//    delete grass;
//    for (Obstacle* obstacle : obstacles) delete obstacle;
//    for (Bot* bot : bots) delete bot;
}

//void World::loadTable(JSONConfig* config) {
//    table = new Table(config->tableSize, config->tableSize);
//}

void World::loadSkybox(JSONConfig* config, Shader *shader) {
    std::string faces[] = {
            config->right_side_texture,
            config->left_side_texture,
            config->top_side_texture,
            config->bottom_side_texture,
            config->front_side_texture,
            config->back_side_texture
    };
    skybox = new Skybox(LoadCubeMapTexture(6, (std::string*)&faces), shader);
}

//void World::genereateLife(JSONConfig* config,
//                          Shader* plane_shader,
//                          Shader* terrain_shader,
//                          Shader* bot_shader) {
//    fillPlane   (config, plane_shader);
//    fillGrass   (config, terrain_shader);
//    fillObstacle(config, terrain_shader);
//    fillObstacle(config, terrain_shader);
//    fillBot     (config, bot_shader);
//}

//void World::fillPlane(JSONConfig* config, Shader* shader) {
//    plane = new Obstacle(config->plane, shader, config->tableSize, config->cellSize);
//    for (GLuint i = 0; i < config->tableSize; i++) {
//        for (GLuint j = 0; j < config->tableSize; j++) {
//            plane->add(i, j, 0);
//        }
//    }
//    plane->loadMatrices();
//}

//void World::fillGrass(JSONConfig* config, Shader* shader) {
//    grass = new Obstacle(config->grass, shader, config->tableSize, config->cellSize);
//    GLfloat grassCount = config->tableSize * config->tableSize >> 2;
//    for (GLuint i = 0; i < grassCount; i++) {
//        Pos pos = table->add(GRASS);
//        grass->add(pos.x, pos.y, pos.angle);
//    }
//    grass->loadMatrices();
//}
//
//void World::fillObstacle(JSONConfig* config, Shader* shader) {
//    std::vector<std::string> models;
//    searchModels(&models, config->stones);
//    searchModels(&models, config->trees);
//
//    GLfloat obstacleCount = ((config->tableSize * config->tableSize >> 2) >> 1) / models.size();
//    for (const std::string model : models) {
//        Obstacle* obstacle = new Obstacle(model, shader, config->tableSize, config->cellSize);
//        for (GLuint i = 0; i < obstacleCount; i++) {
//            Pos pos = table->add(OBSTACLE);
//            obstacle->add(pos.x, pos.y, pos.angle);
//        }
//        obstacle->loadMatrices();
//        obstacles.push_back(obstacle);
//    }
//}
//
//void World::searchModels(std::vector<std::string> *models, std::string path) {
//    for (const auto &entry : std::filesystem::directory_iterator(path)) {
//        std::string str = entry.path();
//        if (str.find(".obj", str.length() - 4) != std::string::npos) {
//            models->push_back(str);
//        }
//    }
//}
//
//void World::fillBot(JSONConfig* config, Shader* shader) {
//    std::mt19937 gen(glfwGetTime());
//    std::uniform_int_distribution<>  gender(0, 1);
//    std::uniform_real_distribution<> amplifier(0.5f, 1.5f);
//
//    GLuint creatureCount = (config->tableSize * config->tableSize >> 2) / COMND_COUNT;
//    for (GLuint colony = 0; colony < COMND_COUNT; colony++) {
//        glm::vec4 color;
//        switch (colony) {
//            case 0 :
//                // RED
//                color = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
//                break;
//            case 1 :
//                // GREEN
//                color = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
//                break;
//            case 2 :
//                // BLUE
//                color = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
//                break;
//            case 3 :
//                // BLACK
//                color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
//                break;
//        }
//
//        Bot* bot = new Bot(config->bot, shader, config->tableSize, config->cellSize);
//        for (GLuint i = 0; i < creatureCount; i++) {
//            Pos pos = table->addBot(colony,
//                                    (GLuint)(LIFETIME   * amplifier(gen)),
//                                    (GLuint)(MAX_ENERGY * amplifier(gen)),
//                                    (GLuint)(STRENGTH   * amplifier(gen)),
//                                    (GLuint)gender(gen));
//            bot->add(color, pos.x, pos.y, pos.angle);
//        }
//        bot->loadMatrices();
//        bots.push_back(bot);
//    }
//}

void World::draw() {
//    plane->draw();
//    grass->draw();
//    for (Obstacle* obstacle : obstacles) { obstacle->draw(); }
//    for (Bot* bot : bots) { bot->draw(); }
    skybox->draw();
//    makeMove();
}

//void World::makeMove() {
//    if (*accumulation >= 0.4f) {
//        toStep();
////         table->print();
////         WarOrLive();
////         generateGrass();
//        for (Bot* bot : bots) bot->loadMatrices();
//
//        *accumulation = 0.0f;
//    }
//}
//
//void World::moveBot(Cell* from, Cell* to, GLuint i, GLuint j) {
//    bots[from->bot->getColony()]->remove(from->bot->X(), from->bot->Y());
//    from->bot->step();
//    from->bot->setCoords(i, j);
//    to->bot = from->bot;
//    to->isBot = true;
//    addBot(to->bot->getColony(), i, j);
//    from->bot = nullptr;
//    from->isBot = false;
//}
//
//void World::addBot(GLuint colony, GLuint i, GLuint j) {
//    bots[colony]->add(i, j, table->table[i][j].angle);
//}
//
//void World::toStep() {
//    std::mt19937 gen(glfwGetTime());
//    std::uniform_int_distribution<> uid(0, 4);
////     std::cout << "First" << std::endl;
//    for (GLuint i = 0; i < table->width; i++) {
//        for (GLuint j = 0; j < table->height; j++) {
////             std::cout << "i: " << i << " j: " << j << std::endl;
//            Cell* curr  = &(table->table[i][j]);
//            if (curr->isBot && curr->bot->getStep()) {
////                 std::cout << "Baha - tarakan, nahoi" << std::endl;
//                curr->bot->mutate();
//                curr->bot->setStep(false);
////                 std::cout << "Pizda" << std::endl;
//                GLuint way = uid(gen);
////                 std::cout << "way: " << way << std::endl;
//                switch (way) {
//                    case 0:
//                        curr->bot->rest();
//                        break;
//                    case 1:
//                        if (i != 0 && table->table[i-1][j].isEmpty()) {
//                            Cell* left = &(table->table[i-1][j]);
//                            moveBot(curr, left, i-1, j);
//                        }
//                        break;
//                    case 2:
//                        if (i != table->width-1 && table->table[i+1][j].isEmpty()) {
//                            Cell* right = &(table->table[i+1][j]);
//                            moveBot(curr, right, i+1, j);
//                        }
//                        break;
//                    case 3:
//                        if (j != 0 && table->table[i][j-1].isEmpty()) {
//                            Cell* down = &(table->table[i][j-1]);
//                            moveBot(curr, down, i, j-1);
////                             std::cout << "Move beatch" << std::endl;
//                        }
//                        break;
//                    case 4:
//                        if (j != table->width-1 && table->table[i][j+1].isEmpty()) {
//                            Cell* up = &(table->table[i][j+1]);
//                            moveBot(curr, up, i, j+1);
//                        }
//                        break;
//                }
//            }
//        }
//    }
////     std::cout << "Second" << std::endl;
//    for (GLuint i = 0; i < table->width; i++) {
//        for (GLuint j = 0; j < table->height; j++) {
//            Cell* curr = &(table->table[i][j]);
//            if (!curr->isBot) continue;
//            curr->bot->setStep(true);
//            curr->bot->setAge(curr->bot->getAge()+1);
//            if (curr->bot->getAge() >= curr->bot->getLifetime()) {
//                bots[curr->bot->getColony()]->remove(i, j);
//                delete curr->bot;
//                curr->isBot = false;
//            }
//        }
//    }
////     std::cout << "Third" << std::endl;
//}
//
//void World::fightBots(Organism* a, Organism* b) {
//    if (a->getColony() != b->getColony() && b->getEnergy() > 0) {
//        while (true) {
//            a->setEnergy(a->getEnergy() - b->getStrength());
//            if (a->getEnergy() <= 0)
//                break;
//            b->setEnergy(b->getEnergy() - a->getStrength());
//            if (b->getEnergy() <= 0)
//                break;
//        }
//    }
//}
//
//void World::pairBots(Organism* a, Organism* b) {
//    std::mt19937 gen(time(0));
//    std::uniform_int_distribution<> uid(2, 3);
//
//    bool x = a->getColony() == b->getColony();
//    bool y = a->getAge() > 2 && b->getAge() > 2;
//    bool z = a->getGender() != b->getGender();
//    GLuint generation = a->getGeneration() > b->getGeneration() ?
//                        a->getGeneration() :
//                        b->getGeneration();
//    generation++;
//
//    if (x && y && z) {
//        for (GLuint i = 0; i < 2; i++) {
//            GLuint colony = a->getColony();
//            if (i == 0) {
//                Cell* curr = &(table->table[a->X()][a->Y()]);
//                curr->isBot = true;
//                curr->bot = new Organism(colony,
//                                         generation,
//                                         a->getLifetime(),                                                                                                         b->getMaxEnergy(),
//                                         a->getInitStrength(),
////                                          a->getColor(),
//                                         0,
//                                         a->X(), a->Y());
//                addBot(curr->bot->getColony(), a->X(), a->Y());
//            } else {
//                Cell* curr = &(table->table[b->X()][b->Y()]);
//                curr->isBot = true;
//                curr->bot = new Organism(colony,
//                                         generation,                                                                                                         a->getLifetime(),
//                                         b->getMaxEnergy(),
//                                         b->getInitStrength(),
//                        /*b->getColor(),*/
//                                         1,
//                                         b->X(), b->Y());
//                addBot(curr->bot->getColony(), a->X(), a->Y());
//            }
//        }
//
//        if (uid(gen) - 2) {
//            GLuint motherX, motherY;
//            if (!a->getGender()) {
//                motherX = a->X();
//                motherY = a->Y();
//            } else {
//                motherX = b->X();
//                motherY = b->Y();
//            }
//
//            GLuint colony = a->getColony();
//            GLuint gender = uid(gen) - 2;
//
//            GLuint lifetime   = a->getLifetime();
//            GLuint max_energy = b->getMaxEnergy();
//            GLuint strength   = a->getInitStrength();
//            if (gender) {
//                lifetime   = b->getLifetime();
//                max_energy = a->getMaxEnergy();
//                strength   = b->getInitStrength();
//            }
//
//            Cell* down  = &(table->table[motherX][motherY-1]);
//            Cell* up    = &(table->table[motherX][motherY+1]);
//            Cell* left  = &(table->table[motherX-1][motherY]);
//            Cell* right = &(table->table[motherX+1][motherY]);
//
//            if (motherY && down->isEmpty()) {
//                down->isBot = true;
//                down->bot = new Organism(colony,
//                                         generation,
//                                         lifetime,                                                                                                              max_energy,
//                                         strength,
////                                          b->getColor(),
//                                         gender,
//                                         motherX, motherY);
//                addBot(down->bot->getColony(), motherX, motherY);
//            } else if (motherY != table->width-1 && up->isEmpty()) {
//                up->isBot = true;
//                up->bot = new Organism(colony,
//                                       generation,
//                                       lifetime,
//                                       max_energy,
//                                       strength,
////                                        b->getColor(),
//                                       gender,
//                                       motherX, motherY);
//                addBot(up->bot->getColony(), motherX, motherY);
//            } else if (motherX && !left->isBot) {
//                left->isBot = true;
//                left->bot = new Organism(colony,
//                                         generation,
//                                         lifetime,
//                                         max_energy,
//                                         strength,
////                                          b->getColor(),
//                                         gender,
//                                         motherX, motherY);
//                addBot(left->bot->getColony(), motherX, motherY);
//            } else if (motherX != table->width-1 && right->isEmpty()) {
//                right->isBot = true;
//                right->bot = new Organism(colony,
//                                          generation,
//                                          lifetime,
//                                          max_energy,
//                                          strength,
////                                           b->getColor(),
//                                          gender,
//                                          motherX, motherY);
//                addBot(right->bot->getColony(), motherX, motherY);
//            }
//        }
//    }
//}
//
//bool World::checkNeighbor(Organism *bot) {
//    GLuint i = bot->X();
//    GLuint j = bot->Y();
//    Cell* curr  = &(table->table[i][j]);
//    Cell* left  = &(table->table[i-1][j]);
//    Cell* right = &(table->table[i+1][j]);
//    Cell* down  = &(table->table[i][j-1]);
//    Cell* up    = &(table->table[i][j+1]);
//    if (bot->getEnergy() > 0) {
//        if (j == 0 && down->isBot) {
//            fightBots(curr->bot, down->bot);
//            pairBots(curr->bot, down->bot);
//        } else if (j != table->width-1 && up->isBot) {
//            fightBots(curr->bot, up->bot);
//            pairBots(curr->bot, up->bot);
//        } else if (i == 0 && left->isBot) {
//            fightBots(curr->bot, left->bot);
//            pairBots(curr->bot, left->bot);
//        } else if (i != table->width-1 && right->isBot) {
//            fightBots(curr->bot, right->bot);
//            pairBots(curr->bot, right->bot);
//        } else return false;
//    }
//    return true;
//}
//
//void World::feed(Organism* bot, Cell* curr) {
//    GLint energy = bot->getEnergy() + bot->getStrength();
//    bot->setEnergy(energy);
//    delete curr->grass;
//    curr->isGrass = false;
//}
//
//void World::checkGrass(Organism* bot) {
//    GLuint i = bot->X();
//    GLuint j = bot->Y();
//
//    Cell* left  = &(table->table[i-1][j]);
//    Cell* right = &(table->table[i+1][j]);
//    Cell* down  = &(table->table[i][j-1]);
//    Cell* up    = &(table->table[i][j+1]);
//
//    if (j == 0 && down->isGrass)
//        feed(bot, down);
//    else if(j != table->width-1 && up->isGrass)
//        feed(bot, up);
//    else if(i && left->isGrass)
//        feed(bot, left);
//    else if(i != table->width-1  && right->isGrass)
//        feed(bot, right);
//}
//
//void World::generateGrass() {
//    std::vector<std::pair<GLuint, GLuint>> empty;
//    for (GLuint i = 0; i < table->width; i++) {
//        for (GLuint j = 0; j < table->width; j++) {
//            Cell* curr = &(table->table[i][j]);
//            if (curr->isEmpty()) empty.emplace_back(i, j);
//        }
//    }
//
//    GLuint grassCount = table->width/12 > empty.size() ?
//                        empty.size() :
//                        table->width/12;
//
//    std::mt19937 gen(glfwGetTime());
//    if (grassCount == table->width / 12) {
//        for (GLuint i = 0; i < grassCount; i++) {
//            std::uniform_int_distribution<>  uid(0, empty.size() - 1);
//            GLuint ind = uid(gen);
//            GLuint x = empty[ind].first;
//            GLuint y = empty[ind].second;
//            Cell* curr = &(table->table[x][y]);
//            curr->isGrass = true;
//            curr->grass = new Grass(x, y);
//            empty.erase(empty.begin() + ind);
//        }
//    } else {
//        for (GLuint i = 0; i < grassCount; i++) {
//            GLuint x = empty[i].first;
//            GLuint y = empty[i].second;
//            Cell* curr = &(table->table[x][y]);
//            curr->isGrass = true;
//            curr->grass = new Grass(x, y);
//        }
//    }
//}
//void World::WarOrLive() {
//    int hungry;
//    for (GLuint i = 0; i < table->width; i++) {
//        for (GLuint j = 0; j < table->height; j++) {
//            Cell* curr = &(table->table[i][j]);
//            if (curr->isBot) {
//                hungry = curr->bot->getMaxEnergy() / 3;
//                if (curr->bot->getEnergy() > hungry && checkNeighbor(curr->bot)) {
//                    if (curr->bot->getEnergy() <= 0) {
//                        bots[curr->bot->getColony()]->remove(i, j);
//                        delete curr->bot;
//                        curr->isBot = false;
//                    }
//                } else checkGrass(curr->bot);
//            }
//        }
//    }
//}
