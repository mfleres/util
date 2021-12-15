//
// Created by mfleres on 7/15/21.
//

#include "LinkedElement.h"

namespace util {
    template<class T>
    size_t LinkedElement<T>::countChildren() const {
        size_t c = 0;
        LinkedElement<T>* e = next.get();
        while (e) {
            c++;
            e = e->next.get();
        }
        return c;
    }

    template<class T>
    size_t LinkedElement<T>::count() const {
        return countChildren() + 1;
    }

    template<class T>
    size_t LinkedElement<T>::insert(size_t i, std::unique_ptr<T> a) {
        if (!element && !next) {
            element = std::move(a);
            return 0;
        } else if (!i) {
            std::unique_ptr<T> oldElement = std::move(element);
            std::unique_ptr<LinkedElement<T>> oldNext = std::move(next);
            element = std::move(a);
            next = std::make_unique<LinkedElement<T>>(oldElement);
            next->next = std::move(oldNext);
            return 0;
        }
        size_t index = 0;
        LinkedElement<T>* leadingElement = getElement(i, true, &index);
        std::unique_ptr<LinkedElement<T>> newElement = std::make_unique(a);
        newElement->next = std::move(leadingElement->next);
        leadingElement->next = std::move(newElement);

        return index;
    }

    template<class T>
    size_t LinkedElement<T>::push_back(std::unique_ptr<T> t) {
        if (!element && !next) {
            element = std::move(t);
            return 0;
        }
        LinkedElement<T>* e = this;
        size_t i = 1;
        while (e->next) {
            e = e->next;
            i++;
        }
        e->next = std::move(t);
        return i;
    }

    template<class T>
    std::unique_ptr<T> LinkedElement<T>::remove(size_t i) {
        if (i == 0) {
            auto retValue = std::move(element);
            if (next) {
                element = std::move(next->element);
                if (!next->next || !*(next->next))
                    next = nullptr; //Clean invalid node from memory.
                else
                    next = std::move(next->next);
            }
            return retValue;
        }

        LinkedElement<T>* leadingNode = this;
        size_t leadingIndex = 0;
        while (leadingNode->next && leadingIndex + 1 != i) {
            leadingNode = leadingNode->next.get();
            leadingIndex++;
        }

        if (leadingNode->next) {
            auto retNode = std::move(leadingNode->next);
            if (retNode->next && !!*(retNode->next))
                leadingNode->next = std::move(retNode->next);
            else
                leadingNode->next = nullptr; //Clean invalid node from memory.
            return retNode->element;
        } else {
            return nullptr;
        }
    }

    template<class T>
    LinkedElement<T>* LinkedElement<T>::getElement(size_t& i, bool useLastElement, bool updateIndex) const {
        size_t c = 0;
        LinkedElement<T>* e = this;
        while (c < i) {
            LinkedElement<T>* eNext = e->next.get();
            if (!eNext) {
                if (updateIndex)
                    i = c;
                if (useLastElement)
                    return e;
                else
                    return nullptr;
            }
            e = eNext;
            c++;
        }
        if (updateIndex)
            i = c;
        return e;
    }

    template<class T>
    T* LinkedElement<T>::get(size_t& i, bool useLastElement, bool updateIndex) const {
        auto foundElement = getElement(i, useLastElement, updateIndex);
        if (foundElement)
            return foundElement->element.get();
        else
            return nullptr;
    }

    template<class T>
    size_t LinkedElement<T>::find(const T& t) {
        LinkedElement<T>* node = this;
        size_t i = 0;
        while (node) {
            if (node->element && *(node->element) == t)
                return i;
            node = node->next;
            i++;
        }
        return (size_t) (-1);
    }

//TODO: TEST THIS FUNCTION.
    template<class T>
    void LinkedElement<T>::CLEAN(LinkedElement<T>*& head, bool removeEmptyElements) {
        //Ensure valid head
        if (!head || !*head) {
            head = nullptr;
            return;
        }
        while (removeEmptyElements && head->element == nullptr) {
            head = head->next;
            if (!head || !*head) {
                head = nullptr;
                return;
            }
        }

        LinkedElement<T>* node = head;
        while (node != nullptr && node->next != nullptr) {
            while (!*node->next || (removeEmptyElements && (!node->next->element || !*node->next->element))) {
                node->next = std::move(node->next->next); //Replace the invalid node->next
                if (node->next == nullptr)
                    break; //Reached end of list.
            }
            node = node->next; //node->next is valid or a simple nullptr.
        }
    }
}