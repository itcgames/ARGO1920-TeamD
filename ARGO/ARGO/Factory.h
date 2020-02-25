#ifndef FACTORY
#define FACTORY
#include "Character.h" 
class Factory
{
public:

	virtual Character* createCatAudio(Entity& t_ent, const char* t_audioStr) = 0;
	virtual Character* createFlagAudio(Entity& t_ent, const char* t_audioStr) = 0;
	virtual Character* createRockAudio(Entity& t_ent, const char* t_audioStr) = 0;
	virtual Character* createPlatformAudio(Entity& t_ent, const char* t_audioStr) = 0;
	virtual Character* createCactusAudio(Entity& t_ent, const char* t_audioStr) = 0;
};
#endif	//!FACTORY

#ifndef CHARACTERFACTORY
#define CHARACTERFACTORY
class CharacterFactory : public Factory
{
private:
	Character* m_test;
public:
	Character* createCatAudio(Entity& t_ent, const char* t_audioStr) { t_ent.addComponent<AudioComponent>(); t_ent.addComponent<AudioComponent>().LoadMusicFile(t_audioStr); std::cout << "created a cat audio component from factory" << std::endl; return m_test; }
	Character* createFlagAudio(Entity& t_ent, const char* t_audioStr) { t_ent.addComponent<AudioComponent>(); t_ent.addComponent<AudioComponent>().LoadMusicFile(t_audioStr); std::cout << "created a flag audio component from factory" << std::endl; return m_test; }
	Character* createRockAudio(Entity& t_ent, const char* t_audioStr) { t_ent.addComponent<AudioComponent>(); t_ent.addComponent<AudioComponent>().LoadMusicFile(t_audioStr); std::cout << "created a flag audio component from factory" << std::endl; return m_test; }
	Character* createPlatformAudio(Entity& t_ent, const char* t_audioStr) { t_ent.addComponent<AudioComponent>(); t_ent.addComponent<AudioComponent>().LoadMusicFile(t_audioStr); std::cout << "created a flag audio component from factory" << std::endl; return m_test; }
	Character* createCactusAudio(Entity& t_ent, const char* t_audioStr) { t_ent.addComponent<AudioComponent>(); t_ent.addComponent<AudioComponent>().LoadMusicFile(t_audioStr); std::cout << "created a flag audio component from factory" << std::endl; return m_test; }

};
#endif	//!CHARACTERFACTORY