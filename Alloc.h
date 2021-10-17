#pragma once

#include <malloc.h>

#include "AllocInterface.h"

/**
 * implementation of interface `AllocInterface`
 */
class Alloc : public BaseAlloc {
public:
    /**
     * function to allocate the needed memory
     * @param size the size of the memory in bytes to allocate
     * @return pointer to the allocated memory
     */
    void* alloc(size_t size) final { return malloc(size); }

    /**
     * function to free the allocated memory
     * @param ptr pointer to the allocated memory, which is to be deleted
     */
    void clear(void* ptr) final { return free(ptr); }
};