#ifndef AUDIOCOMPONENT
#define AUDIOCOMPONENT
#include "SDL_mixer.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include "Component.h"
class AudioComponent: public Component
{
public:
	AudioComponent();
	~AudioComponent();
	AudioComponent(const char* t_string);
	void LoadMusicFile( const char * t_string);
	void closeAudio();
	void playAudio();
private:
	Mix_Music* m_music;
};
#endif // !AUDIOCOMPONENT
