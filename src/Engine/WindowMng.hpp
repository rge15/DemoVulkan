#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class WindowMng
{
private:
    
    UniqPtr<GLFWwindow, void (*)(GLFWwindow*)> _window {nullptr, nullptr};

    uint32_t _width, _heigth;

public:
    WindowMng(const uint32_t p_w = 640, const uint32_t p_h = 480) noexcept;
    ~WindowMng() = default;

    static void deleteWindow( GLFWwindow* p_window )
	{
		glfwDestroyWindow( p_window );
		glfwTerminate();
	}

    inline
    GLFWwindow& getWindow()
    {
        return *_window.get();
    }

    inline
    uint32_t getWidth(){ return _width; };

    inline
    uint32_t getHeigth(){ return _heigth; };

};

