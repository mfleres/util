//
// Created by mfleres on 9/18/20.
//

#ifndef GRIDWORLD_DIRECTIONS_H
#define GRIDWORLD_DIRECTIONS_H

#include <string>
#include <glm/glm.hpp>
#include <iostream>

#include <cmath>
#ifndef M_SQRT1_2
#define M_SQRT1_2 0.707106781186547524401
#endif

namespace util {
    class Direction {
    public:
        enum Value : uint8_t {
            N = 0,
            NE = 1,
            E = 2,
            SE = 3,
            S = 4,
            SW = 5,
            W = 6,
            NW = 7,
            O = 8 //Represents no direction, the origin.
        };
    private:
        Value value_;

        static double getAngleFromY(const glm::vec2& v) {
            return std::atan2(v.x,v.y);
        }
    public:
        Direction() = default;
        constexpr Direction(Value aDirection) : value_(aDirection) {};
        explicit Direction(glm::vec2 vect);
        explicit Direction(const char* cStr);
        constexpr bool operator==(Direction a) const { return value_ == a.value_; }
        constexpr bool operator!=(Direction a) const { return value_ != a.value_; }

        explicit operator uint8_t() const;
        explicit operator std::string() const;
        explicit operator glm::vec2() const;

        Direction reverse();

        static Direction reverse(Direction direction);
        static Direction cStrToDirection(const char* cStr);
        static std::string to_string(Direction direction);
        static Direction toDirection(const glm::vec2& vect);
        static Direction toOrthogonalDirection(const glm::vec2& vect);
        Direction toRelativeDirection(Direction baseDirection);
        // Returns unit vector in direction. If Direction::O, returns (0,0).
        static glm::vec2 toVect2(Direction direction);
    };
}

#endif //GRIDWORLDSDL_DIRECTIONS_H
