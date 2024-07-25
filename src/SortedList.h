#pragma once

#include <iostream>
#include <stdexcept>
#include <functional>

#define FOREACH(statement) for(const T& current : iterable()) { \
statement }

namespace mtm {

    template<typename T>
    class SortedList {
    private:
        class Holder {
        private:
            T data;
            Holder *chain;


        public:

            Holder(T data)
                    : data(data), chain(nullptr) {};

            //This is a copy constructor for Holder
            Holder(const Holder &copy) : Holder(copy.data) {
                if (copy.chain != nullptr) {
                    // copy the chain
                    chain = new Holder(*copy.chain);
                }
            }

            //check ensures that if you are assigning an object to itself,
            //it does nothing and returns *this to avoid self-assignment issues.
            Holder &operator=(const Holder &other) {
                if (this == &other) return *this;

                data = other.data;
                if (other.chain == nullptr) {
                    chain = nullptr;
                } else {
                    chain = new Holder(other.chain);
                }
            }

            const T &getData() {
                return data;
            }

            Holder *next() {
                return chain;
            }

            void setChain(Holder *holder) {
                chain = holder;
            }
        };

        const SortedList<T> &iterable() const {
            return *this;
        }

        Holder *head;
        int length;

    public:
        //constructor of the sortedlist initialization empty
        //1. SortedList() - creates an empty list.
        SortedList()
                : head(nullptr), length(0) {};

        //constructor of the sortedlist initialization of the copy
        //2. copy constructor
        SortedList(const SortedList<T> &copy)
                : length(copy.length) {
            if (copy.head != nullptr) {
                head = new Holder(*copy.head);
            } else {
                head = nullptr;
            }
        }


        //declares the assignment operator for the SortedList class template.
        // It allows one SortedList object to be assigned to another.
        //3. operator= - assignment operator
        SortedList<T> &operator=(const SortedList<T> &other) {
            if (this == &other) return *this;

            if (other.head != nullptr) {
                head = new Holder(*other.head);
            }
            length = other.length;

            return *this;
        }

        //4. ~SortedList() - destructor
        ~SortedList() {
            Holder *current = head;
            while (current != nullptr) {
                Holder *temp = current;
                current = current->next();
                // Without temp, once current is advanced,
                // the reference to the Holder that needs to be deleted would be lost.
                delete temp;
            }

        }

        //* iterator:
        //* 5. class ConstIterator;
        class ConstIterator;

        //6. begin method
        ConstIterator begin() const {
            return ConstIterator(head);
        }

        //7. end method
        ConstIterator end() const {
            return ConstIterator(nullptr);
        }

        //8. insert - inserts a new element to the list
        void insert(const T &input) {
            Holder *newInput = new Holder(input);
            if (head == nullptr || input > head->getData()) {
                newInput->setChain(head);
                head = newInput;
            } else {
                Holder *current = head;
                //find the last place that the input is bigger than the value in it
                while (current->next() != nullptr && (current->next()->getData() > input)) {
                    current = current->next();
                }
                //once you find it update the next and put it in the right place
                newInput->setChain(current->next());
                current->setChain(newInput);
            }
            // we added a new number then the length will increase
            length++;
        }

        //9. remove - removes an element from the list
        void remove(const ConstIterator &toDelete) {
            //check if empty
            if (head == nullptr)
                return;

            Holder *current = head;
            Holder *previous = nullptr;

            while (current != nullptr && &current->getData() != &*toDelete) {
                previous = current;
                current = current->next();
            }

            if (current == nullptr) return; //the line was not found

            if (previous == nullptr) {
                // in the situation where the list is just one number
                head = current->next();
            } else {
                // make the previous one make two steps forward
                previous->setChain(current->next());
            }
            // manged to find the number and to delete it
            delete current;
            length--;
        }

        //10. length - returns the number of elements in the list
        int size() const {
            return length;
        }

        // 11. filter - returns a new list with elements that satisfy a given condition
        SortedList filter(std::function<bool(T)> prediction) const {
            SortedList<T> newList;
            for (const T &current: iterable()) {
                if (prediction(current)) {
                    newList.insert(current);
                }
            }
            return newList;
        }

        //12. apply - returns a new list with elements that were modified by an operation
        SortedList apply(std::function<T(const T &)> func) const {
            SortedList<T> newList;
            for (const T &current: iterable()) {
                newList.insert(func(current));
            }
            return newList;
        }

    };

    template<class T>
    class SortedList<T>::ConstIterator {
    private:
        Holder *current;

    public:
        //* constructors and destructor:
        //* 1. a ctor(or ctors) your implementation needs
        //* 2. copy constructor
        //* 3. operator= - assignment operator
        //* 4. ~ConstIterator() - destructor
        ConstIterator(Holder *holder) : current(holder) {}

        ConstIterator(const ConstIterator &other) = default;

        ConstIterator &operator=(const ConstIterator &other) = default;

        ~ConstIterator() = default;

        //5. operator* - returns the element the iterator points to
        const T &operator*() const {
            return current->getData();
        }

        //6. operator++ - advances the iterator to the next element
        ConstIterator &operator++() {
            if (current == nullptr) throw std::out_of_range("Iterator out of range");
            current = current->next();
            return *this;
        }

        //7. operator!= - returns true if the iterator points to a different element
        bool operator!=(const ConstIterator &other) const {
            return current != other.current;
        }
    };
}
