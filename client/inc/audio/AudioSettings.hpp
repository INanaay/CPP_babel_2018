//
// Created by NANAA on 20/09/18.
//

#ifndef CPP_BABEL_2018_AUDIOSETTINGS_HPP
#define CPP_BABEL_2018_AUDIOSETTINGS_HPP

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (512)
#define NB_SECONDS (2)
#define NB_CHANNELS (2)

typedef struct
{
	int frameIndex;
	int maxFrameIndex;
	float *recordedSamples;
} audioData;

typedef struct encodedData
{
	std::vector<uint8_t> encoded;
	int size;
} encodedData;

#endif //CPP_BABEL_2018_AUDIOSETTINGS_HPP
