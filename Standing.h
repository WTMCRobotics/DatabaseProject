#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Standing
{
private:
	sf::RectangleShape box;
	sf::Text categoryNameLabel;
	sf::Text team1Name;
	sf::Text team2Name;
	sf::Text team3Name;
	sf::Text team4Name;
	sf::Text team5Name;
	sf::Text team1Value;
	sf::Text team2Value;
	sf::Text team3Value;
	sf::Text team4Value;
	sf::Text team5Value;

	std::string categoryName;

	std::string team1NameStr;
	std::string team2NameStr;
	std::string team3NameStr;
	std::string team4NameStr;
	std::string team5NameStr;
	std::string team1ValueStr;
	std::string team2ValueStr;
	std::string team3ValueStr;
	std::string team4ValueStr;
	std::string team5ValueStr;
public:
	void setCategoryName(std::string x) { categoryName = x; }

	void setTeamName(std::string x, int index) 
	{
		switch (index)
		{
		case 0: team1NameStr = x; break;
		case 1: team2NameStr = x; break;
		case 2: team3NameStr = x; break;
		case 3: team4NameStr = x; break;
		case 4: team5NameStr = x; break;
		}
	}

	void setTeamValue(std::string x, int index) 
	{
		switch (index)
		{
		case 0: team1ValueStr = x; break;
		case 1: team2ValueStr = x; break;
		case 2: team3ValueStr = x; break;
		case 3: team4ValueStr = x; break;
		case 4: team5ValueStr = x; break;
		}
	}

	std::string getCategoryName() { return categoryName; }

	std::string getTeam1NameStr() { return team1NameStr; }
	std::string getTeam2NameStr() { return team2NameStr; }
	std::string getTeam3NameStr() { return team3NameStr; }
	std::string getTeam4NameStr() { return team4NameStr; }
	std::string getTeam5NameStr() { return team5NameStr; }

	std::string getTeam1ValueStr() { return team1ValueStr; }
	std::string getTeam2ValueStr() { return team2ValueStr; }
	std::string getTeam3ValueStr() { return team3ValueStr; }
	std::string getTeam4ValueStr() { return team4ValueStr; }
	std::string getTeam5ValueStr() { return team5ValueStr; }

	sf::RectangleShape& getBox() { return box; }
	sf::Text& getCategoryNameLabel() { return categoryNameLabel; }
	sf::Text& getTeam1Name() { return team1Name; }
	sf::Text& getTeam2Name() { return team2Name; }
	sf::Text& getTeam3Name() { return team3Name; }
	sf::Text& getTeam4Name() { return team4Name; }
	sf::Text& getTeam5Name() { return team5Name; }
	sf::Text& getTeam1Value() { return team1Value; }
	sf::Text& getTeam2Value() { return team2Value; }
	sf::Text& getTeam3Value() { return team3Value; }
	sf::Text& getTeam4Value() { return team4Value; }
	sf::Text& getTeam5Value() { return team5Value; }
}; 