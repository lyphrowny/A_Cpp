#pragma once

#include <malloc.h>

#include "AllocInterface.h"

class Alloc : public BaseAlloc {
public:
    void* alloc(size_t size) final { return malloc(size); }

    void clear(void* ptr) final { return free(ptr); }
};