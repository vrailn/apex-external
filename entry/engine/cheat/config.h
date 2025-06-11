#pragma once
#include <string>
#include <vector>
#include "vars.h"

namespace config {
    bool Save(const std::string& name);
    bool Load(const std::string& name);
    std::vector<std::string> List();
    bool Delete(const std::string& name);
    std::string GetConfigDir();
} 