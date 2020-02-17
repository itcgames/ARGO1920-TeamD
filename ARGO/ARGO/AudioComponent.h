#ifndef AUDIOCOMPONENT
#define AUDIOCOMPONENT
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <string>
#include "Component.h"
class AudioComponent: public Component
{
public:
	AudioComponent();
	~AudioComponent();
	void LoadMusicFile( const char * t_string);
	void playAudio();
	void closeAudio();
	void init() override;
	void update() override;
	void render() override;
private:
	Mix_Music* m_music;
	Mix_Chunk* m_chunk;
	bool doOnce = false;
};
#endif // !AUDIOCOMPONENT
