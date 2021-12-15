//
// Created by mfleres on 7/20/21.
//

#ifndef GRIDWORLD3D_INDEXEDARRAY_H
#define GRIDWORLD3D_INDEXEDARRAY_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

namespace util {
    template<class T>
    class IndexedArray {
    private:
        struct IndexedElement {
        public:
            size_t index = LONG_LONG_MAX - 1;
            T data;
            IndexedElement() = default;
            explicit IndexedElement(size_t i) : index(i) {}
            IndexedElement(T& d, size_t i)
                : data(std::move(d)), index(i) {}
        };
        size_t capacity_ = 0;
        std::vector<IndexedElement> indexedArray_;
        T nullReference = T();

//        size_t realIndex(size_t index);
    public:
        using iterator = T*;
        using const_iterator = const T*;
        static bool DEBUG_VERBOSE;

        T& operator[]( size_t index ) {
//            std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Start." << std::endl;
            if ( index >= capacity_ )
                throw std::out_of_range("ERROR::INDEXEDARRAY<T>::OPERATOR[]::OUT_OF_RANGE");

            size_t i;
            for ( i = 0; i < indexedArray_.size(); i++ ) {
                if ( indexedArray_[i].index == index ) {
//                    std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Found matching index." << std::endl;
                    IndexedElement& element = indexedArray_[i];
                    T& data = element.data;
//                    if (index != i)
//                        std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]("<<index<<"): FOUND: Real index = " << i << std::endl;
                    return data;
                } else if ( indexedArray_[i].index > index ) {
                    std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]("<<index<<"): NOT FOUND: Real index = " << i << std::endl;
                    break;
                }
            }
//            std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Couldn't find index. i = " << i << std::endl;
            if ( i >= indexedArray_.size() || indexedArray_[i].index <= index) {
                // Add new element to back of array.
//                std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Adding new element to back of array." << std::endl;
                indexedArray_.emplace_back( IndexedElement( index ) );
//                std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: End(1)." << std::endl;
//                std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: push_back new element with index = " << indexedArray_.back().index << std::endl;
                return indexedArray_.back().data;
            } else {
                // Insert new element into middle of array.
//                std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Inserting new element into middle of array." << std::endl;
                indexedArray_.insert( indexedArray_.begin() + i, IndexedElement( index ) );
                IndexedElement& element = indexedArray_[i];
                T& data = element.data;
//                std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: End(2)." << std::endl;
                return data;
            }
        }
        const T& operator[]( size_t index ) const {
//            std::cout << "TRACE::INDEXEDARRAY::OPERATOR[] CONST: Start." << std::endl;
            if ( index >= capacity_ )
                return nullReference;

            size_t i;
            for ( i = 0; i < indexedArray_.size(); i++ ) {
                if ( indexedArray_[i].index == index ) {
//                    std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]: Found matching index." << std::endl;
                    const IndexedElement& element = indexedArray_[i];
                    const T& data = element.data;
//                    if (index != i)
//                        std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]("<<index<<"): FOUND: Real index = " << i << std::endl;
                    return data;
                } else if ( indexedArray_[i].index > index ) {
//                    std::cout << "TRACE::INDEXEDARRAY::OPERATOR[]("<<index<<") CONST: NOT FOUND: Real index = " << i << std::endl;
                    break;
                }
            }
            return nullReference;
        }
        void set(const T& data, size_t index) {
            std::cout << "TRACE::INDEXEDARRAY::SET(index = "<<index<<"): Start." << std::endl;
            if (index >= capacity_) {
                capacity_ = index + 1;
                indexedArray_.push_back( IndexedElement( data, index ) );
            } else {
                operator[]( index ) = data;
            }
            std::cout << "TRACE::INDEXEDARRAY::SET: End." << std::endl;
        }
        void resize(size_t size) {
//            std::cout << "TRACE::INDEXEDARRAY::RESIZE("<<size<<"): Start." << std::endl;
            // Remove any elements indexed out of the new bounds.
            if ( size < capacity_ ) {
                int i;
//                std::cout << "TRACE::INDEXEDARRAY::RESIZE: Compressing... indexedArray.size() = " << indexedArray_.size()
//                          << " size = " << size << " capacity_ = " << capacity_ << std::endl;
                for (i = indexedArray_.size() - 1; i >= 0 && indexedArray_[i].index >= size; i--);
//                std::cout << "TRACE::INDEXEDARRAY::RESIZE: Compressing down to real-size " << i << std::endl;
                if (i >= 0)
                    indexedArray_.resize(i);
            }
            capacity_ = size;
//            std::cout << "TRACE::INDEXEDARRAY::RESIZE: End." << std::endl;
        }
        void push_back(const T& data) {
            std::cout << "TRACE::INDEXEDARRAY::PUSH_BACK: Start." << std::endl;
            size_t newIndex = indexedArray_.back().index + 1;
            if ( newIndex >= capacity_ )
                capacity_++;
            indexedArray_.push_back( IndexedElement( data, newIndex ) );
            std::cout << "TRACE::INDEXEDARRAY::PUSH_BACK: End." << std::endl;
        }
        size_t count( bool includeDefaults = false ) const {
            std::cout << "TRACE::INDEXEDARRAY::COUNT: Start." << std::endl;
            if ( !includeDefaults ) {
                size_t c = 0;
                for (const IndexedElement& element : indexedArray_)
                    if (element.data != T())
                        c++;
//                std::cout << "TRACE::INDEXEDARRAY::COUNT: END(0)." << std::endl;
                return c;
            } else {
//                std::cout << "TRACE::INDEXEDARRAY::COUNT: END(1)." << std::endl;
                return indexedArray_.size();
            }
        }
        size_t size() const { return capacity_; }
        iterator begin() { return &indexedArray_[0].data; }
        const_iterator begin() const { return &indexedArray_[0].data; }
        iterator end() { return &indexedArray_.end()->data; }
        const_iterator end() const { return &indexedArray_.end()->data;; }

//        void clean();
//        bool indexExists(size_t index, bool includeDefault = false) const;

    };
}

#endif //GRIDWORLD3D_INDEXEDARRAY_H
