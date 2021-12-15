//
// Created by mfleres on 7/15/21.
//

#ifndef GRIDWORLD3D_LINKEDELEMENT_H
#define GRIDWORLD3D_LINKEDELEMENT_H

#include <memory>
#include <vector>

namespace util {
    template<class T>
    class LinkedElement {
    public:
        std::unique_ptr<T> element = nullptr;
        std::unique_ptr<LinkedElement<T>> next = nullptr;
        LinkedElement<T>() = default;
        explicit LinkedElement<T>(const T& t) { element = std::make_unique<T>(t); }
        explicit LinkedElement<T>(std::unique_ptr<T> t) { element = std::move(t); }
        //Override copy constructor because member variables are unique_ptrs.
        LinkedElement<T>(const LinkedElement<T>& other) {
            element = std::make_unique<T>(*other->element); //Copy the value of element.
            next = nullptr; //Cannot copy other->next without copying the entire list tail.
        }
        size_t countChildren() const;
        size_t count() const;
        size_t insert(size_t i, std::unique_ptr<T> t);
        size_t push_back(std::unique_ptr<T> t);
        std::unique_ptr<T> remove(size_t i);
        LinkedElement<T>* getElement(size_t& i, bool useLastElement = false, bool updateIndex = false) const;
        T* get(size_t& i, bool useLastElement = false, bool updateIndex = false) const;
        size_t find(const T& t);
        static void CLEAN(LinkedElement<T>*& head, bool removeEmptyElements = false);
        bool operator!() const { return !element && !next; }
    };
}

#endif //GRIDWORLD3D_LINKEDELEMENT_H
