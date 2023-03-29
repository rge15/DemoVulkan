#include "WindowMng.hpp"

WindowMng::WindowMng(const uint32_t p_w, const uint32_t p_h) noexcept
: width_ { p_w }, heigth_ { p_h }
{
    glfwInit();

    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> window { 
        glfwCreateWindow( width_, heigth_, "HelloVulkan!", nullptr, nullptr),
        deleteWindow };

    assert(window.get());

    window_ = std::move(window);
}

