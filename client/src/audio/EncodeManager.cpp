//
// Created by NANAA on 21/09/18.
//


#include <exception>
#include <iostream>
#include <vector>
#include <client/inc/audio/EncodeManager.hpp>

#include "../../inc/audio/EncodeManager.hpp"
#include "../../inc/audio/AudioSettings.hpp"

EncodeManager::EncodeManager()
{
	int error;

	std::cout << "Creating encoder" << std::endl;
	m_encoder = opus_encoder_create(SAMPLE_RATE, NB_CHANNELS, OPUS_APPLICATION_VOIP, &error);
	m_decoder = opus_decoder_create(SAMPLE_RATE, NB_CHANNELS, &error);
}

EncodeManager::~EncodeManager()
{
	opus_encoder_destroy(m_encoder);
	opus_decoder_destroy(m_decoder);
}

encodedData EncodeManager::encode(const decodedData &data) {

	encodedData encoded{};
	auto sampleSize = FRAMES_PER_BUFFER * NB_CHANNELS;

	std::cout << "ptdr" << std::endl;
	encoded.audio.resize(sampleSize);
	std::cout << "ptdr" << std::endl;

	encoded.size = opus_encode_float(m_encoder, data.audio.data(), FRAMES_PER_BUFFER, encoded.audio.data(), sampleSize);

	std::cout << "size = " << encoded.size << std::endl;

	if (encoded.size < 0)
		throw std::exception();
	return (encoded);

}

decodedData EncodeManager::decode(const encodedData &data) {
	decodedData decoded{};


	std::cout << "Trying to decode" << std::endl;
	std::cout << "Size = " << data.size << std::endl;

	decoded.audio.resize(FRAMES_PER_BUFFER * NB_CHANNELS);

	decoded.size = opus_decode_float(m_decoder, data.audio.data(), data.size, decoded.audio.data(), FRAMES_PER_BUFFER, 0);
	std::cout << "decoded" << std::endl;
	std::cout << "Decoded size = " << decoded.size << std::endl;
	if (decoded.size < 0)
		throw std::exception();
	return decoded;
}
