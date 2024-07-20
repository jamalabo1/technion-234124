#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template<typename T>
    class SortedList {
    private:
        class Holder {
        private:
            T data;
            Holder *chain;

        public:
            Holder(T data) : data(data), chain(nullptr) {};

            Holder(const Holder &copy) : Holder(copy.data) {
                if (copy.chain != nullptr) {
                    // copy the chain
                    chain = new Holder(copy.chain);
                }
            }

            Holder &operator=(const Holder &other) {
                if (this == &other) return *this;

                data = other.data;
                chain = new Holder(other.chain);
            }

        };

        Holder head;
        int length;

    public:
        SortedList() : head(nullptr), length(0) {};

        SortedList(const SortedList<T> &copy) : head(copy.head), length(copy.length) {}

        SortedList<T> &operator=(const SortedList<T> &other) {
            if (this == &other) return *this;

            //TODO: check if copy by value
            head = other.head;
            length = other.length;
        }

        class ConstIterator;
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template<class T>
    class SortedList<T>::ConstIterator {
        /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */
    public:
        ConstIterator() = default;

        const T &operator*();
    };

}

