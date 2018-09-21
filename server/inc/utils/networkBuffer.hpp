//
// Created by flaviangontier on 9/21/18.
//

#ifndef CPP_BABEL_2018_NETWORKBUFFER_HPP
#define CPP_BABEL_2018_NETWORKBUFFER_HPP


class networkBuffer
{
public:
    //CTOR DTOR
    explicit networkBuffer(std::size_t length = 256);
    ~networkBuffer();

    //FUNCTIONS
    void append(const char *buffer, std::size_t length);
    const char *access(std::size_t offset = 0);
    char *pop(std::size_t length);

    //PROPERTIES
    std::size_t size() const;

private:
    //FIELDS
    char *m_buffer;
    std::size_t m_length;
    std::size_t m_capacity;

    //FUNCTIONS
    void increase(std::size_t new_capacity);
};


#endif //CPP_BABEL_2018_NETWORKBUFFER_HPP
