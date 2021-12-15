//
// Created by mfleres on 6/14/21.
//

#include "DynamicArray2D.h"

namespace util {
    template<class T>
    size_t DynamicArray2D<T>::count() const {
        if (array2dHead)
            return array2dHead->countChildren() + 1;
        return 0;
    }

    template<class T>
    size_t DynamicArray2D<T>::count(size_t i) const {
        LinkedElement<T>* e;
        if (array2dHead && (e = array2dHead->get(i)) && e->element)
            return e->element->countChildren() + 1;
        return 0;
    }

    template<class T>
    size_t DynamicArray2D<T>::countAll() const {
        size_t c = 0;
        LinkedElement<T>* e = array2dHead.get();
        while (e) {
            if (e->element)
                c += e->element->countChildren() + 1;
            e = e->next.get();
        }
        return c;
    }

    template<class T>
    glm::vec2 DynamicArray2D<T>::insert(std::unique_ptr<T> t, size_t i, size_t j) {
        if (!array2dHead) {
            array2dHead = std::make_unique<LinkedElement<T>>(t);
            return glm::vec2(0.0f, 0.0f);
        }
        LinkedElement<T>* iList = nullptr;
        auto result = array2dHead->get(i, true, true);
        if (result)
            iList = result->element.get();
        return glm::vec2((float) i, (float) (iList->insert(j, t)));
    }

    typedef glm::vec2 vec2i;

    template<class T>
    vec2i DynamicArray2D<T>::push_back(std::unique_ptr<T>& t) {
        size_t i = array2dHead->push_back(std::make_unique<LinkedElement<T>>(t));
        return vec2i(i, 0);
    }

    template<class T>
    vec2i DynamicArray2D<T>::push_back(size_t i, std::unique_ptr<T>& t) {
        LinkedElement<T>* rowHead = nullptr;
        auto result = array2dHead->get(i, false, true);
        if (result)
            rowHead = result->element.get();
        if (rowHead) {
            size_t j = rowHead->push_back(std::make_unique<LinkedElement<T>>(t));
            return vec2i(i, j);
        } else
            return push_back(t);
    }

    template<class T>
    void DynamicArray2D<T>::remove(size_t i) {
        array2dHead->remove(i);
    }

    template<class T>
    std::unique_ptr<T> DynamicArray2D<T>::remove(size_t i, size_t j) {
        LinkedElement<T>* rowHead = nullptr;
        auto result = array2dHead->get(i, false, true);
        if (result)
            rowHead = result->element.get();
        if (rowHead) {
            auto ret = rowHead->remove(j);
            if (!*rowHead)
                array2dHead->remove(i);
            return std::move(ret);
        }
        return nullptr;
    }

    template<class T>
    std::vector<T*> DynamicArray2D<T>::get(size_t i) const {
        std::vector<T*> ret;
        LinkedElement<T>* rowNode = nullptr;
        auto result = array2dHead->get(i);
        if (result)
            rowNode = result->element.get();
        while (rowNode) {
            if (rowNode->element)
                ret.push_back(rowNode->element.get());
            rowNode = rowNode->next.get();
        }
        return ret;
    }

    template<class T>
    T* DynamicArray2D<T>::get(size_t i, size_t j) const {
        LinkedElement<T>* rowNode = array2dHead->get(i);
        if (rowNode)
            return rowNode->get(j);
        return nullptr;
    }

    template<class T>
    vec2i DynamicArray2D<T>::find(const T& t) const {
        size_t i = 0;
        LinkedElement<LinkedElement<T>>* rowHead = array2dHead.get();
        LinkedElement<T>* node = nullptr;
        while (rowHead) {
            node = rowHead->element.get();
            size_t j = 0;
            if (node) {
                j = node->find(t);
                if (j != (size_t) (-1))
                    return vec2i(i, j);
            }
            j++;
            rowHead = rowHead->next.get();
        }
        return vec2i(-1, -1);
    }

    template<class T>
    size_t DynamicArray2D<T>::find(size_t i, const T& t) const {
        LinkedElement<T>* rowHead = nullptr;
        auto getResult = array2dHead->get(i);
        if (getResult)
            rowHead = getResult->element.get();
        if (rowHead)
            return rowHead->find(t);
        else
            return (size_t) (-1);
    }
}