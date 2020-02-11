cmake_minimum_required(VERSION 3.15)
project(CourseWork)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
set(OpenGlLinkers -lGL -lglfw -lGLU -lGLEW -lSOIL -lassimp -fopenmp)

add_executable(
        CourseWork
        src/main.cpp

        src/game/application/game.hpp
        src/game/application/game.cpp

        src/engine/utility/logging/log.cpp
        src/engine/utility/logging/log.hpp

        src/engine/engine.cpp
        src/engine/engine.hpp
        src/engine/camera/camera.hpp
        src/engine/camera/camera.cpp
        src/engine/camera/camera_frustum.hpp
        src/engine/camera/camera_frustum.cpp
        src/engine/camera/fly_camera.hpp
        src/engine/camera/fly_camera.cpp

        src/engine/math/common.hpp
        src/engine/math/conversions.hpp
        src/engine/math/math.hpp
        src/engine/math/linear_algebra/vector.hpp
        src/engine/math/linear_algebra/matrix.hpp
        src/engine/math/linear_algebra/operation.hpp
        src/engine/math/linear_algebra/quaternion.hpp
        src/engine/math/linear_algebra/transformation.hpp

        src/engine/utility/string_id.hpp

        src/engine/lighting/point_light.hpp
        src/engine/lighting/directional_light.hpp

        src/engine/shading/texture.hpp
        src/engine/shading/texture.cpp
        src/engine/shading/material.hpp
        src/engine/shading/shading_types.hpp
        src/engine/shading/shader.hpp
        src/engine/shading/shader.cpp
        src/engine/shading/texture_cube.hpp
        src/engine/shading/texture_cube.cpp
        src/engine/shading/material.cpp

        src/engine/glad/glad.h
        src/engine/glad/glad.c
        src/engine/glad/khrplatform.h

        src/engine/resources/resources.hpp

        src/engine/mesh/circle.hpp
        src/engine/mesh/mesh.hpp
        src/engine/mesh/mesh.cpp
        src/engine/mesh/circle.cpp
        src/engine/mesh/cube.hpp
        src/engine/mesh/cube.cpp
        src/engine/mesh/line_strip.hpp
        src/engine/mesh/line_strip.cpp
        src/engine/mesh/plane.hpp
        src/engine/mesh/plane.cpp
        src/engine/mesh/quad.hpp
        src/engine/mesh/quad.cpp
        src/engine/mesh/sphere.hpp
        src/engine/mesh/sphere.cpp
        src/engine/mesh/torus.hpp
        src/engine/mesh/torus.cpp

        src/engine/resources/resources.cpp
        src/engine/scene/scene.hpp
        src/engine/scene/scene.cpp
        src/engine/scene/scene_node.hpp
        src/engine/scene/scene_node.cpp
        src/engine/scene/background.hpp
        src/engine/scene/background.cpp
        src/engine/renderer/renderer.hpp
        src/engine/renderer/command_buffer.hpp
        src/engine/renderer/render_command.hpp
        src/engine/renderer/command_buffer.cpp
        src/engine/renderer/material_library.hpp
        src/engine/renderer/material_library.cpp
        src/engine/renderer/pbr.hpp
        src/engine/renderer/pbr.cpp
        src/engine/renderer/pbr_capture.hpp
        src/engine/renderer/pbr_capture.cpp
        src/engine/renderer/gl_cache.hpp
        src/engine/renderer/gl_cache.cpp
        src/engine/renderer/post_processor.hpp
        src/engine/renderer/post_processor.cpp
        src/engine/renderer/render_target.hpp
        src/engine/renderer/render_target.cpp
        src/engine/renderer/renderer.cpp
        src/engine/imgui/imconfig.h
        src/engine/imgui/imgui.h
        src/engine/imgui/imgui.cpp
        src/engine/imgui/stb_truetype.h
        src/engine/imgui/stb_textedit.h
        src/engine/imgui/stb_rect_pack.h
        src/engine/imgui/imgui_internal.h
        src/engine/imgui/imgui_draw.cpp
        src/engine/imgui/imgui_demo.cpp
        src/engine/resources/shader_loader.hpp
        src/engine/resources/shader_loader.cpp
        src/engine/resources/texture_loader.hpp
        src/engine/resources/texture_loader.cpp
        src/engine/stb/stb_image.h
        src/engine/stb/stb_image.cpp
        src/engine/resources/mesh_loader.hpp
        src/engine/resources/mesh_loader.cpp
        src/game/game_object.hpp
        src/game/game_object.cpp
        src/game/gui/gui.hpp
        src/game/gui/button.hpp
        src/game/gui/main_menu.hpp
        src/game/gui/main_menu.cpp
        src/game/application/game_state.hpp
#        src/game/components/actor.hpp
#        src/game/components/actor_component_definitions.hpp
#        src/game/components/actor_factory.hpp
#        src/game/components/actor_factory.cpp
#        src/game/components/actor_component.hpp
#        src/game/components/actor.cpp
        src/game/communication/FastDelegate.h
        src/game/communication/IEventData.h
        src/game/communication/EventManager.h
        src/game/communication/EventManager.cpp
        src/game/application/event_startLevel.hpp
        src/game/application/event_startLevel.cpp
        src/game/application/event_quitGame.hpp
        src/game/application/event_quitGame.cpp
        src/game/gui/container.hpp
        src/game/gui/element.hpp
        src/game/gui/button.cpp
        src/game/gui/element.cpp
        src/game/gui/container.cpp
        src/game/gui/game_menu.hpp
        src/game/gui/game_menu.cpp
        src/engine/renderer/text_renderer.hpp
        src/engine/resources/font_loader.hpp
        src/engine/resources/font_loader.cpp
        src/engine/shading/font.hpp
        src/engine/shading/font.cpp)

target_link_libraries(CourseWork ${OpenGlLinkers})