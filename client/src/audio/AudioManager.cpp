//
// Created by NANAA on 20/09/18.
//

#include <iostream>
#include <exception>
#include "../../inc/audio/AudioManager.hpp"

AudioManager::AudioManager()
{
	std::cout << "starting manager" << std::endl;
	initInputDevice();
	initOutputDevice();
}

void AudioManager::initInputDevice()
{
	m_inputData.maxFrameIndex = NB_SECONDS * SAMPLE_RATE;
	m_inputData.frameIndex = 0;
	m_numSamples = m_inputData.maxFrameIndex * NB_CHANNELS;
	m_inputData.recordedSamples = (float *) malloc(sizeof(float) * m_numSamples);

	if (!m_inputData.recordedSamples)
		throw std::exception();
	for (int index = 0; index < m_numSamples; index++)
		m_inputData.recordedSamples[index] = 0;
	std::cout << "intializing" << std::endl;

	m_err = Pa_Initialize();
	std::cout << "intializing" << std::endl;
	if (m_err != paNoError)
		throw std::exception();
	std::cout << "intializing input parameters" << std::endl;
	initInputParameters();
	std::cout << "Opening stream" << std::endl;

	m_err = Pa_OpenStream(
		&m_inputStream,
		&m_inputParameters,
		NULL,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		recordCallback,
		&m_inputData);

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
	m_outputData.frameIndex = 0;
	std::cout << "initalizing output parameters\n";
	initOutputParameters();
	std::cout << "opening output stream\n";
	m_err = Pa_OpenStream(
		&m_outputStream,
		NULL,
		&m_outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		playCallback,
		&m_outputData);
	if (m_err != paNoError )
		throw std::exception();
	std::cout << "Output initilazing done.\n";
}


void AudioManager::initOutputParameters()
{
	m_outputParameters.device = Pa_GetDefaultOutputDevice();
	m_outputParameters.channelCount = 2;
	m_outputParameters.sampleFormat = paFloat32;
	std::cout << "wtf\n";

	m_outputParameters.suggestedLatency = Pa_GetDeviceInfo(m_outputParameters.device )->defaultLowOutputLatency;
	std::cout << "wtf\n";
	m_outputParameters
		.hostApiSpecificStreamInfo = NULL;
	std::cout << "wtf\n";
}


void AudioManager::startAudioRecording(void)
{
	std::cout << "lol\n";
	m_err = Pa_StartStream(m_inputStream);
	if (m_err != paNoError)
		throw std::exception();
	printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
	while( ( m_err = Pa_IsStreamActive( m_inputStream ) ) == 1 )
	{
		Pa_Sleep(1000);
		printf("index = %d\n", m_inputData.frameIndex ); fflush(stdout);
	}
	if( m_err < 0 )
		throw std::exception();

}

void AudioManager::stopAudioRecording(void)
{


	m_err = Pa_CloseStream( m_inputStream );
	if( m_err != paNoError )
		throw std::exception();


	/* Measure maximum peak amplitude. */
	float max = 0;
	float average = 0.0;
	float val;
	for( int i=0; i < m_numSamples; i++ )
	{
		val = m_inputData.recordedSamples[i];
		if( val < 0 ) val = -val; /* ABS */
		if( val > max )
		{
			max = val;
		}
		average += val;
	}
	average = average / (double)m_numSamples;
	printf("sample max amplitude = %d\n", max );
	printf("sample average = %lf\n", average );
}

void AudioManager::startAudioPlaying(void)
{
	m_err = Pa_StartStream(m_outputStream);
	if (m_err != paNoError)
		throw std::exception();
	printf("Waiting for playback to finish.\n");
	fflush(stdout);
	while( ( m_err = Pa_IsStreamActive( m_outputStream ) ) == 1 )
		Pa_Sleep(100);
}

void AudioManager::stopAudioPlaying(void)
{
	m_err = Pa_CloseStream(m_outputStream);
}


int AudioManager::playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
			       const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
			       void *userData) {
	audioData *data = (audioData*)userData;
	float *rptr = &data->recordedSamples[data->frameIndex * NB_CHANNELS];
	float *wptr = (float*)outputBuffer;
	unsigned int i;
	int finished;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;
	(void) inputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;
	if( framesLeft < framesPerBuffer )
	{
		/* final buffer... */
		for( i=0; i<framesLeft; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( NB_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
		}
		for( ; i<framesPerBuffer; i++ )
		{
			*wptr++ = 0;  /* left */
			if( NB_CHANNELS == 2 ) *wptr++ = 0;  /* right */
		}
		data->frameIndex += framesLeft;
		finished = paComplete;
	}
	else
	{
		for( i=0; i<framesPerBuffer; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( NB_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
		}
		data->frameIndex += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}

int AudioManager::recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
				 const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
				 void *userData) {
	audioData *data = (audioData*)userData;
	const float *rptr = (const float*)inputBuffer;
	float *wptr = &data->recordedSamples[data->frameIndex * NB_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
	(void) outputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;
	if( framesLeft < framesPerBuffer )
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}
	if( inputBuffer == NULL )
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = 0.0f;  /* left */
			if( NB_CHANNELS == 2 )
				*wptr++ = 0.0f;  /* right */
		}
	}
	else
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( NB_CHANNELS == 2 )
				*wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}

const audioData &AudioManager::getM_inputData() const {
	return m_inputData;
}

void AudioManager::setM_outputData(const audioData &m_outputData) {
	AudioManager::m_outputData = m_outputData;
}
