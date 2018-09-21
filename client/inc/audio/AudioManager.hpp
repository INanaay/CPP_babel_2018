//
// Created by NANAA on 19/09/18.
//

#ifndef CPP_BABEL_2018_AUDIOMANAGER_HPP
#define CPP_BABEL_2018_AUDIOMANAGER_HPP

#include <portaudio.h>
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

	/* input attriutes */

	PaError m_err;
	PaStream *m_inputStream;
	PaStreamParameters m_inputParameters;
	audioData m_inputData;
public:
	const audioData &getM_inputData() const;

private:
	int m_numSamples;

	/* output attributes */

	PaStreamParameters m_outputParameters;
	PaStream *m_outputStream;
	audioData m_outputData;
public:
	void setM_outputData(const audioData &m_outputData);
};

#endif //CPP_BABEL_2018_AUDIOMANAGER_HPP
