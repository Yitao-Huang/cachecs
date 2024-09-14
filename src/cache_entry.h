#pragma once
#include "cache_buffer.h"
#include <cstddef>
#include <cstring>

template <typename T>
class cache_entry
{
public:
    cache_entry()
    {
        char* buf = get_buffer<T>();
        if (!buf)
        {
            create_buffer<T>();
            offset = 0;
        }
        offset = get_and_update_offset<T>();
    }

    void get(T& data) const
    {
        char* buf = get_buffer<T>();
        memcpy(&data, &buf[offset * sizeof(T)], sizeof(T));
    }

    void set(T&& data)
    {
        char* buf = get_buffer<T>();
        memcpy(&buf[offset * sizeof(T)], &data, sizeof(T));
    }

private:
    size_t offset;
};