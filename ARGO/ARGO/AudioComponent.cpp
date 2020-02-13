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
}

AudioComponent::~AudioComponent()
{
}

AudioComponent::AudioComponent(const char* t_string)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	/// <summary>
	/// for thia function 41000 is the recommended frequency in Hertz
	/// 2 is the number of channels used for the audio
	/// 4096 is the number of chunks for this Audio
	/// </summary>
	Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, 2, 4096);
	m_music = Mix_LoadMUS(t_string);
	Mix_FreeMusic(m_music);
}

void AudioComponent::LoadMusicFile(const char* t_string)
{
	m_music = Mix_LoadMUS(t_string);
	Mix_FreeMusic(m_music);
}

void AudioComponent::closeAudio()
{
	Mix_CloseAudio();
}

void AudioComponent::playAudio()
{
	Mix_PlayMusic(m_music,-1);
}
