#include "AudioComponent.h"



AudioComponent::AudioComponent()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	/// <summary>
	/// for thia function 41000 is the recommended frequency in Hertz
	/// 2 is the number of channels used for the audio
	/// 4096 is the number of chunks for this Audio
	/// </summary>
	Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, 2, 4096);
	if (Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Error initialising SDL" << std::endl;
	}
}

AudioComponent::~AudioComponent()
{
	Mix_Quit();
}



void AudioComponent::LoadMusicFile(const char* t_string)
{
	m_music = Mix_LoadMUS(t_string);
	//m_chunk = Mix_LoadWAV("ASSETS/AUDIO/temp.wav");
	if (m_music == nullptr)
	{
		std::cout << "error loading file in audio" << std::endl;
	}
	
}

void AudioComponent::playAudio()
{
	if (!doOnce)
	{
		Mix_PlayMusic(m_music, -1);
		doOnce = true;
	}
}

void AudioComponent::closeAudio()
{
	Mix_FreeMusic(m_music);
	Mix_CloseAudio();
	Mix_Quit();
}


void AudioComponent::init()
{
	
}

void AudioComponent::update()
{
	playAudio();
}

void AudioComponent::render()
{
}
