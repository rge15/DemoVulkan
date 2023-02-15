#include "WindowMng.hpp"

WindowMng::WindowMng(const uint32_t p_w, const uint32_t p_h) noexcept
: _width { p_w }, _heigth { p_h }
{
    glfwInit();

    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> window { 
        glfwCreateWindow( _width, _heigth, "HelloVulkan!", nullptr, nullptr),
        deleteWindow };

    assert(window.get());

    _window = std::move(window);
}

