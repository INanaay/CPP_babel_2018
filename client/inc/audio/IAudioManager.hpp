//
// Created by NANAA on 19/09/18.
//

#ifndef CPP_BABEL_2018_IAUDIOMANAGER_HPP
#define CPP_BABEL_2018_IAUDIOMANAGER_HPP

#include "AudioSettings.hpp"

class IAudioManager
{
public:
	virtual ~IAudioManager() {}

	virtual void startAudioRecording(void) = 0;
	virtual void stopAudioRecording(void) = 0;
	virtual void startAudioPlaying(void) = 0;
	virtual void stopAudioPlaying(void) = 0;
	virtual decodedData getLastRecord() = 0;
	virtual void pushLastAudio(decodedData &) = 0;

private:
	virtual void initInputDevice() = 0;
	virtual void initOutputDevice() = 0;

	virtual void initInputParameters() = 0;
	virtual void initOutputParameters() = 0;
};

#endif //CPP_BABEL_2018_IAUDIOMANAGER_HPP
