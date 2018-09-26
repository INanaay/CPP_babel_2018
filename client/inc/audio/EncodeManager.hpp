//
// Created by NANAA on 21/09/18.
//

#ifndef CPP_BABEL_2018_ENCODEMANAGER_HPP
#define CPP_BABEL_2018_ENCODEMANAGER_HPP

#include "opus/opus.h"
#include "IEncodeManager.hpp"

class EncodeManager : public IEncodeManager
{
public:
	EncodeManager();
	~EncodeManager() override;

	encodedData encode(const decodedData &data) override;
	virtual decodedData decode(const encodedData &data) override;

private:
	OpusEncoder *m_encoder;
	OpusDecoder *m_decoder;
};

#endif //CPP_BABEL_2018_ENCODEMANAGER_HPP
