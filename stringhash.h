#pragma once

template<typename T>
size_t BKDRHash(const T* str)
{
    size_t hash = 0;
    while(size_t ch = (size_t)*str++)
    {
        hash = hash * 131 + ch;
    }
    return hash;
}

template<typename T>
size_t SDBMHash(const T* str)
{
    size_t hash = 0;
    while(size_t ch = (size_t)*str++)
    {
        hash = 65599 * hash + ch;
    }
    return hash;
}

template<typename T>
size_t RSHash(const T* str)
{
    size_t hash = 0;
    size_t magic = 63689;
    while(size_t ch = (size_t)*str++)
    {
        hash = hash * magic + ch;
        magic *= 378551;
    }
    return hash;
}


template<typename T>
size_t APHash(const T* str)
{
    size_t hash = 0;
    size_t ch;
    for(long long i = 0; ch = (size_t)*str++; i++)
    {
        if((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
        }
    }
    return hash;
}