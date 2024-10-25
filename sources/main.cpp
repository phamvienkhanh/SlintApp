
#include "main.h"

#include "services/services_manager.h"
#include "services/utils_services.h"

int main(int argc, char const* argv[]) {
    ServicesManager sm;
    sm.run<UtilsServices>("/tmp/test.sock");

    auto app = UI::MainWindow::create();
    app->run();

    return 0;
}
