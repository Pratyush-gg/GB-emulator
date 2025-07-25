#pragma once

#include <iostream>
#include <cstdint>

void not_implemented(const char* function_name) {
    std::cerr << "Function not implemented: " << function_name << std::endl;
    // std::exit(EXIT_FAILURE);
}