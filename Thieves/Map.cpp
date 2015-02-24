#include "Map.h"

void Map::createMap(int *map_ptr, int size)
{
	worldSize = size;
	map = map_ptr;

	int index = 0;
	for (int y = 0; y < worldSize; y++)
		for (int x = 0; x < worldSize; x++)
		{
			index = x + (y * worldSize);
			map[index] = 0;
			if (x == 0 || x == worldSize - 1)
				map[index] = 1;
			if (y == 0 || y == worldSize - 1)
				map[index] = 1;
			if (rand() % 100 > density)
				map[index] = 1;
		}
	
	for (int i = 0; i < iterations; i++)
		doSimulationStep();	

	createWalls();
}

void Map::doSimulationStep()
{
	int deathLimit = 3;
	int birthLimit = 4;
	int index = 0;

	//Here's the new map we're going to copy our data into
	int *newmap = new int[worldSize * worldSize];

	for (int y = 0; y < worldSize; y++)
	{
		for (int x = 0; x < worldSize; x++)
		{
			index = x + (y * worldSize);
			//Count up the neighbours
			int nbs = countAliveNeighbours(x, y);
			//If the tile is currently solid
			if (map[index] > 0)
			{
				//See if it should die
				if (nbs < deathLimit)
					newmap[index] = 0;
				//Otherwise keep it solid
				else
					newmap[index] = 1;
			}
			//If the tile is currently empty
			else
			{
				//See if it should become solid
				if (nbs > birthLimit)
					newmap[index] = 1;
				else
					newmap[index] = 0;
			}
		}
	}

	for (int i = 0; i < worldSize * worldSize; i++)
		map[i] = newmap[i];

	delete[] newmap;
}

int Map::countAliveNeighbours(int x, int y)
{
	int count = 0;
	int index = 0;
	int nb_x = 0, nb_y = 0;
	int localIndex = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			nb_x = i + x;
			nb_y = j + y;
			localIndex = nb_x + (nb_y * worldSize);

			if (i == 0 && j == 0)
			{
			}
			//If it's at the edges, consider it to be solid (you can try removing the count = count + 1)
			else if (nb_x <= 0 || nb_y <= 0 || nb_x >= worldSize - 2 || nb_y >= worldSize - 2)
				count++;
			else if (map[localIndex] == 1)
				count++;
		}
	}
	return count;
}

void Map::createWalls()
{
	int index = 0;
	for (int y = 0; y < worldSize; y++)
	{
		for (int x = 0; x < worldSize; x++)
		{ 
			index = x + (y * worldSize);
			//if (map[index] == 1 && map[index] != 2)
			if (map[index] == 1)
			{
				if (y > 0 && y < worldSize - 1 && x > 0 && x < worldSize - 1)
				{
					
					if (map[index + 1] == 0 || map[index + worldSize] == 0)
						map[index] = 2;
					
					if (map[index - 1] == 0 || map[index - worldSize] == 0)
						map[index] = 2;
				}
				if (y == 0) 
				{ 
					if (map[index + worldSize] == 0) map[index] = 2; 
				}
				if (y == worldSize - 1) 
				{ 
					if (map[index - worldSize] == 0) map[index] = 2; 
				}
				if (x == 0) 
				{ 
					if (map[index + 1] == 0) map[index] = 2; 
				}
				if (x == worldSize - 1) 
				{ 
					if (map[index - 1] == 0) map[index] = 2; 
				}
			}
		}
	}
}