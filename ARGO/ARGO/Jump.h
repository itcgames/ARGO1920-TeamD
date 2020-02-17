#pragma once
#include"Command.h"

class JumpCommand : public Command
{
public:
	virtual void execute() { jump(); }
};
