//
// Created by mfleres on 4/6/21.
//

#include "vec3Util.h"

namespace util {
    std::string to_string(const glm::vec3& vec, uint size) {
        std::stringstream retString;
        retString << '(' << std::to_string(vec.x).substr(0, size) << ','
                  << std::to_string(vec.y).substr(0, size) << ','
                  << std::to_string(vec.z).substr(0, size) << ')';
        return retString.str();
    }
    std::string to_string(const glm::vec4& vec, uint size) {
        std::stringstream retString;
        retString << '(' << std::to_string(vec.x).substr(0, size) << ','
                  << std::to_string(vec.y).substr(0, size) << ','
                  << std::to_string(vec.z).substr(0, size) << ','
                  << std::to_string(vec.w).substr(0, size) << ')';
        return retString.str();
    }
}