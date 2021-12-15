//
// Created by mfleres on 7/15/21.
//

#include "DynamicArray.h"

namespace util {
    template <class T, uint8_t d>
    size_t DynamicArray<T,d>::count() const {
        if ( topDimensionHead_ )
            return topDimensionHead_->count();
        else
            return 0;
    }

    //TODO: implement functions below.
    template <class T, uint8_t d>
    size_t DynamicArray<T,d>::count(size_t i) const {
        LinkedElement<T>* e;
        if (d > 1 && topDimensionHead_ && (e = topDimensionHead_->get(i)) && e->element)
            return e->element->count();
        return 0;
    }
    template <class T, uint8_t d>
    size_t DynamicArray<T,d>::countAll() const {
        if (d == 0)
            return 1;
        else if (d == 1)
            return count();
        size_t c = 0;
        LinkedElement<T>* e = topDimensionHead_.get();
        while (e) {
            if (e->element)
                c += e->element->count();
            e = e->next.get();
        }
        return c;
    }
    template <class T, uint8_t d>
    std::vector<size_t> DynamicArray<T,d>::insert(std::unique_ptr<T> t, const std::vector<size_t>& index) {
        if (d == 0) {
            data_ = std::move(t);
            return {};
        } else if (index.size() < d) {
            return {};
        } else if (d == 1) {
            auto package = std::make_unique<DynamicArray<T, 0>>( std::move(t) );
            size_t i = topDimensionHead_->insert(index[0], package);
            return { i };
        }

        if (!topDimensionHead_) {
            topDimensionHead_ = std::make_unique<LinkedElement<DynamicArray<T, d - 1>>>();
            topDimensionHead_->element = std::make_unique<DynamicArray<T, d - 1>>();
            topDimensionHead_->element->insert(t,std::vector<size_t>(d - 1));
            return std::vector<size_t>(d);
        }

        std::vector<size_t> retIndex(d);
        std::vector<size_t> subIndex = std::vector<size_t>( index.begin() + 1, index.end() );
        size_t topIndex = index[0];
        auto subDimension = topDimensionHead_->get(topIndex, true, true);
        if (!subDimension) {
            auto emptySubDimension = std::make_unique<DynamicArray<T, d - 1>>();
            subDimension = emptySubDimension.get();
            retIndex[0] = topDimensionHead_->push_back( std::move(emptySubDimension) );
        } else {
            retIndex[0] = topIndex;
        }
        subIndex = subDimension->insert(t, subIndex);
        retIndex.insert(retIndex.end(),subIndex.begin(),subIndex.end());
        return retIndex;
    }

    template <class T, uint8_t d>
    std::vector<size_t> DynamicArray<T, d>::push_back(std::unique_ptr<T>& t) {
        if (d > 0) {
            std::vector<size_t> retVector(d);
            auto data = std::make_unique<DynamicArray<T, d - 1>>( t );
            retVector[0] = topDimensionHead_->push_back( std::move( data ) );
            return retVector;
        } else {
            data_ = std::move( t );
            return {};
        }
    }
//    template <class T, uint8_t d>
//    std::vector<size_t> DynamicArray<T,d>::push_back(size_t i, std::unique_ptr<T>& t);
//    template <class T, uint8_t d>
//    void DynamicArray<T,d>::remove(size_t i);
//    template <class T, uint8_t d>
//    std::unique_ptr<T> DynamicArray<T,d>::remove(size_t i...);
    template <class T, uint8_t d>
    T* DynamicArray<T,d>::get( const std::vector<size_t>& index ) const {
        if (index.size() != d)
            return nullptr;
        if (d == 0 || !topDimensionHead_)
            return data_.get();

        auto linkedEle = topDimensionHead_->get( index[0] );
        if ( linkedEle ) {
            if ( d == 1 )
                return linkedEle->data_.get();
            else
                return linkedEle->get( std::vector<size_t>(index.begin()+1, index.end()) );
        }
        return nullptr;
    }
//    template <class T, uint8_t d>
//    std::vector<size_t> DynamicArray<T,d>::find(const T& t) const;
}