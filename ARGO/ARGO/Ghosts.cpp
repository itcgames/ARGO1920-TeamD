#include "Ghosts.h"
#include <fstream>
#include <sstream>
Ghost::Ghost()
{
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		dstrect[i] = { 0, 0, 120, 120 };
		srcrect[i] = { 0, i*120, 120, 120 };
		if (i >= 5)
			srcrect[i].y -= 600;
	}
}

void Ghost::setUp(SDL_Renderer* t_screen)
{
	m_screen = t_screen;
	m_loadedSurface = SDL_LoadBMP("ASSETS/IMAGES/ghosts.bmp");
	m_texture = SDL_CreateTextureFromSurface(m_screen, m_loadedSurface);
}

int Ghost::update(std::string t_pos, int t_mainPlayerNum)
{
	/*mess = std::to_string(playerNum) + ":Cat-" + std::to_string(int(m_map.getCatPos().x)) + "," + std::to_string(int(m_map.getCatPos().y)) + ","
		+ "Clock-" + std::to_string(int(m_map.getClockPos().x)) + "," + std::to_string(int(m_map.getClockPos().y)) + ","
		+ "Book-" + std::to_string(int(m_map.getFlagPos().x)) + "," + std::to_string(int(m_map.getFlagPos().y)) + ","
		+ "Flag-" + std::to_string(int(m_map.getPlatformPos().x)) + "," + std::to_string(int(m_map.getPlatformPos().y)) + ","
		+ "Cactus-" + std::to_string(int(m_map.getCactusPos().x)) + "," + std::to_string(int(m_map.getCactusPos().y)) + ",";
		*/
	std::istringstream input;
	input.str(t_pos);
	std::string message = "";
	std::getline(input, message, ':');
	int playerNum = std::stoi(message);
	int index;
	if (playerNum == 1 || (t_mainPlayerNum = 1 && playerNum == 2))
	{
		index = 0;
	}
	else
	{
		index = 5;
	}
	while (std::getline(input, message, '-'))
	{
		std::getline(input, message, ',');
		dstrect[index].x = std::stoi(message);
		std::getline(input, message, ',');
		dstrect[index].y = std::stoi(message);
		index++;
	}
	index -= 5;
	for (int i = index; i < index + 5; i++)
	{
		srcrect[i].x = (playerNum-1) * 120;
	}
	return playerNum;
}

void Ghost::render()
{
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		SDL_RenderCopy(m_screen, m_texture, &srcrect[i], &dstrect[i]);
	}
}
