//
// Created by mfleres on 7/15/21.
//

#ifndef GRIDWORLD3D_DYNAMICARRAY_H
#define GRIDWORLD3D_DYNAMICARRAY_H

#include "LinkedElement.h"
#include <cstdarg>

namespace util {
    template <class T, uint8_t dimensions>
    class DynamicArray {
    private:
        std::unique_ptr<T> data_ = nullptr;
        std::unique_ptr<LinkedElement<DynamicArray<T, dimensions-1>>> topDimensionHead_;
    public:
        DynamicArray<T, dimensions>() {
            if (dimensions <= 1)
                topDimensionHead_ = nullptr;
            else {
                topDimensionHead_ = std::make_unique<LinkedElement<DynamicArray<T, dimensions - 1>>>();
                topDimensionHead_->element = std::make_unique<DynamicArray<T, dimensions - 1>>();
            }
        }
        explicit DynamicArray<T, dimensions>( T data ) {
            if (dimensions == 0) {
                data_ = data;
                topDimensionHead_ = nullptr;
            } else {
                topDimensionHead_ = std::make_unique<LinkedElement<DynamicArray<T, dimensions - 1>>>();
                topDimensionHead_->element = std::make_unique<DynamicArray<T, dimensions - 1>>( data );
            }
        }
        size_t count() const;
        size_t count(size_t i) const;
        size_t countAll() const;
        std::vector<size_t> insert(std::unique_ptr<T> t, const std::vector<size_t>& index);
        std::vector<size_t> push_back(std::unique_ptr<T>& t);
        std::vector<size_t> push_back(std::unique_ptr<T>& t, const std::vector<size_t>& index);
        void remove(const std::vector<size_t> index);
        std::unique_ptr<T> remove(size_t i...);
        T* get(const std::vector<size_t>& index) const;
        std::vector<size_t> find(const T& t) const;
//        std::vector<T*> get(size_t i...) const;
//        size_t find(size_t i, const T& t) const;
    };
}


#endif //GRIDWORLD3D_DYNAMICARRAY_H
