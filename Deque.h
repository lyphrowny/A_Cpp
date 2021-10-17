#pragma once

#include "Alloc.h"

/**
 * Deque implementation using double-linked list
 * @tparam T data type
 * @tparam A allocator, should inherit AllocInterface interface
 */
template<class T, class A = Alloc>
class Deque {
private:
    /**
     * Message to be printed when popping from an empty deque is attempted
     */
    static inline std::string emptyPop = "Stop! You're popping from an empty queue";

    /**
     * internal class used to implement the double-linked list
     */
    struct Node {
        /**
         * allocator for `new` and `delete`
         */
        static inline A _alloc = A();
        /**
         * pointers required for double-linked list
         */
        Node* _next, * _prev;
        /**
         * data is stored here
         */
        const T _data;

        /**
         * copy constructor
         * @param data data to store
         * @param next pointer to the next (right) node
         * @param prev pointer to the previous (left) node
         */
        explicit Node(const T &data, Node* next = nullptr, Node* prev = nullptr) : _next(next), _prev(prev),
                                                                                   _data(data) {}

        /**
         * move constructor
         * @param data data to store
         * @param next pointer to the next (right) node
         * @param prev pointer to the previous (left) node
         */
        explicit Node(T &&data, Node* next = nullptr, Node* prev = nullptr) : _next(next), _prev(prev),
                                                                              _data(std::move(data)) {}

        /**
         * new operator implementation
         * @param size the size of memory in bytes to allocate
         * @return `void*` pointer to the allocated memory
         */
        static void* operator new(size_t size) { return _alloc.alloc(size); }

        /**
        * delete operator implementation
        * @param ptr pointer to the memory to be freed
        */
        static void operator delete(void* ptr) { _alloc.clear(ptr); }
    };

    /**
     * pointers to the 'beginning' and 'ending' of the double-linked list
     */
    Node* _head, * _tail;
    /**
     * size of the double-linked list
     */
    size_t _size{};

    /**
     * @brief function to nullify internal data
     * @param size new size (=0)
     * @param head new head (=nullptr)
     * @param tail new tail (=nullptr)
     */
    void _reset(const size_t size = 0, Node* head = nullptr, Node* tail = nullptr) {
        _head = head;
        _tail = tail;
        _size = size;
    }

    /**
     * function helper to connect three nodes by changing the corresponding pointers
     * @param prev the pointer to connect with `curr` (using its `_next`)
     * @param curr the pointer to connect with `prev` and `next`
     * @param next the pointer to connect with `curr` (using its `_prev`)
     */
    void _connectNodes(Node* prev, Node* curr, Node* next) {
        if (prev != nullptr)
            prev->_next = curr;
        if (next != nullptr)
            next->_prev = curr;

        curr->_prev = prev;
        curr->_next = next;
    }

    /**
     * function helper to connect two nodes by changing the corresponding pointers
     * @param prev the pointer to connect with `next` (using its `_next`)
     * @param next the pointer to connect with `prev` (using its `_prev`)
     */
    void _connectNodes(Node* prev, Node* next) {
        if (prev != nullptr)
            prev->_next = next;
        if (next != nullptr)
            next->_prev = prev;
    }

public:
    /**
     * class implementing the iterator pattern
     */
    class iterator {
    private:
        /**
         * pointer to the current node
         */
        Node* _curr;
        /**
         * message to show on attempt to get the `_data` from `nullptr`
         */
        static inline std::string valueFromNullptr = "Yes, I see - you're trying to get something, that doesn't even exists...\n"
                                                     "Keep it up! (in some other place, though,"
                                                     " for while I am here, your legs are bulletproof)";
    public:
        /**
         *
         * @param node
         */
        explicit iterator(Node* node = nullptr) { _curr = node; };

        /**
         * initializer list constructor
         * @param list initializer list
         */
        iterator(std::initializer_list<Node*> list) { _curr = *list.begin(); }

