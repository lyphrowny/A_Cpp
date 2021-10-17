#pragma once

class BaseAlloc {
public:
    virtual void* alloc(size_t size) = 0;
    virtual void clear(void *ptr) = 0;
};