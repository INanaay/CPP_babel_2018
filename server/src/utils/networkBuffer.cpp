//
// Created by flaviangontier on 9/21/18.
//

#include <cstdlib>
#include <cstring>
#include "../../inc/utils/networkBuffer.hpp"

networkBuffer::networkBuffer(std::size_t capacity)
: m_capacity(capacity), m_length(0)
{
    m_buffer = (char *)malloc(sizeof(char) * capacity);
}

networkBuffer::~networkBuffer()
{
    if (m_buffer != nullptr)
        free(m_buffer);
}

void networkBuffer::increase(std::size_t new_capacity)
{
    char *new_buffer = (char *)malloc(sizeof(char) * new_capacity);
    memcpy(new_buffer, m_buffer, m_length);

    free(m_buffer);
    m_buffer = new_buffer;
    m_capacity = new_capacity;
}

void networkBuffer::append(const char *buffer, std::size_t length)
{
    auto total_length = length + m_length;
    if (total_length > m_capacity)
        increase(total_length);

    memcpy(m_buffer + m_length, buffer, length);
    m_length += length;
}

const char *networkBuffer::access(std::size_t offset)
{
    if (offset > m_length)
        return nullptr;

    return m_buffer + offset;
}

char *networkBuffer::pop(std::size_t length)
{
    if (length > m_length)
        return nullptr;

    char *result = (char *)malloc(sizeof(char) * length);
    memcpy(result, m_buffer, length);
    memcpy(m_buffer, m_buffer + length, m_length - length);

    m_length -= length;
    return (result);
}

std::size_t networkBuffer::size() const
{
    return m_length;
}
