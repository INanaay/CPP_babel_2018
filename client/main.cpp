
#include <iostream>
#include "inc/audio/AudioManager.hpp"
#include "inc/audio/EncodeManager.hpp"


int main(void)
{
	EncodeManager encodeManager;

	AudioManager audioManager;

	audioManager.startAudioRecording();
	audioManager.stopAudioRecording();

	auto temp = audioManager.getM_inputData();
	temp.frameIndex = 0;

	std::cout << "Encoding data" << std::endl;

	auto encoded = encodeManager.encode(temp.recordedSamples, 0);

	std::cout << "yo\n";


	audioManager.setM_outputData(temp);
	audioManager.startAudioPlaying();
}
