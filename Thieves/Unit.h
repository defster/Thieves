#include <string>

using namespace std;

class Unit
{
public:
	Unit();
	void createUnit(string, int, int, int);
	void createStats();

	string name;
	/*
	string name = "none";
	int race, job;
	int maxhp, hp, maxmp, mp, exp, level;
	int attack, accuracy, defense, evasion;
	int strength = 0, dexterity = 0, agility = 0;
	int vitality = 0, mind = 0, intelligence = 0, charisma = 0;

	int posx = 0, posy = 0;

	int moveStep = 0, moveCounter = 0;
	bool isMoving = false;
	bool initStop = false;
	*/
};