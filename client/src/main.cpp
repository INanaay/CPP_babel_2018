#include <iostream>
#include "../inc/audio/AudioManager.hpp"
#include "../inc/audio/EncodeManager.hpp"
#include <QApplication>
#include <QPushButton>
#include <client/gui/loginscreen.hpp>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Client client;

	loginScreen loginScreen;
	loginScreen.setM_client(&client);
	loginScreen.show();


	//LoginScreen w;
	//w.show();

	return a.exec();
}


/*
using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QPushButton button("hello world");

    button.show();
    return app.exec();
} */


/*
int main(void)
{
	AudioManager audioManager;
	EncodeManager encodeManager;

	audioManager.startAudioRecording();
	audioManager.startAudioPlaying();

	while (1)
	{
		auto sample = audioManager.getLastRecord();

		if (sample.size > 0) {
			auto lol = encodeManager.encode(sample);

			auto relol = encodeManager.decode(lol);
			audioManager.pushLastAudio(relol);
			std::cout << "ptdr\n";

		}
		else
			audioManager.pushLastAudio(sample);
	}
}
*/