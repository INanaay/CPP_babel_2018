//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_LISTMESSAGE_HPP
#define CPP_BABEL_2018_LISTMESSAGE_HPP

#include <core/io/BinaryStreamReader.hpp>
#include <core/io/BinaryStreamWriter.hpp>

class ListMessage
{
private:
    bool m_valid;

public:
    //FUNCTIONS
    std::vector<std::tuple<std::string, std::string, int>> unpack(marguerite::io::BinaryStreamReader &reader);
    void pack(marguerite::io::BinaryStreamWriter &writer, std::vector<std::tuple<std::string, std::string, int>> &contacts);
};


#endif //CPP_BABEL_2018_LISTMESSAGE_HPP
