//
// Created by NANAA on 20/09/18.
//

#include <iostream>
#include <exception>
#include <vector>
#include "../../inc/audio/AudioManager.hpp"
#include "../../inc/audio/AudioSettings.hpp"

AudioManager::AudioManager()
{
	m_err = Pa_Initialize();
	if (m_err != paNoError)
		throw std::exception();
	initInputDevice();
	initOutputDevice();
}

void AudioManager::initInputDevice()
{
	initInputParameters();

	m_err = Pa_OpenStream(
		&m_inputStream,
		&m_inputParameters,
		nullptr,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		recordCallback,
		this);

	if (m_err != paNoError)
		throw std::exception();

}

void AudioManager::initInputParameters()
{
	m_inputParameters.device = Pa_GetDefaultInputDevice();
	if (m_inputParameters.device == paNoDevice)
		throw std::exception();
	m_inputParameters.channelCount = 2;
	m_inputParameters.sampleFormat = paFloat32;
	m_inputParameters.suggestedLatency = Pa_GetDeviceInfo(m_inputParameters.device )->defaultLowInputLatency;
	m_inputParameters.hostApiSpecificStreamInfo = NULL;
}


void AudioManager::initOutputDevice()
{
	initOutputParameters();
	m_err = Pa_OpenStream(
		&m_outputStream,
		nullptr,
		&m_outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		playCallback,
		this);
	if (m_err != paNoError )
		throw std::exception();
	std::cout << "Output initilazing done.\n";
}


void AudioManager::initOutputParameters()
{
	m_outputParameters.device = Pa_GetDefaultOutputDevice();
	m_outputParameters.channelCount = 2;
	m_outputParameters.sampleFormat = paFloat32;
	m_outputParameters.suggestedLatency = Pa_GetDeviceInfo(m_outputParameters.device )->defaultLowOutputLatency;
	m_outputParameters.hostApiSpecificStreamInfo = NULL;
}


void AudioManager::startAudioRecording(void)
{
	m_err = Pa_StartStream(m_inputStream);
	if (m_err != paNoError)
		throw std::exception();

}

void AudioManager::stopAudioRecording(void)
{


	m_err = Pa_CloseStream( m_inputStream );
	if( m_err != paNoError )
		throw std::exception();



}

void AudioManager::startAudioPlaying(void)
{
	m_err = Pa_StartStream(m_outputStream);
	if (m_err != paNoError)
		throw std::exception();
}

void AudioManager::stopAudioPlaying(void)
{
	m_err = Pa_CloseStream(m_outputStream);
}


int AudioManager::playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
			       const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
			       void *userData) {

	auto *data = static_cast<AudioManager *> (userData);
	auto *wptr = static_cast<float *>(outputBuffer);


	data->m_mutex.lock();
	if (!data->samplesToPlay.empty()) {
		for (auto index = 0; index < framesPerBuffer * NB_CHANNELS; index++) {

			*wptr++ = data->samplesToPlay.front().audio[index];

		}
		data->samplesToPlay.pop_front();
	}

	data->m_mutex.unlock();
	return paContinue;
}


int AudioManager::recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
				 const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
				 void *userData) {

	auto *data = static_cast<AudioManager *>(userData);
	const auto *rptr = static_cast<const float *>(inputBuffer);
	decodedData decoded;

	decoded.size = framesPerBuffer * NB_CHANNELS;

	data->m_mutex.lock();

	if (inputBuffer == nullptr)
	{
		for (auto index = 0; index < framesPerBuffer * NB_CHANNELS ; index++)
			decoded.audio.push_back(0);
	}
	else
	{
		for (auto index = 0; index < framesPerBuffer * NB_CHANNELS; index++)
			decoded.audio.push_back(*rptr++);
	}

	data->recordedSamples.push_back(decoded);
	data->m_mutex.unlock();

	return paContinue; //TODO pacomplete when i want to finish.
}

decodedData AudioManager::getLastRecord() {
	if (!recordedSamples.empty()) {
		m_mutex.lock();
		auto sample = recordedSamples.front();
		recordedSamples.pop_front();
		m_mutex.unlock();
		return sample;
	}
	return decodedData();
}

void AudioManager::pushLastAudio(decodedData &sample)
{
	if (sample.size > 0) {
		m_mutex.lock();
		samplesToPlay.push_back(sample);
		m_mutex.unlock();
	}
}
