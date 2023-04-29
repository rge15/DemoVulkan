#include <App/BaseApplication.hpp>

/**
 * @brief InitDemoApp which loads and executes the Time demo
 */
class InitDemoApp : BaseApplication
{
public:
    InitDemoApp(/* args */) = default;
    ~InitDemoApp() = default;

    virtual void run() override;
};