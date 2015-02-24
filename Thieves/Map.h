#include <cstdlib>

class Map
{
public:
	void createMap(int*, int);

private:
	void doSimulationStep();
	void createWalls();
	int countAliveNeighbours(int, int);

	const int iterations = 6;
	const int density = 61;
	int worldSize;
	int *map;
};