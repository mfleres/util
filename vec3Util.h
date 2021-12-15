//
// Created by mfleres on 3/28/21.
//

#pragma once
#ifndef GRIDWORLD3D_VEC3UTIL_H
#define GRIDWORLD3D_VEC3UTIL_H

#include <glm/glm.hpp>
#include <string>
#include <sstream>

namespace util {
    extern std::string to_string(const glm::vec3& vec, uint size = 5);
    extern std::string to_string(const glm::vec4& vec, uint size = 5);
}

#endif //GRIDWORLD3D_VEC3UTIL_H