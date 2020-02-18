#pragma once
class Command
{
public:
	Command();
	virtual ~Command() = 0;
	virtual void execute() = 0;
};