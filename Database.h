#include <string>
#include <iostream>
#include <sstream>
#include "Team.h"
#include "Standing.h"
#include <msclr/marshal_cppstd.h>
#using <mscorlib.dll>
#using <System.Data.dll>
#using <System.dll>

using namespace System;
using namespace System::Data::OleDb;

ref class Database
{
private:
	static String^ query;
	static std::string* str;
	static std::string* error;
	static OleDbDataReader^ resultsReader;
	static OleDbConnection^ database;
	static OleDbCommand^ command;
public:
	static std::string getNextMatch(std::vector<Team>& teams)
	{
		try {
			database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
			database->Open();
			query = "SELECT TOP 1 * FROM matches WHERE hasPlayed=false ORDER BY matchNumber ASC";
			command = gcnew OleDbCommand(query, database);

			resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			if (resultsReader->HasRows)
			{
				while (resultsReader->Read())
				{
					teams[0].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["red1"]->ToString()));
					teams[1].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["red2"]->ToString()));
					teams[2].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["red3"]->ToString()));
					teams[3].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["blue1"]->ToString()));
					teams[4].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["blue2"]->ToString()));
					teams[5].setNumber(msclr::interop::marshal_as<std::string>(resultsReader["blue3"]->ToString()));
					return msclr::interop::marshal_as<std::string>(resultsReader["matchNumber"]->ToString());
				}
			}
			else
				return "Done";
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}

		resultsReader->Close();
		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}

	static void getTeamMatches(std::vector<Team>& teams)
	{
		try {
			for (int i = 0; i < 6; i++)
			{
				database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
				if (database->State == System::Data::ConnectionState::Closed)
					database->Open();
				query = "SELECT TOP 1 matchNumber FROM " + msclr::interop::marshal_as<String^>(teams[i].getNumber()) + " WHERE hasPlayed=false ORDER BY matchNumber ASC";
				command = gcnew OleDbCommand(query, database);
				resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				while (resultsReader->Read())
				{
					teams[i].setTeamMatch(msclr::interop::marshal_as<std::string>(resultsReader["matchNumber"]->ToString()));
				}
				resultsReader->Close();
			}
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}

		resultsReader->Close();
		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}

	static void updateTeamMatch(Team teamObj)
	{
		try {
			database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();

			// SQL Query
			//		UPDATE [teamNumber] SET hasPlayed=true, autonGear='[Middle, Side, Miss, None, Unset]', autonBalls=[autonBallsValue],
			//			teleopGears=[teleopGearsValue], teleopBalls=[teleopBallsValue], climb=[true, false] WHERE match=[teamMatch]
			query = "UPDATE " + msclr::interop::marshal_as<String^>(teamObj.getNumber()) + " SET hasPlayed = true, autonGear = '";
			query += msclr::interop::marshal_as<String^>(teamObj.getAutonGearStr()) + "', autonBalls = " + msclr::interop::marshal_as<String^>(teamObj.getAutonBallsStr());
			query += ", teleopGears = " + msclr::interop::marshal_as<String^>(teamObj.getTeleopGearsStr()) + ", teleopBalls = " + msclr::interop::marshal_as<String^>(teamObj.getTeleopBallsStr());
			query += ", climb = ";
			if (teamObj.getClimb() != climbEnum::UNDEF)
				query += msclr::interop::marshal_as<String^>(teamObj.getClimbStr());
			else
				query += "false"; 
			query += " WHERE matchNumber = " + msclr::interop::marshal_as<String^>(teamObj.getTeamMatch());
			command = gcnew OleDbCommand(query, database);
			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}
		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}

	static void updateTeamAverages(Team teamObj)
	{
		std::stringstream convert;
		std::string tempStr;
		double autonBalls = 0, teleopBalls = 0, teleopGears = 0, tempDouble = 0, climb = 0;
		double gamesPlayedDouble = 0, autonGearScoredDouble = 0, autonGearAttemptedDouble = 0;

		try {
			database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
			
			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();
			query = "SELECT hasPlayed FROM " + msclr::interop::marshal_as<String^>(teamObj.getNumber()) + " WHERE hasPlayed=true";
			command = gcnew OleDbCommand(query, database);
			resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (resultsReader->Read())
			{
				if (resultsReader["hasPlayed"]->ToString() == "True")
					gamesPlayedDouble++;
			}

			resultsReader->Close();
			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();
			query = "SELECT autonBalls, teleopBalls, teleopGears, climb FROM " + msclr::interop::marshal_as<String^>(teamObj.getNumber()) + " WHERE hasPlayed=true";
			command = gcnew OleDbCommand(query, database);
			resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (resultsReader->Read())
			{
				convert.clear();
				tempStr = msclr::interop::marshal_as<std::string>(resultsReader["autonBalls"]->ToString());
				convert << tempStr;
				convert >> tempDouble;
				autonBalls += tempDouble;

				convert.clear();
				tempStr = msclr::interop::marshal_as<std::string>(resultsReader["teleopBalls"]->ToString());
				convert << tempStr;
				convert >> tempDouble;
				teleopBalls += tempDouble;

				convert.clear();
				tempStr = msclr::interop::marshal_as<std::string>(resultsReader["teleopGears"]->ToString());
				convert << tempStr;
				convert >> tempDouble;
				teleopGears += tempDouble;

				if (resultsReader["climb"]->ToString() == "True")
					climb++;
			}
			resultsReader->Close();
			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();
			query = "SELECT autonGear FROM " + msclr::interop::marshal_as<String^>(teamObj.getNumber()) + " WHERE hasPlayed=true AND (autonGear='Middle' OR autonGear='Side')";
			command = gcnew OleDbCommand(query, database);
			resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (resultsReader->Read())
			{
				if(resultsReader["autonGear"]->ToString() == "Middle" || resultsReader["autonGear"]->ToString() == "Side")
					autonGearScoredDouble++;
			}
			resultsReader->Close();

			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();
			query = "SELECT autonGear FROM " + msclr::interop::marshal_as<String^>(teamObj.getNumber()) + " WHERE hasPlayed=true AND (autonGear='Miss' OR autonGear='Middle' OR autonGear='Side')";
			command = gcnew OleDbCommand(query, database);
			resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (resultsReader->Read())
			{
				if (resultsReader["autonGear"]->ToString() == "Miss" || resultsReader["autonGear"]->ToString() == "Middle" || resultsReader["autonGear"]->ToString() == "Side")
					autonGearAttemptedDouble++;
			}
			resultsReader->Close();

			if (database->State == System::Data::ConnectionState::Closed)
				database->Open();
			// UPDATE totals SET avgAutonBalls = [autonBallsAvg], avgTeleopBalls = [teleopBallsAvg],
			//			avgTeleopGears=[teleopGearsAvg], perClimb=[climbPercentage], perAutonGearTotal=[autonGearTotalPercentage], 
			//			perAutonGearAttempted=[autonGearAttemptedPercentage] WHERE teamNumber=[teamNumber]
			query = "UPDATE totals SET avgAutonBalls=" + autonBalls/gamesPlayedDouble + ", avgTeleopBalls=" + teleopBalls/gamesPlayedDouble;
			query += ", avgTeleopGears=" + teleopGears / gamesPlayedDouble + ", perClimb=" + climb / gamesPlayedDouble + ", perAutonGearTotal=" + autonGearScoredDouble / gamesPlayedDouble;
			query += ", perAutonGearAttempted=";
			if (autonGearAttemptedDouble == 0)
				query += "0";
			else
				query += autonGearScoredDouble / autonGearAttemptedDouble;
			query += " WHERE teamNumber=" + msclr::interop::marshal_as<String^>(teamObj.getNumber());

			command = gcnew OleDbCommand(query, database);
			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}
		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}

	static void closeMatch(std::string match)
	{
		try {
			database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
			database->Open();

			// SQL Query
			//		UPDATE [teamNumber] SET hasPlayed=true, autonGear='[Middle, Side, Miss, None, Unset]', autonBalls=[autonBallsValue],
			//			teleopGears=[teleopGearsValue], teleopBalls=[teleopBallsValue], climb=[true, false] WHERE match=[teamMatch]
			query = "UPDATE matches SET hasPlayed=true WHERE matchNumber=" + msclr::interop::marshal_as<String^>(match);

			command = gcnew OleDbCommand(query, database);
			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}
		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}

	static void getStandingTeams(std::vector<Standing>& standings, std::string totalsColumns[])
	{
		try {
			int j = 0;
			for (int i = 0; i < 6; i++)
			{
				database = gcnew OleDbConnection("PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source=../scout.mdb");
				if(database->State == System::Data::ConnectionState::Closed)
					database->Open();
				query = "SELECT TOP 5 teamNumber, " + msclr::interop::marshal_as<String^>(totalsColumns[i]) + " FROM totals ORDER BY " + msclr::interop::marshal_as<String^>(totalsColumns[i]) + " DESC";
				command = gcnew OleDbCommand(query, database);
				resultsReader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				j = 0;
				while (resultsReader->Read())
				{
					standings[i].setTeamName(msclr::interop::marshal_as<std::string>(resultsReader["teamNumber"]->ToString()), j);
					standings[i].setTeamValue(msclr::interop::marshal_as<std::string>(resultsReader[msclr::interop::marshal_as<String^>(totalsColumns[i])]->ToString()), j);
					j++;
				}
				resultsReader->Close();
			}
		}
		catch (Exception^ ex)
		{
			*error = msclr::interop::marshal_as<std::string>(ex->ToString());
			std::cout << error << std::endl;
		}

		if (database->State == System::Data::ConnectionState::Open)
			database->Close();
	}
};