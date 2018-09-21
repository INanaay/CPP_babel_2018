//
// Created by NANAA on 21/09/18.
//


#include <exception>
#include <iostream>
#include <vector>
#include "../../inc/audio/EncodeManager.hpp"
#include "../../inc/audio/AudioSettings.hpp"

EncodeManager::EncodeManager()
{
	int error;

	std::cout << "Creating encoder" << std::endl;
	m_encoder = opus_encoder_create(SAMPLE_RATE, NB_CHANNELS, OPUS_APPLICATION_VOIP, &error);
	m_decoder = opus_decoder_create(SAMPLE_RATE, NB_CHANNELS, &error);
}

unsigned char *EncodeManager::encode(const float *toEncode, int size)
{
	std::vector<uint8_t> encoded;

	auto sampleSize = FRAMES_PER_BUFFER * NB_CHANNELS;

	std::cout << "Tyring to encode\n";


	std::cout << "sampleSize = " << sampleSize << std::endl;


	encoded.resize(sampleSize);
	auto encodedSize = opus_encode_float(m_encoder, toEncode, FRAMES_PER_BUFFER, encoded.data(), sampleSize);

	std::cout << "size = " << encodedSize << std::endl;


	return encoded.data();

}

void EncodeManager::decode(const unsigned char *toDecode, float *decodedData, int size)
{
	auto ret = opus_decode_float(m_decoder, toDecode, size, decodedData, FRAMES_PER_BUFFER, 0);
	if (ret < 0)
		throw std::exception();

}

EncodeManager::~EncodeManager()
{
	opus_encoder_destroy(m_encoder);
	opus_decoder_destroy(m_decoder);
}
