#include"Jump.h"

void JumpCommand::execute(Joystick& stick, std::vector<Vector2> t_mapsize, EntityManager manager)
{
	manager.handleEvents(stick, t_mapsize);
}
