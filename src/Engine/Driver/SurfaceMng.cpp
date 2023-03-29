#include "SurfaceMng.hpp"


SurfaceMng::SurfaceMng(VkInstance& p_instance, GLFWwindow& p_window)
: instance_ { p_instance }, window_ { p_window }
{
    glfwCreateWindowSurface( instance_, &window_, nullptr, &surface_ );
}

SurfaceMng::~SurfaceMng()
{
    vkDestroySurfaceKHR( instance_, surface_, nullptr);
}
