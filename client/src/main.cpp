#include <iostream>
#include "../inc/audio/AudioManager.hpp"
#include "../inc/audio/EncodeManager.hpp"
#include <QApplication>
#include <QPushButton>
#include <client/gui/loginscreen.hpp>
#include <QDesktopWidget>
#include <client/inc/viewmodel/ViewModel.hpp>
#include <core/net/Socket.hpp>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ViewModel viewModel;

	viewModel.start();
	/*
	Client client;

	loginScreen loginScreen;
	loginScreen.setM_client(&client);
	loginScreen.show();

	//LoginScreen w;
	//w.show();

	 */

	return a.exec();
}


/*
int main(void)
{
	AudioManager audioManager;
	EncodeManager encodeManager;
	marguerite::net::Socket sock(marguerite::net::IpType::V4, marguerite::net::ProtocolType::UDP);
	sock.mBind("0.0.0.0", 6666);

	audioManager.startAudioRecording();
	//audioManager.startAudioPlaying();

	while (1)
	{
		auto sample = audioManager.getLastRecord();

		if (sample.size > 0)
		{

			auto encodedData = encodeManager.encode(sample);
			std::cout << "my size = " << encodedData.size << std::endl;

			std::cout << "Flavian =  " << encodedData.audio.size() << std::endl;

			sock.mSendTo(encodedData.audio, encodedData.size, "192.168.0.104", 6666);


			//auto relol = encodeManager.decode(lol);
			//audioManager.pushLastAudio(relol);
		}
		else
			audioManager.pushLastAudio(sample);
	}
}
 */