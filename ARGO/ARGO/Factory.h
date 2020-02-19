#ifndef FACTORY
#define FACTORY
#include "Character.h" 
class Factory
{
public:

	virtual Character* createCat(Entity& t_ent, Vector2 t_pos, Vector2 t_size, std::string t_str, bool t_isAnim, const char* t_audioStr) = 0;
	virtual Character* createFlag(Entity& t_ent, Vector2 t_pos, Vector2 t_size, std::string t_str, bool t_isAnim, const char* t_audioStr) = 0;
};
#endif

#ifndef CHARACTERFACTORY
#define CHARACTERFACTORY
class CharacterFactory : public Factory
{
private:
	Character* m_test;
public:
	Character* createCat(Entity& t_ent, Vector2 t_pos, Vector2 t_size, std::string t_str, bool t_isAnim, const char* t_audioStr) { std::cout << "created a cat from factory" << std::endl; return m_test; }
	Character* createFlag(Entity& t_ent, Vector2 t_pos, Vector2 t_size, std::string t_str, bool t_isAnim, const char* t_audioStr) { std::cout << "created a flag from factory" << std::endl; return m_test; }
};
#endif