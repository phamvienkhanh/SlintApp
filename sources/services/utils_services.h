#ifndef _CORE_UTILS_SERVICES_H_
#define _CORE_UTILS_SERVICES_H_

#include "core/base_services.h"

class UtilsServices : public BaseServices {
  public:
    UtilsServices() = default;

    void onMessage(const Connection& connection, const std::string& message) override;
};

#endif