        /**
         * copy constructor
         * @param it const reference to the iterator
         */
        iterator(const iterator &it) { _curr = it._curr; };

        /**
         * copy assignment
         * @param it const reference to the iterator
         * @return iterator with changed position
         */
        iterator &operator=(const iterator &it) {
            if (*this != it)
                _curr = it._curr;
            return *this;
        };

        /**
         * operator to compare to 'states' of iterator
         * @param it iterator to which state to compare to
         * @return `true` if the states are equal, `false` otherwise
         */
        bool operator==(const iterator &it) const { return this->_curr == it._curr; };

        /**
         * operator to compare to 'states' of iterator
         * @param it iterator to which state to compare to
         * @return `false` if the states are equal, `true` otherwise
         */
        bool operator!=(const iterator &it) const { return this->_curr != it._curr; };

        /**
         * operator to shift the iterator to the next state
         * @return shifter iterator
         */
        iterator &operator++() {
            if (_curr)
                _curr = _curr->_next;
            return *this;
        };

        /**
         * operator to shift the iterator to the previous state
         * @return shifter iterator
         */
        iterator &operator--() {
            if (_curr)
                _curr = _curr->_prev;
            return *this;
        };

        /**
         * @brief operator to shift the iterator to the different state
         * @param size if positive, alike ++; negative - --; 0 - the state is unchanged
         * @return the shifted iterator
         */
        iterator operator+(size_t size) const {
            if (_curr) {
                if (size > 0) return {_curr->_next};
                else if (size < 0) return {_curr->_prev};
            }
            return {_curr};
        };

        /**
         * @brief operator to shift the iterator to the different state
         * @param size if positive, alike --; negative - ++; 0 - the state is unchanged
         * @return the shifted iterator
         */
        iterator operator-(size_t size) const { return *this + (-size); };

        /**
         * operator to get internal data
         * @throws runtime error in the attempt to get the data of `nullptr`
         * @return internal data
         */
        const T &operator*() const {
            if (_curr)
                return _curr->_data;
            else
                throw std::runtime_error(valueFromNullptr);
        };

        /**
         * operator to get the access to the state node
         * @return state node
         */
        iterator* operator->() const { return _curr; };
    };

    /**
     * the beginning of the iterator
     * @return the iterator to the `begin` state of the iterator
     */
    iterator begin() { return iterator(_head); };

    /**
     * the ending of the iterator
     * @return the iterator to the `end` state of the iterator
     */
    iterator end() { return iterator(); };

    /**
     * default constructor
     */
    Deque() : _head(nullptr), _tail(nullptr), _size(0) {};

    /**
     * initializer list constructor
     * @param data initializer list data
     */
    Deque(std::initializer_list<T> data) : _head(nullptr), _tail(nullptr), _size(0) {
        for (auto &d: data)
            pushBack(d);
    }

    // FIXME the parameter should be const, but in order for it to be,
    //      one should implement const iterator, which I lack :(
    /**
     * copy constructor
     * @param other the other deque to be copied
     */
    Deque(Deque &other) : _head(nullptr), _tail(nullptr), _size(0) {
        for (auto it = other.begin(); it != other.end(); ++it)
            pushBack(*it);
    }

    /**
     * move constructor
     * @param other the other deque to be moved
     */
    Deque(Deque &&other) noexcept: _head(other._head), _tail(other._tail), _size(other._size) {
        other._reset();
    }

    /**
     * function to check whether the deque is empty
     * @return `true` if the deque is empty, `false` otherwise
     */
    bool isEmpty() { return _head == nullptr && _tail == nullptr && _size == 0; }

    /**
     * function to place the new element to the back of the double-linked list with copy semantics
     * @param data data of the new node
     */
    void pushBack(const T &data) {
        auto* node = new Node(data);
        if (isEmpty())
            _head = _tail = node;
        else {
            _connectNodes(_tail, node, nullptr);
            _tail = _tail->_next;
        }
        _size++;
    }

