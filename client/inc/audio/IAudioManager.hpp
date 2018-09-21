//
// Created by NANAA on 19/09/18.
//

#ifndef CPP_BABEL_2018_IAUDIOMANAGER_HPP
#define CPP_BABEL_2018_IAUDIOMANAGER_HPP

class IAudioManager
{
public:
	virtual ~IAudioManager() {}

	virtual void startAudioRecording() = 0;
	virtual void stopAudioRecording() = 0;
	virtual void startAudioPlaying() = 0;
	virtual void stopAudioPlaying() = 0;

private:
	virtual void initInputDevice() = 0;
	virtual void initOutputDevice() = 0;

	virtual void initInputParameters() = 0;
	virtual void initOutputParameters() = 0;
};

#endif //CPP_BABEL_2018_IAUDIOMANAGER_HPP
