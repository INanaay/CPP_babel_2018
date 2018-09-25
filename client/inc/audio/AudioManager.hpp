//
// Created by NANAA on 19/09/18.
//

#ifndef CPP_BABEL_2018_AUDIOMANAGER_HPP
#define CPP_BABEL_2018_AUDIOMANAGER_HPP

#include <deque>
#include <portaudio.h>
#include <mutex>
#include "IAudioManager.hpp"
#include "AudioSettings.hpp"

class AudioManager : public IAudioManager
{
public:
	AudioManager();

	void startAudioRecording(void) override;
	void stopAudioRecording(void) override;
	void startAudioPlaying(void) override;
	void stopAudioPlaying(void) override;
	decodedData getLastRecord();
	void pushLastAudio(decodedData &);




private:
	static int playCallback( const void *inputBuffer, void *outputBuffer,
				 unsigned long framesPerBuffer,
				 const PaStreamCallbackTimeInfo* timeInfo,
				 PaStreamCallbackFlags statusFlags,
				 void *userData );
	static int recordCallback( const void *inputBuffer, void *outputBuffer,
				   unsigned long framesPerBuffer,
				   const PaStreamCallbackTimeInfo* timeInfo,
				   PaStreamCallbackFlags statusFlags,
				   void *userData );

	void initInputDevice() override;
	void initOutputDevice() override;

	void initInputParameters() override;
	void initOutputParameters() override;

	PaError m_err;
	std::deque<decodedData> recordedSamples;
	std::deque<decodedData> samplesToPlay;
	std::mutex m_mutex {};

	/* input attriutes */

	PaStream *m_inputStream;
	PaStreamParameters m_inputParameters;

	/* output attributes */

	PaStreamParameters m_outputParameters;
	PaStream *m_outputStream;
};

#endif //CPP_BABEL_2018_AUDIOMANAGER_HPP
