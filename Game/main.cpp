#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: main <json_config_path>" << std::endl;
        return -1;
    }
    char* configPath = argv[1];

    Engine engine;
    if (!engine.init(configPath)) {
        std::cout << "ERROR::ENGINE_INITIALIZATION_FALIED" << std::endl;
        return -1;
    }
    engine.startGame();
    
    return 0;
}
