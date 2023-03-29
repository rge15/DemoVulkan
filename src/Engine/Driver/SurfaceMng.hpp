#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class SurfaceMng
{
private:
    VkInstance& instance_;
    GLFWwindow& window_;

    VkSurfaceKHR surface_;
public:
    SurfaceMng(VkInstance& p_instance, GLFWwindow& p_window);
    ~SurfaceMng();

    inline 
    VkSurfaceKHR& getSurface()
    {
        return surface_;
    }
};

