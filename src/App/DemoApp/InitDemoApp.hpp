#include <App/BaseApplication.hpp>

class InitDemoApp : BaseApplication
{
public:
    InitDemoApp(/* args */) = default;
    ~InitDemoApp() = default;

    virtual void run() override;
};