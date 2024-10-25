#include "utils_services.h"

#include "core/log.h"

void UtilsServices::onMessage(const Connection& connection, const std::string& message) {
    log("UtilsServices from : " << (Connection*)&connection << " : " << message);
}