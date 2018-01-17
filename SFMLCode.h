#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Team.h"
#include "Standing.h"

class SFMLCode
{
private:
	// Draw boxes (for PLAYING and STANDINGS mode)
	static void drawBoxes(std::vector<Team>& teamsVector, sf::RenderWindow& win);
	static void drawBoxes(std::vector<Standing>& standingVector, sf::RenderWindow& win);
	// Draw header (PLAYING = match number; STANDINGS = "Competition Standings")
	static void drawHeader(sf::Font& font, sf::RenderWindow& win, std::string match);
	static void drawHeader(sf::Font& font, sf::RenderWindow& win);
	// Draw titles (PLAYING = team numbers; STANDINGS = category names)
	static void drawTitles(std::vector<Team>& teamsVector, sf::Font& font, sf::RenderWindow& win);
	static void drawTitles(std::vector<Standing>& standingVector, sf::Font& font, sf::RenderWindow& win);
	// Draw labels (PLAYING = gears, balls, climb; STANDINGS = team numbers)
	static void drawLabels(std::vector<Team>& teamsVector, sf::Font& font, sf::RenderWindow& win);
	static void drawLabels(std::vector<Standing>& standingVector, sf::Font& font, sf::RenderWindow& win);
	// Draw submit box for PLAYING mode
	static void drawSubmit(std::vector<Team>& teamsVector, sf::Font& font, sf::RenderWindow& win);
	// Draw values (PLAYING = gear and ball counts, climb yes/no, etc.; STANDINGS = averages and percentages)
	static void drawValues(std::vector<Team>& teamsVector, sf::Font& font, sf::RenderWindow& win);
	static void drawValues(std::vector<Standing>& standingVector, sf::Font& font, sf::RenderWindow& win);
	// Draw joystick message (run when a joystick is missing for a team) for PLAYING mode
	static void drawJoystickMessage(std::vector<Team>& teamsVector, sf::Font& font, sf::RenderWindow& win);
public:
	// Update values for when the window is resized to keep proportions correct
	static void updateSizeValues(double width, double height);

	// Used in positioning to move from box to box
	static double xOffset;
	static double yOffset;
	// Used to get the offset for positioning in different boxes (index = 0 through 5)
	static void getOffset(int index);

	// Used in drawing boxes and keeping elements proportional
	static double WIN_WIDTH;
	static double WIN_HEIGHT;
	static double BORDER_WIDTH;
	static double HEAD_HEIGHT;
	static double BOX_HEIGHT;
	static double BOX_WIDTH;
	static double BOX_BUFFER;

	// Used in keeping text size reasonable
	static double TITLE_SCALE;
	static double SCALE;

	// Constant strings that are used in the header and titles
	const static std::string HEADER_GAME_TEXT;
	const static std::string HEADER_STANDINGS_TEXT;
	const static std::string TITLE_TEXT;

	// Draw all the elements (PLAYING = 6 teams layout; STANDINGS = 6 categories layout)
	static void drawAll(sf::RenderWindow& win, std::vector<Team>& teamsVector, std::string match);
	static void drawAll(sf::RenderWindow& win, std::vector<Standing>& standingVector);
};