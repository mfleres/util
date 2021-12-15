//
// Created by mfleres on 8/30/21.
//

#include "Directions.h"

namespace util {
    Direction::Direction(glm::vec2 vect) {
        const long double M_PI_8 = M_PI_4 * 0.5;
        const long double M_PI_16 = M_PI_4 * 0.25;
        if (vect.x == 0.0f && vect.y == 0.0f)
            value_ = Value::O;
        else {
            double radians = getAngleFromY(vect);
            if (std::abs(radians) < M_PI_8)
                value_ = Value::N;
            else if (std::abs(radians) > M_PI - M_PI_8)
                value_ = Value::S;
            else if (std::abs(radians) <= M_PI_2 - M_PI_8) {
                if (radians > 0)
                    value_ = Value::NE;
                else
                    value_ = Value::NW;
            } else if (std::abs(radians) < M_PI_2 + M_PI_8) {
                if (radians > 0)
                    value_ = Value::E;
                else
                    value_ = Value::W;
            } else {
                if (radians > 0)
                    value_ = Value::SE;
                else
                    value_ = Value::SW;
            }
        }
    }
    Direction::Direction(const char* cStr) {
        if (!cStr || cStr[0] == '\0')
            value_ = Value::O;
        else {
            bool diag = cStr[1] != '\0';
            switch (cStr[0]) {
                case 'N':
                    if (diag) {
                        if (cStr[1] == 'W')
                            value_ = Value::NW;
                        else if (cStr[1] == 'E')
                            value_ = Value::NE;
                        else
                            value_ = Value::N;
                        break;
                    }
                    value_ = Value::N;
                    break;
                case 'S':
                    if (diag) {
                        if (cStr[1] == 'W')
                            value_ = Value::SW;
                        else if (cStr[1] == 'E')
                            value_ = Value::SE;
                        else
                            value_ = Value::S;
                        break;
                    }
                    value_ = Value::S;
                    break;
                case 'E':
                    value_ = Value::E;
                    break;
                case 'W':
                    value_ = Value::W;
                    break;
                default:
                    value_ = Value::O;
            }
        }
    }

    Direction::operator uint8_t() const { return value_; }
    Direction::operator std::string() const {
        switch (value_) {
            case Direction::N:
                return "N";
            case Direction::S:
                return "S";
            case Direction::E:
                return "E";
            case Direction::W:
                return "W";
            case Direction::NE:
                return "NE";
            case Direction::NW:
                return "NW";
            case Direction::SE:
                return "SE";
            case Direction::SW:
                return  "SW";
            default:
                return "O";
        }
    }
    Direction::operator glm::vec2() const {
        switch (value_) {
            case Direction::N:
                return { 0.0f, 1.0f };
            case Direction::S:
                return { 0.0f, -1.0f };
            case Direction::E:
                return { 1.0f, 0.0f };
            case Direction::W:
                return { -1.0f, 0.0f };
            case Direction::NE:
                return { M_SQRT1_2, M_SQRT1_2 };
            case Direction::NW:
                return { -M_SQRT1_2, M_SQRT1_2 };
            case Direction::SE:
                return { M_SQRT1_2, -M_SQRT1_2 };
            case Direction::SW:
                return  { -M_SQRT1_2, -M_SQRT1_2 };
            default:
                return { 0.0f, 0.0f };
        }
    }

    Direction Direction::reverse() {
        switch (value_) {
            case Direction::N:
                return Direction::S;
            case Direction::S:
                return Direction::N;
            case Direction::E:
                return Direction::W;
            case Direction::W:
                return Direction::E;
            case Direction::NE:
                return Direction::SW;
            case Direction::NW:
                return Direction::SE;
            case Direction::SE:
                return Direction::NW;
            case Direction::SW:
                return  Direction::NE;
            default:
                return Direction::O;
        }
    }

    Direction Direction::reverse(Direction direction) { return direction.reverse();}
    Direction Direction::cStrToDirection(const char* cStr) { return Direction(cStr); }
    std::string Direction::to_string(Direction direction) { return static_cast<std::string>(direction); }
    Direction Direction::toDirection(const glm::vec2& vect) { return Direction(vect); }

    Direction Direction::toOrthogonalDirection(const glm::vec2& vect) {
//        const long double M_PI_8 = M_PI_4 * 0.5;
//        const long double M_PI_16 = M_PI_4 * 0.25;
        if (vect.x == 0.0f && vect.y == 0.0f)
            return Direction::O;
        else {
            double radians = getAngleFromY(vect);
            if (std::abs(radians) < M_PI_4)
                return Direction::N;
            else if (std::abs(radians) > M_PI - M_PI_4)
                return Direction::S;
            else { //if (std::abs(radians) < M_PI_2 + M_PI_4) {
                if (radians > 0)
                    return Direction::E;
                else
                    return Direction::W;
            }
        }
    } //Direction::toOrthogonalDirection(const glm::vec2& vect)
    Direction Direction::toRelativeDirection(Direction baseDirection) {
        uint8_t relDirectionVal = static_cast<uint8_t>(value_) + static_cast<uint8_t>(baseDirection);
        relDirectionVal %= 8;
//        std::cout << "TRACE::DIRECTION::toRelativeDirection:: base = " << std::string(baseDirection)
//                  << ", original = " << to_string(*this)
//                  << ", relative = " << to_string(static_cast<Direction>(static_cast<Value>(relDirectionVal)))
//                  << std::endl;
        return static_cast<Value>(relDirectionVal);
    }
    // Returns unit vector in direction. If Direction::O, returns (0,0).
    glm::vec2 Direction::toVect2(Direction direction) { return direction.operator glm::vec2(); }
}