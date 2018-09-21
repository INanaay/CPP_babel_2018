//
// Created by NANAA on 21/09/18.
//

#ifndef CPP_BABEL_2018_IENCODEMANAGER_HPP
#define CPP_BABEL_2018_IENCODEMANAGER_HPP

class IEncodeManager
{
public:
	virtual ~IEncodeManager() {}

	virtual unsigned char *encode(const float *toEncode, int size) = 0;
	virtual void decode(const unsigned char *toDecode, float *decodedData, int size) = 0;

};

#endif //CPP_BABEL_2018_IENCODEMANAGER_HPP
