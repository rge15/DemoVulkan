#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class WindowMng
{
private:
    
    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> window_ {nullptr, nullptr};

    uint32_t width_, heigth_;

public:
    WindowMng(const uint32_t p_w = 1280, const uint32_t p_h = 720) noexcept;
    ~WindowMng() = default;

    static void deleteWindow( GLFWwindow* p_window )
	{
		glfwDestroyWindow( p_window );
		glfwTerminate();
	}

    inline
    GLFWwindow& getWindow()
    {
        return *window_.get();
    }

    inline
    uint32_t getWidth(){ return width_; };

    inline
    uint32_t getHeigth(){ return heigth_; };

};

