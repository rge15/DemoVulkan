#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

/**
 * @brief Class for presentation Surface management. (KHR extension)
 */
class SurfaceMng
{
private:
    //! Reference to the Vulkan Instance Handler
    VkInstance& instance_;
    //! Reference to the Window to present in
    GLFWwindow& window_;

    //! Vulkan (KHR extension) surface handler
    VkSurfaceKHR surface_;
public:
    /**
     * @brief Construct a new Surface Mng object and create a SUrface Handler obj based on the window to present on
     * 
     * @param p_instance Vulkan Instance for Surface creation
     * @param p_window Window to get the presentation surface
     */
    SurfaceMng(VkInstance& p_instance, GLFWwindow& p_window);
    /**
     * @brief Destroy the Surface Mng object and the Vulkan Surface
     */
    ~SurfaceMng();

    /**
     * @brief Get the Surface object
     * 
     * @return VkSurfaceKHR& 
     */
    inline 
    VkSurfaceKHR& getSurface()
    {
        return surface_;
    }
};

