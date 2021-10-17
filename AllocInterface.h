#pragma once

/**
 * interface to implement if one wants their custom allocator to be used in `Deque`
 */
class BaseAlloc {
public:
    /**
     * function to allocate the needed memory
     * @param size the size of the memory in bytes to allocate
     * @return pointer to the allocated memory
     */
    virtual void* alloc(size_t size) = 0;

    /**
     * function to free the allocated memory
     * @param ptr pointer to the allocated memory, which is to be deleted
     */
    virtual void clear(void* ptr) = 0;
};