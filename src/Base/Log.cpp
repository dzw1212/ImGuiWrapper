#include "Log.h"

std::once_flag Log::logInitFlag;
std::shared_ptr<spdlog::logger> Log::consoleLogger = nullptr;
