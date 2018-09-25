//
// Created by NANAA on 21/09/18.
//

#ifndef CPP_BABEL_2018_IENCODEMANAGER_HPP
#define CPP_BABEL_2018_IENCODEMANAGER_HPP

#include "AudioSettings.hpp"

class IEncodeManager
{
public:
	virtual ~IEncodeManager() {}

	virtual encodedData encode(const decodedData &data) = 0;
	virtual decodedData decode(const encodedData &data) = 0;

};

#endif //CPP_BABEL_2018_IENCODEMANAGER_HPP
