#include <iostream>
#include <string>

#include "core/log/log.h"
#include "runtime/application/application.h"

using namespace Shadow;

class Sandbox : public Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

int main() {
    Log::Init();
    auto app = new Sandbox();
    app->Init();
    app->Run();
}
