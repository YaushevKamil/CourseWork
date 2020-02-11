#ifndef RESOURCES_FONT_LOADER_HPP
#define RESOURCES_FONT_LOADER_HPP

#include "resources.hpp"
#include "../shading/font.hpp"

namespace Engine {
    class FontLoader {
    public:
        static Font LoadFont(std::string name, std::string path);
    private:
        //TODO: split the LoadFont() into separate parts:
        //static void parseDimensions(...);
        //static Material* parseMaterial(...);
        //static std::string processPath(std::string* path, std::string directory);
    };
}

#endif //RESOURCES_FONT_LOADER_HPP