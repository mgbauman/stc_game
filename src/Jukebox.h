#pragma once
#include "sdl/include/SDL.h"
#include "sdl/include/SDL_mixer.h"
#include <stdio.h>
#include <string>
#include <vector>

class Jukebox
{
public:
	Mix_Music *clip;
    std::vector<Mix_Chunk*> effects;

	Jukebox();
	~Jukebox();
    void Jukebox::loadMusic(const char* music);
    void Jukebox::loadEffect(const char* effect);
	void Jukebox::play();
    void Jukebox::playEffect(int);
    int Jukebox::revEngine(bool idle);
    void Jukebox::stop(int channel);
    int Jukebox::isPlaying(int channel);
    void Jukebox::setup();
    void Jukebox::stopMusic();

    enum soundEffects
        {
            firehook, gravpull, metalhit, hollowhit, revengine, idle, menumove, menuselect
    };
};