    /**
     * function to place the new element to the back of the double-linked list with move semantics
     * @param data data of the new node
     */
    void pushBack(T &&data) {
        auto* node = new Node(std::move(data));
        if (isEmpty())
            _head = _tail = node;
        else {
            _connectNodes(_tail, node, nullptr);
            _tail = _tail->_next;
        }
        _size++;
    }

    /**
     * function to place the new element to the front of the double-linked list with copy semantics
     * @param data data of the new node
     */
    void pushFront(const T &data) {
        if (isEmpty())
            pushBack(data);
        else {
            _connectNodes(nullptr, new Node(data), _head);
            _head = _head->_prev;
        }
        _size++;
    }

    /**
     * function to place the new element to the front of the double-linked list with move semantics
     * @param data data of the new node
     */
    void pushFront(T &&data) {
        if (isEmpty())
            pushBack(data);
        else {
            _connectNodes(nullptr, new Node(std::move(data)), _head);
            _head = _head->_prev;
        }
        _size++;
    }

    /**
     * function to delete the element from the back of the doubled-linked list
     * @return the value stored in the deleted element
     */
    T popBack() {
        if (isEmpty())
            throw std::runtime_error(emptyPop);
        auto p_data = _tail->_data;
        if (_size-- > 1) {
            _tail = _tail->_prev;
            delete _tail->_next;
            _tail->_next = nullptr;
        } else {
            delete _tail;
            _reset();
        }
        return p_data;
    }

    /**
     * function to delete the element from the front of the doubled-linked list
     * @return the value stored in the deleted element
     */
    T popFront() {
        if (isEmpty()) {
            throw std::runtime_error(emptyPop);
        }
        auto p_data = _head->_data;
        if (_size-- > 1) {
            _head = _head->_next;
            delete _head->_prev;
            _head->_prev = nullptr;
        } else {
            delete _head;
            _reset();
        }
        return p_data;
    }

    /**
     * function to get the const value of element from the back of the doubled-linked list without deleting it
     * @return the const value stored in the element at the back
     */
    T const &peekTail() {
        if (isEmpty())
            std::cerr << emptyPop << std::endl;
        return _tail->_data;
    }

    /**
     * function to get the const value of element from the front of the doubled-linked list without deleting it
     * @return the const value stored in the element at the front
     */
    T const &peekHead() {
        if (isEmpty())
            std::cerr << emptyPop << std::endl;
        return _head->_data;
    }

    // FIXME the parameter should be const, but in order for it to be,
    //      one should implement const iterator, which I lack :(
    /**
     * concatenate two deques using copy semantics
     * @param deque the deque to concatenate with
     * @return the concatenated deques
     */
    Deque &operator+(Deque &deque) {
        for (auto it = deque.begin(); it != deque.end(); ++it)
            pushBack(*it);
        return *this;
    }

    /**
     * concatenate two deques using move semantics
     * @param deque the deque to concatenate with
     * @return the concatenated deques
     */
    Deque &operator+(Deque &&deque) {
        if (!isEmpty()) {
            if (!deque.isEmpty()) {
                _connectNodes(_tail, deque._head);
                _tail = deque._tail;
                _size += deque._size;

                deque._reset();
            }
            return *this;
        }
        return deque;
    }

    // FIXME the second parameter should be const, but in order for it to be,
    //      one should implement const iterator, which I lack :(
    /**
     * operator << for printing the deque
     * @param os the `ostream` to print to
     * @param deque thi `deque` to print
     * @return modified output stream
     */
    friend std::ostream &operator<<(std::ostream &os, Deque<T, A> &deque) {
        os << "Deque(";
        for (auto curr = deque.begin(); curr != iterator(deque._tail); ++curr)
            os << *curr << ", ";
        if (!deque.isEmpty())
            os << deque._tail->_data << ");" << std::endl;
        return os;
    }

    /**
     * function to delete every internal node
     */
    void clear() {
        while (!isEmpty())
            popBack();
        _reset();
    }

    /**
     * destructor
     */
    ~Deque() { clear(); }
};