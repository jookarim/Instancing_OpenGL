cmake_minimum_required(VERSION 3.26)

project(Instancing_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- Dependencies ----------------
# GLFW
find_package(glfw3 CONFIG REQUIRED)

# GLEW
find_package(GLEW CONFIG REQUIRED)

# OpenGL (portable across OS)
find_package(OpenGL REQUIRED)

# ---------------- ImGui ----------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external
    external/imgui
    external/imgui/backends
)

# ImGui needs GLFW + OpenGL
target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# ---------------- Game ----------------
add_executable(Instancing_OpenGL
    src/main.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Transform.cpp
    src/stb_image.cpp
    src/AssetManager.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/Renderer.cpp
)

target_include_directories(Instancing_OpenGL PRIVATE
    include
)

target_link_libraries(Instancing_OpenGL PRIVATE
    imgui
    glfw
    GLEW::GLEW
    OpenGL::GL
)

# ---------------- Assets ----------------
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Instancing_OpenGL>/assets
)
add_dependencies(Instancing_OpenGL copy_assets)