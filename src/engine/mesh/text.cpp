#include "text.hpp"

namespace Engine {
    Text::Text(Font* font, std::string text, math::vec2 position, float userScale, math::vec2 centerBox) :
            m_Font(font), text(text), position(position), userScale(userScale), centerBox(centerBox) {
        ProcessMesh();
    }

    void Text::ProcessMesh() {
        Clear();

        float cursor = 0.0f;
        float scale = userScale * m_Font->GetCharSize();
        float centerXPadding = 0.0f;
        float centerYPadding = 0.0f;
        if (centerBox.x != 1.0f && centerBox.y != 1.0f) {
            float textWidth = 0.0f;
            for (int i = 0; i < text.size(); i++) {
                textWidth += (m_Font->GetCharInfo().at(text[i]).XAdvance / m_Font->GetWidth()) * scale;
            }
            centerXPadding = (centerBox.x - textWidth) / 2.0f;
            centerYPadding = (centerBox.y - (m_Font->GetCharInfo().at(text[0]).Scale.y / m_Font->GetWidth() * scale)) / 2.0f;
        }
        for (char ch : text) {
            CharInfo charInfo = m_Font->GetCharInfo().at(ch);
            for (int i = 0; i < 6; ++i) {
                Positions.push_back({
                                            position.x + centerXPadding + charInfo.RenderInfo[i].x * scale + cursor,
                                            position.y + centerYPadding + charInfo.RenderInfo[i].y * scale,
                                            0.0f
                                    });
                UV.push_back({
                                     charInfo.RenderInfo[i].z,
                                     charInfo.RenderInfo[i].w
                             });
            }
            cursor += (charInfo.XAdvance / m_Font->GetWidth()) * scale;
        }

        Topology = TRIANGLES;
        Finalize();
    }

    void Text::SetFont(Font* font) {
        m_Font = font;
    }

    void Text::SetText(std::string txt) {
        text = txt;
    }

    void Text::SetPosition(math::vec2 pos) {
        position = pos;
    }

    void Text::SetScale(float scale) {
        userScale = scale;
    }

    void Text::SetCenterBox(math::vec2 centerBoxPos) {
        centerBox = centerBoxPos;
    }

    Font *Text::GetFont() {
        return m_Font;
    }

    std::string Text::GetText() {
        return text;
    }

    math::vec2 Text::GetPosition() {
        return position;
    }

    float Text::GetScale() {
        return userScale;
    }

    math::vec2 Text::GetCenterBox() {
        return centerBox;
    }
}