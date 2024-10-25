#ifndef _CORE_SERVICES_SERVICES_MANAGER_H_
#define _CORE_SERVICES_SERVICES_MANAGER_H_

#include <thread>

class ServicesManager {
  public:
    ServicesManager() = default;

    template <typename T>
    void run(const std::string& sockpath) {
        std::thread t([sockpath]() {
            T s;
            s.setSockPath(sockpath);
            s.run();
        });
        t.detach();
    }
};

#endif