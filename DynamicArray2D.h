//
// Created by mfleres on 6/14/21.
//

#ifndef GRIDWORLD3D_DYNAMICARRAY2D_H
#define GRIDWORLD3D_DYNAMICARRAY2D_H

#include "LinkedElement.h"

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace util {
    template<class T>
    class DynamicArray2D {
    private:
        typedef glm::vec2 vec2i;

        std::unique_ptr<LinkedElement<LinkedElement<T>>> array2dHead = std::make_unique<LinkedElement<LinkedElement<T>>>();
    public:
        size_t count() const;
        size_t count(size_t i) const;
        size_t countAll() const;
        vec2i insert(std::unique_ptr<T> t, size_t i, size_t j);
        vec2i push_back(std::unique_ptr<T>& t);
        vec2i push_back(size_t i, std::unique_ptr<T>& t);
        void remove(size_t i);
        std::unique_ptr<T> remove(size_t i, size_t j);
        std::vector<T*> get(size_t i) const;
        T* get(size_t i, size_t j) const;
        vec2i find(const T& t) const;
        size_t find(size_t i, const T& t) const;
    };
}

#endif //GRIDWORLD3D_DYNAMICARRAY2D_H
