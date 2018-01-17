#pragma once
#include <SFML/Graphics.hpp>

// Enumerator for the autonomous gear.
enum autonGearEnum { MIDDLE = 0, SIDE = 1, MISS = 2, NONE = 3, UNSET = 4 };
// Enumerator for climbing. (UNDEF = unset, but needed another word because UNSET is defined in autonGearEnum.)
enum climbEnum { NO = 0, YES = 1, UNDEF = 2 };

// Enumerator for the state of an individual team.
enum teamState { GAME, EDIT, WAIT };
// Enumerator for the selection in edit mode.
enum editSelection { A_GEAR, A_BALLS, T_GEARS, T_BALLS, CLIMB, NO_EDIT };

class Team
{
private:
	// Team number value
	std::string number;
	// Joystick plugged in: true = yes; false = no
	bool isJoystick;
	// Autonomous gear value
	autonGearEnum autonGear;
	// Match for team (1 through 12)
	std::string teamMatch;
	// Autonomous balls value
	int autonBalls;
	// Teleop gears value
	int teleopGears;
	// Teleop balls value
	int teleopBalls;
	// Climb value
	climbEnum climb;
	// State: GAME = match in progress; EDIT = change values; WAIT = submitted and waiting for next match
	teamState state;
	// Edit selection = auton/teleop balls/gears and climb
	editSelection editSelect;
	// Box to hold the joystick message
	sf::RectangleShape joystickBox;
	// Box for the team
	sf::RectangleShape box;
	// Box to hold the submit/edit message
	sf::RectangleShape submit;
	// Values have been put in the database: true = yes; false = no
	bool saved;

	// SFML text variables that allow for drawing text to the window
	// Team number
	sf::Text title;
	// Auton text
	sf::Text autonLabel;
	sf::Text autonGearLabel;
	sf::Text autonGearValue;
	sf::Text autonBallsLabel;
	sf::Text autonBallsValue;
	// Teleop text
	sf::Text teleopLabel;
	sf::Text teleopGearsLabel;
	sf::Text teleopGearsValue;
	sf::Text teleopBallsLabel;
	sf::Text teleopBallsValue;
	// Climb text
	sf::Text climbLabel;
	sf::Text climbValue;
	// Submit text
	sf::Text submitStatus;
	// Joystick message text
	sf::Text joystickText;
public:
	// Constructor
	// Start by resetting all the variables and setting the text for the text variables
	Team()
	{
		reset();
		joystickText.setString("Joystick Missing");
		autonLabel.setString("Auton");
		autonGearLabel.setString("Gear");
		autonBallsLabel.setString("Balls");
		teleopLabel.setString("Teleop");
		teleopGearsLabel.setString("Gears");
		teleopBallsLabel.setString("Balls");
		climbLabel.setString("Climb");
	} // END of constructor

	// Setters
	void setNumber(std::string x) { number = x; };
	void setJoystick(bool x) { isJoystick = x; }
	void setTeamMatch(std::string x) { teamMatch = x; }
	void setAutonGear(autonGearEnum x) { autonGear = x; }
	void setAutonBalls(int x) { autonBalls = x; }
	void setTeleopGears(int x) { teleopGears = x; }
	void setTeleopBalls(int x) { teleopBalls = x; }
	void setClimb(climbEnum x) { climb = x; }
	void setState(teamState x) { state = x; }
	void setEditSelection(editSelection x) { editSelect = x; }
	void setSaved(bool x) { saved = x; }

	// Getters for auton/teleop gears/balls and climb value text variables
	sf::Text& getAutonGearValue() { return autonGearValue; }
	sf::Text& getAutonBallsValue() { return autonBallsValue; }
	sf::Text& getTeleopGearsValue() { return teleopGearsValue; }
	sf::Text& getTeleopBallsValue() { return teleopBallsValue; }
	sf::Text& getClimbValue() { return climbValue; }

	// Getter for the box
	sf::RectangleShape& getBox() { return box; }
	

	// Getters for title (team number) and labels text variables
	sf::Text& getTitle() { return title; }
	sf::Text& getAutonLabel() { return autonLabel; }
	sf::Text& getAutonGearLabel() { return autonGearLabel; }
	sf::Text& getAutonBallsLabel() { return autonBallsLabel; }
	sf::Text& getTeleopLabel() { return teleopLabel; }
	sf::Text& getTeleopGearsLabel() { return teleopGearsLabel; }
	sf::Text& getTeleopBallsLabel() { return teleopBallsLabel; }
	sf::Text& getClimbLabel() { return climbLabel; }
	
	// Getters for joystick
	sf::RectangleShape& getJoystickBox() { return joystickBox; }
	sf::Text& getJoystickText() { return joystickText; }
	bool getJoystick() { return isJoystick; }

	// Getters for saving/submitting
	sf::RectangleShape& getSubmit() { return submit; }
	sf::Text& getSubmitStatus() { return submitStatus; }
	bool getSaved() { return saved; }

	// Getter for the team state
	teamState getState() { return state; }
	// Getter for the edit selection
	editSelection getEditSelection() { return editSelect; }
	// Getters for the team match
	std::string getTeamMatch() { return teamMatch; }
	
	// Getter for the team number
	std::string getNumber() { return number; }
	
	// Getters for the values for auton/teleop gears/balls and climb
	autonGearEnum getAutonGear() { return autonGear; }
	std::string getAutonGearStr()
	{
		switch (autonGear)
		{
		case autonGearEnum::MIDDLE: return "Middle"; break;
		case autonGearEnum::SIDE: return "Side"; break;
		case autonGearEnum::MISS: return "Miss"; break;
		case autonGearEnum::NONE: return "None"; break;
		case autonGearEnum::UNSET: return "Unset"; break;
		}
	}
	int getAutonBalls() { return autonBalls; }
	std::string getAutonBallsStr() { return std::to_string(autonBalls); }
	int getTeleopGears() { return teleopGears; }
	std::string getTeleopGearsStr() { return std::to_string(teleopGears); }
	int getTeleopBalls() { return teleopBalls; }
	std::string getTeleopBallsStr() { return std::to_string(teleopBalls); }
	climbEnum getClimb() { return climb; }
	std::string getClimbStr()
	{
		switch (climb)
		{
		case climbEnum::YES: return "True"; break;
		case climbEnum::NO: return "False"; break;
		case climbEnum::UNDEF: return "Unset"; break;
		}
	}

	// Reset all the game variables
	void reset()
	{
		// Auton gear back to UNSET
		autonGear = autonGearEnum::UNSET;
		// Balls and teleop gears back to 0
		autonBalls = 0;
		teleopGears = 0;
		teleopBalls = 0;
		// Climb back to UNDEF
		climb = climbEnum::UNDEF;
		// Edit selection to NO_EDIT
		editSelect = NO_EDIT;
	} // END of reset
};