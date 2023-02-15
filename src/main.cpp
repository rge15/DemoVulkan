#include <utilities/typeAliases.hpp>
#include <App/DemoApp/InitDemoApp.hpp>
#include <utilities/Timer/Timer.hpp>

int main()
{
    Timer::getInstance();

    InitDemoApp app {};

    app.run();
}