#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class SurfaceMng
{
private:
    VkInstance& _instance;
    GLFWwindow& _window;

    VkSurfaceKHR _surface;
public:
    SurfaceMng(VkInstance& p_instance, GLFWwindow& p_window);
    ~SurfaceMng();

    inline 
    VkSurfaceKHR& getSurface()
    {
        return _surface;
    }
};

