#include "SurfaceMng.hpp"


SurfaceMng::SurfaceMng(VkInstance& p_instance, GLFWwindow& p_window)
: _instance { p_instance }, _window { p_window }
{
    glfwCreateWindowSurface( _instance, &_window, nullptr, &_surface );
}

SurfaceMng::~SurfaceMng()
{
    vkDestroySurfaceKHR( _instance, _surface, nullptr);
}
