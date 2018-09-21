//
// Created by NANAA on 20/09/18.
//

#ifndef CPP_BABEL_2018_AUDIOSETTINGS_HPP
#define CPP_BABEL_2018_AUDIOSETTINGS_HPP

#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NB_SECONDS (5)
#define NB_CHANNELS (2)

typedef struct
{
	int frameIndex;
	int maxFrameIndex;
	float *recordedSamples;
} audioData;

#endif //CPP_BABEL_2018_AUDIOSETTINGS_HPP
