#pragma once
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "types.h"

#define INITIAL_BUFFER_SIZE 4096

template <size_t N>
struct buffer_pool
{
    buffer_pool() = default;

    ~buffer_pool()
    {
        for (size_t idx = 0; idx < N; idx++)
        {
            char* buf = pool[idx];
            if (buf)
            {
                if (munmap(buf, config[idx].buffer_size) == -1) {
                    perror("munmap failed");
                }
            }
        }
    }

    struct metadata
    {
        size_t buffer_size;
        size_t offset;
    };

    char* pool[N] = {};
    metadata config[N] = {};
};

static buffer_pool<NUM_SUPPORTED_TYPES> buffer_pool_;

template <typename T>
inline void create_buffer()
{
    size_t idx = get_type<T>();

    void* addr = mmap(nullptr, INITIAL_BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) 
    {
        throw std::runtime_error("mmap failed");
    }

    buffer_pool_.pool[idx] = static_cast<char*>(addr);
    buffer_pool_.config[idx].buffer_size = INITIAL_BUFFER_SIZE;
    buffer_pool_.config[idx].offset = 0;
}

template <typename T>
inline char* get_buffer()
{
    size_t idx = get_type<T>();
    /* invalid type check only happens in get */ 
    /* because it's called before create and scale */
    if (idx == INVALID_TYPE_ID)
    {
        throw std::runtime_error("invalid type");
    }
    return buffer_pool_.pool[idx];
}

inline void scale_buffer(size_t idx)
{
    size_t old_size = buffer_pool_.config[idx].buffer_size;
    buffer_pool_.config[idx].buffer_size *= 2;

    void* old_addr = buffer_pool_.pool[idx];
    void* new_addr = mmap(nullptr, old_size * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_addr == MAP_FAILED) 
    {
        throw std::runtime_error("mmap failed");
    }
    buffer_pool_.pool[idx] = static_cast<char*>(new_addr);

    memcpy(new_addr, old_addr, old_size);
    if (munmap(old_addr, old_size) == -1)
    {
        throw std::runtime_error("munmap failed");
    }
}

template <typename T>
inline size_t get_and_update_offset()
{
    size_t idx = get_type<T>();
    if (buffer_pool_.config[idx].offset * sizeof(T) >= buffer_pool_.config[idx].buffer_size)
    {
        scale_buffer(idx);
    }
    return buffer_pool_.config[idx].offset++;
}