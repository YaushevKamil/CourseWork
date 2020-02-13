#ifndef MESH_TEXT_HPP
#define MESH_TEXT_HPP

#include "mesh.hpp"
#include "../shading/font.hpp"

namespace Engine {
    class Text : public Mesh {
    private:
        Font* m_Font;
        std::string text;

        math::vec2 position;
        math::vec2 centerBox;
        float userScale;
    public:
        Text(
                Font* font,
                std::string text,
                math::vec2 position,
                float userScale = 30.0f,
                math::vec2 centerBox = math::vec2(1.0f)
        );
        void ProcessMesh();

        // After all modifications generate a new mesh!
        void SetFont(Font* font);
        void SetText(std::string txt);
        void SetPosition(math::vec2 position);
        void SetScale(float scale);
        void SetCenterBox(math::vec2 centerBoxPos);

        Font* GetFont();
        std::string GetText();
        math::vec2 GetPosition();
        float GetScale();
        math::vec2 GetCenterBox();
    };
}

#endif //MESH_TEXT_HPP