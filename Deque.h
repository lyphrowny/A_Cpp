#pragma once

#include "Alloc.h"

template<class T, class A = Alloc>
class Deque {
private:
    static inline std::string emptyPop = "Stop! You're popping from an empty queue";

    struct Node {
        static inline A _alloc = A();
        Node* _next, * _prev;
        const T _data;

        explicit Node(const T &data, Node* next = nullptr, Node* prev = nullptr) : _next(next), _prev(prev),
                                                                                   _data(data) {}

        explicit Node(T &&data, Node* next = nullptr, Node* prev = nullptr) : _next(next), _prev(prev),
                                                                              _data(std::move(data)) {}

        static void* operator new(size_t size) { return _alloc.alloc(size); }

        static void operator delete(void* ptr) { _alloc.clear(ptr); }
    };

    Node* _head, * _tail;
    size_t _size{};

    void _reset(const size_t size = 0, Node* head = nullptr, Node* tail = nullptr) {
        _head = head;
        _tail = tail;
        _size = size;
    }

    void _connectNodes(Node* prev, Node* curr, Node* next) {
        if (prev != nullptr)
            prev->_next = curr;
        if (next != nullptr)
            next->_prev = curr;

        curr->_prev = prev;
        curr->_next = next;
    }

    void _connectNodes(Node* prev, Node* next) {
        if (prev != nullptr)
            prev->_next = next;
        if (next != nullptr)
            next->_prev = prev;
    }

public:
    class iterator {
    private:
        Node* _curr;
        static inline std::string valueFromNullptr = "Yes, I see - you're trying to get something, that doesn't even exists...\n"
                                                     "Keep it up! (in some other place, though,"
                                                     " for while I am here, your legs are bulletproof)";
    public:
        explicit iterator(Node* node = nullptr) { _curr = node; };

        iterator(std::initializer_list<Node*> list) { _curr = *list.begin(); }

        iterator(const iterator &it) { _curr = it._curr; };

        iterator &operator=(const iterator &it) {
            if (*this != it)
                _curr = it._curr;
            return *this;
        };

        bool operator==(const iterator &it) const { return this->_curr == it._curr; };

        bool operator!=(const iterator &it) const { return this->_curr != it._curr; };

        iterator &operator++() {
            if (_curr)
                _curr = _curr->_next;
            return *this;
        };

        iterator &operator--() {
            if (_curr)
                _curr = _curr->_prev;
            return *this;
        };

        iterator operator+(size_t size) const {
            if (_curr) {
                if (size > 0) return {_curr->_next};
                else if (size < 0) return {_curr->_prev};
            }
            return {_curr};
        };

        iterator operator-(size_t size) const { return *this + (-size); };

        const T &operator*() const {
            if (_curr)
                return _curr->_data;
            else
                throw std::runtime_error(valueFromNullptr);
        };

        iterator* operator->() const { return _curr; };
    };

    iterator begin() { return iterator(_head); };

    iterator end() { return iterator(); };

    Deque() : _head(nullptr), _tail(nullptr), _size(0) {};

    Deque(std::initializer_list<T> data) : _head(nullptr), _tail(nullptr), _size(0) {
        for (auto &d: data)
            pushBack(d);
    }

    // FIXME the parameter should be const, but in order for it to be,
    //      one should implement const iterator, which I lack :(
    Deque(Deque &other) : _head(nullptr), _tail(nullptr), _size(0) {
        for (auto it = other.begin(); it != other.end(); ++it)
            pushBack(*it);
    }

    Deque(Deque &&other) noexcept: _head(other._head), _tail(other._tail), _size(other._size) {
        other._reset();
    }

    bool isEmpty() { return _head == nullptr && _tail == nullptr && _size == 0; }

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

    void pushFront(const T &data) {
        if (isEmpty())
            pushBack(data);
        else {
            _connectNodes(nullptr, new Node(data), _head);
            _head = _head->_prev;
        }
        _size++;
    }

    void pushFront(T &&data) {
        if (isEmpty())
            pushBack(data);
        else {
            _connectNodes(nullptr, new Node(std::move(data)), _head);
            _head = _head->_prev;
        }
        _size++;
    }

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

    T const &peekTail() {
        if (isEmpty())
            std::cerr << emptyPop << std::endl;
        return _tail->_data;
    }

    T const &peekHead() {
        if (isEmpty())
            std::cerr << emptyPop << std::endl;
        return _head->_data;
    }

    // FIXME the parameter should be const, but in order for it to be,
    //      one should implement const iterator, which I lack :(
    Deque &operator+(Deque &deque) {
        for (auto it = deque.begin(); it != deque.end(); ++it)
            pushBack(*it);
        return *this;
    }

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
    friend std::ostream &operator<<(std::ostream &os, Deque<T, A> &deque) {
        os << "Deque(";
        for (auto curr = deque.begin(); curr != iterator(deque._tail); ++curr)
            os << *curr << ", ";
        if (!deque.isEmpty())
            os << deque._tail->_data << ");" << std::endl;
        return os;
    }

    void clear() {
        while (!isEmpty())
            popBack();
        _reset();
    }

    ~Deque() { clear(); }
};