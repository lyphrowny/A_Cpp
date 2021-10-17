#include <iostream>

#include "Alloc.h"
#include "Deque.h"

int main() {
    // check default constructor
    Deque<int> deque1;
    std::cout << deque1 << std::endl;

    // check initializer list constructor
    Deque<int> deque2({ 1, 2, 3, 4, 5 });
    std::cout << deque2 << std::endl;

    // check copy constructor
    Deque<int> deque3(deque2);
    std::cout << deque3 << std::endl;

    // check move constructor
    Deque<int> deque4(Deque<int>({ 1, 2, 3, 4, 5 }));
    std::cout << deque4 << std::endl;

    // check copy operator=
    Deque<int> deque5 = deque2;
    std::cout << deque5 << std::endl;

    // check move operator=
    Deque<int> deque6 = Deque<int>({ 1, 2, 3, 4, 5 });
    std::cout << deque6 << std::endl;

    // check peekHead
    std::cout << deque2.peekHead() << std::endl;

    // check peekTail
    std::cout << deque6.peekTail() << std::endl;

    // check pushFront with move semantic
    deque3.pushFront(30);
    std::cout << deque3 << std::endl;

    // check pushBack with move semantic
    deque4.pushBack(47);
    std::cout << deque4 << std::endl;

    // check pushFront with copy semantic
    int a = 30;
    deque3.pushFront(a);
    std::cout << deque3 << std::endl;

    // check pushBack with copy semantic
    deque4.pushBack(a);
    std::cout << deque4 << std::endl;

    // check popFront
    deque2.popFront();
    std::cout << deque2 << std::endl;

    // check popBack
    deque5.popBack();
    std::cout << deque5 << std::endl;

    // check move concatenate
    std::cout << Deque<int>({1, 2, 3, 4, 5}).operator+({6, 7, 8, 9, 10}) << std::endl;

    // check copy concatenate
    std::cout << Deque<int>({ 1, 2, 3, 4, 5 }).operator+(deque2) << std::endl;

    // check clear and IsEmpty
    std::cout << deque2.isEmpty() << std::endl;
    deque2.clear();
    std::cout << deque2.isEmpty() << std::endl;
    return 0;
}
