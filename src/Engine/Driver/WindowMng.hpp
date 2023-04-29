#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

/**
 * @brief Class for Window management with GLFW 
 */
class WindowMng
{
private:
    //! Window ptr manager    
    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> window_ {nullptr, nullptr};

    //! Resolution of the window
    uint32_t width_, heigth_;

public:
    /**
     * @brief Construct a new Window Mng object
     * 
     * @param p_w Width of the window 
     * @param p_h Heigth of the window
     */
    WindowMng(const uint32_t p_w = 1280, const uint32_t p_h = 720) noexcept;
    ~WindowMng() = default;

    /**
     * @brief Static method for the UniquePtr handler of the window for manage the window destruction
     * 
     * @param p_window Pointer to the window to destroy 
     */
    static void deleteWindow( GLFWwindow* p_window )
	{
		glfwDestroyWindow( p_window );
		glfwTerminate();
	}

    /**
     * @brief Get a ref to the Window object
     * 
     * @return GLFWwindow& 
     */
    inline
    GLFWwindow& getWindow()
    {
        return *window_.get();
    }

    /**
     * @brief Get the Width of the window
     * 
     * @return uint32_t 
     */
    inline
    uint32_t getWidth(){ return width_; };

    /**
     * @brief Get the Heigth of the window
     * 
     * @return uint32_t 
     */
    inline
    uint32_t getHeigth(){ return heigth_; };

};

