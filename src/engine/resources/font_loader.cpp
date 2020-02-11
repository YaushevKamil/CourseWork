#include <fstream>
#include <sstream>

#include "font_loader.hpp"

namespace Engine {
    // TODO: make code readable
    Font FontLoader::LoadFont(std::string name, std::string path) {
        Font font;
        Texture* fontAtlas;
        std::map<char, CharInfo> charInfo;

        std::ifstream file(path);
        std::string line, word;

        // base path
        std::string directory = std::string(path).substr(0, std::string(path).find_last_of('/'));

        // header 1
        std::getline(file, line);
        std::stringstream ss(line);
        ss >> word >> word >> word; // read size=...
        std::string size = word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')));
        int charSize = atoi(size.c_str());

        // header 2
        std::getline(file, line);
        ss.clear();
        ss.str(line);
        ss >> word >> word >> word >> word; // read scaleW=...
        std::string width = word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')));
        int fontWidth = atoi(width.c_str());
        ss >> word;
        width = word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')));
        int fontHeight = atoi(width.c_str());

        // header 3
        std::getline(file, line);
        ss.clear();
        ss.str(line);
        ss >> word >> word >> word; // read file=...
        std::string atlasPath = word.substr(word.find_last_of('=') + 2, (word.size() - word.find_last_of('=') - 3));
        fontAtlas = Resources::LoadTexture(name, (directory + "/" + atlasPath).c_str(), true);

        // header 4
        std::getline(file, line);
        ss.clear();
        ss.str(line);
        ss >> word >> word; // read count=...
        std::string count = word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')));
        int charCount = atoi(count.c_str());

        for (; charCount > 0; --charCount) {
            std::getline(file, line);
            CharInfo chInfo;
            ss.clear();
            ss.str(line);
            // char
            ss >> word >> word; // read id=...
            char id = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // x
            ss >> word; // read x=...
            chInfo.Position.x = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // y
            ss >> word; // read y=...
            chInfo.Position.y = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // width
            ss >> word; // read width=...
            chInfo.Scale.x = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // height
            ss >> word; // read height=...
            chInfo.Scale.y = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // x offset
            ss >> word; // read xoffset=...
            chInfo.Offset.x = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // y offset
            ss >> word; // read yoffset=...
            chInfo.Offset.y = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            // xadvance
            ss >> word; // read xadvance=...
            chInfo.XAdvance = atoi((word.substr(word.find_last_of('=') + 1, (word.size() - word.find_last_of('=')))).c_str());
            charInfo[id] = chInfo;
        }

        font.Load(fontAtlas, charInfo, charSize, fontWidth, fontHeight);

        return font;
    }
}