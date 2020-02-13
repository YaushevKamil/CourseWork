#include "font.hpp"

namespace Engine {
    Font::Font() : m_Width(0), m_Height(0) {}

    Font::Font(Texture *fontAtlas, std::map<char, CharInfo> charInfo, int charSize, int width, int height) {
        Load(fontAtlas, charInfo, charSize, width, height);
    }

    void Font::Load(Texture* fontAtlas, std::map<char, CharInfo> charInfo, int charSize, int width, int height) {
        m_FontAtlas = fontAtlas;
        m_CharInfo = charInfo;
        m_Width = width;
        m_Height = height;
        m_CharSize = charSize;

        // use char info to generate (normalized) quad render data per char
        for (auto pair : m_CharInfo) {
            CharInfo* info = &pair.second;
            // position data
            math::vec2 pos       = math::vec2(info->Offset.x / m_Width,   info->Offset.y / m_Height); // origin: top-left
            math::vec2 w         = math::vec2(info->Scale.x / m_Width,    info->Scale.y / m_Height);
            math::vec2 texCoords = math::vec2(info->Position.x / m_Width, info->Position.y / m_Height);
            // define char render vertices
            info->RenderInfo[0] = math::vec4(pos + math::vec2(0.0, w.y), texCoords + math::vec2(0.0, w.y)); // Bottom left
            info->RenderInfo[1] = math::vec4(pos + math::vec2(w.x, 0.0), texCoords + math::vec2(w.x, 0.0)); // Top right
            info->RenderInfo[2] = math::vec4(pos, texCoords);                                 // Top left

            info->RenderInfo[3] = math::vec4(pos + math::vec2(0.0, w.y), texCoords + math::vec2(0.0, w.y)); // Bottom left
            info->RenderInfo[4] = math::vec4(pos + w, texCoords + w);                                                   // Bottom right
            info->RenderInfo[5] = math::vec4(pos + math::vec2(w.x, 0.0), texCoords + math::vec2(w.x, 0.0)); // Top right
        }
    }

    const std::map<char, CharInfo>& Font::GetCharInfo() {
        return m_CharInfo;
    }

    Texture* Font::GetFontAtlas() {
        return m_FontAtlas;
    }

    int Font::GetWidth() {
        return m_Width;
    }

    int Font::GetHeight() {
        return m_Height;
    }

    int Font::GetCharSize() {
        return m_CharSize;
    }
}