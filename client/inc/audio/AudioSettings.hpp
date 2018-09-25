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

// TODO use usings in a scope

#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (480)
#define NB_SECONDS (2)
#define NB_CHANNELS (2)

typedef struct
{
	int frameIndex;
	int maxFrameIndex;
	float *recordedSamples;
	std::vector<float> recorded;
} audioData;

typedef struct
{
	std::vector<uint8_t> audio;
	int size;
} encodedData;

typedef struct
{
	std::vector<float> audio {};
	int size = 0;
} decodedData;

#endif //CPP_BABEL_2018_AUDIOSETTINGS_HPP
