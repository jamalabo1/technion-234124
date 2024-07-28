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

            //This is a copy constructor for Holder
            Holder(const Holder &copy);

        public:
            Holder(T data);

            // to avoid confusion, and deep copies, assignment by value is not allowed.
            Holder &operator=(const Holder &other) = delete;

            const T &getData() const;

            // next name was used instead of getChain to provide a meaningful info about the expected output.
            Holder *next() const;

            // allow the setting of a chain
            void setChain(Holder *holder);

            static Holder *copyFromPointer(const Holder *other);
        };

        const SortedList<T> &iterable() const;

        Holder *head;
        int count;

        void releaseChain();

    public:
        //constructor of the sortedlist initialization empty
        //1. SortedList() - creates an empty list.
        SortedList();

        //constructor of the sortedlist initialization of the copy
        //2. copy constructor
        SortedList(const SortedList<T> &copy);


        //declares the assignment operator for the SortedList class template.
        // It allows one SortedList object to be assigned to another.
        //3. operator= - assignment operator
        SortedList<T> &operator=(const SortedList<T> &other);

        //4. ~SortedList() - destructor
        ~SortedList();

        //* iterator:
        //* 5. class ConstIterator;
        class ConstIterator;

        //6. begin method
        ConstIterator begin() const;

        //7. end method
        ConstIterator end() const;

        //8. insert - inserts a new element to the list
        void insert(const T &input);

        //9. remove - removes an element from the list
        void remove(const ConstIterator &toDelete);

        //10. length - returns the number of elements in the list
        int length() const;

        template<typename Func>
        // 11. filter - returns a new list with elements that satisfy a given condition
        SortedList filter(Func prediction) const;


        template<typename Func>
        //12. apply - returns a new list with elements that were modified by an operation
        SortedList apply(Func func) const;
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
        ConstIterator(Holder *holder);

        ConstIterator(const ConstIterator &other) = default;

        ConstIterator &operator=(const ConstIterator &other) = default;

        ~ConstIterator() = default;

        //5. operator* - returns the element the iterator points to
        const T &operator*() const;

        //6. operator++ - advances the iterator to the next element
        ConstIterator &operator++();

        //7. operator!= - returns true if the iterator points to a different element
        bool operator!=(const ConstIterator &other) const;
    };

}


namespace mtm {
    template<typename T>
    SortedList<T>::Holder::Holder(const SortedList::Holder &copy) : Holder(copy.data) {
        chain = Holder::copyFromPointer(copy.next());
    }

    template<typename T>
    SortedList<T>::Holder::Holder(T data)  : data(data), chain(nullptr) {}

    template<typename T>
    const T &SortedList<T>::Holder::getData() const {
        return data;
    }

    template<typename T>
    typename SortedList<T>::Holder *SortedList<T>::Holder::next() const {
        return chain;
    }

    template<typename T>
    void SortedList<T>::Holder::setChain(SortedList::Holder *holder) {
        chain = holder;
    }

    template<typename T>
    typename SortedList<T>::Holder *SortedList<T>::Holder::copyFromPointer(const SortedList::Holder *other) {
        if (other == nullptr) return nullptr;
        return new Holder(*other);
    }


    template<typename T>
    const SortedList<T> &SortedList<T>::iterable() const {
        return (*this);
    }

    template<typename T>
    void SortedList<T>::releaseChain() {
        Holder *current = head;
        while (current != nullptr) {
            Holder *temp = current;
            current = current->next();
            // Without temp, once current is advanced,
            // the reference to the Holder that needs to be deleted would be lost.
            delete temp;
        }
    }

    template<typename T>
    SortedList<T>::SortedList()  : head(nullptr), count(0) {};

    template<typename T>
    SortedList<T>::SortedList(const SortedList<T> &copy)
            : count(copy.count) {
        head = Holder::copyFromPointer(copy.head);
    }


    template<typename T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &other) {
        if (this == &other) return *this;


        Holder *copiedChain = Holder::copyFromPointer(other.head);

        releaseChain();

        head = copiedChain;
        count = other.count;

        return *this;
    }

    template<typename T>
    SortedList<T>::~SortedList() {
        releaseChain();
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(head);
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(nullptr);
    }

    template<typename T>
    void SortedList<T>::insert(const T &input) {
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
        count++;
    }


    template<typename T>
    void SortedList<T>::remove(const SortedList::ConstIterator &toDelete) {
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
        count--;
    }

    template<typename T>
    int SortedList<T>::length() const {
        return count;
    }

    template<typename T>
    template<typename Func>
    SortedList<T> SortedList<T>::filter(Func prediction) const {
        SortedList<T> newList;
        for (const T &current: iterable()) {
            if (prediction(current)) {
                newList.insert(current);
            }
        }
        return newList;
    }

    template<typename T>
    template<typename Func>
    SortedList<T> SortedList<T>::apply(Func func) const {
        SortedList<T> newList;
        for (const T &current: iterable()) {
            newList.insert(func(current));
        }
        return newList;
    }


    template<class T>
    SortedList<T>::ConstIterator::ConstIterator(SortedList::Holder *holder) : current(holder) {

    }

    template<class T>
    const T &SortedList<T>::ConstIterator::operator*() const {
        return current->getData();
    }

    template<class T>
    typename SortedList<T>::ConstIterator &SortedList<T>::ConstIterator::operator++() {
        if (current == nullptr) throw std::out_of_range("Iterator out of range");
        current = current->next();
        return *this;
    }

    template<class T>
    bool SortedList<T>::ConstIterator::operator!=(const SortedList<T>::ConstIterator &other) const {
        return current != other.current;
    }
}