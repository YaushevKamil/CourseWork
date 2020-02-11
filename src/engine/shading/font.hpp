#ifndef SHADING_FONT_HPP
#define SHADING_FONT_HPP

#include <map>

#include "texture.hpp"
#include "../math/math.hpp"

namespace Engine {
    struct CharInfo {
        math::vec2 Position;
        math::vec2 Scale;
        math::vec2 Offset;
        float XAdvance;
        math::vec4 RenderInfo[6]; // <vec2 position, vec2 texCoords>
    };

    class Font {
    private:
        std::string name;
        int m_Width, m_Height;
        int m_CharSize;

        Texture* m_FontAtlas;
        std::map<char, CharInfo> m_CharInfo;
    public:
        Font();
        void Load(Texture* fontAtlas, std::map<char, CharInfo> charInfo, int charSize, int width, int height);

        const std::map<char, CharInfo>& GetCharInfo();
        Texture* GetFontAtlas();
        int GetWidth();
        int GetHeight();
        int GetCharSize();
    };
}

#endif //SHADING_FONT_HPP