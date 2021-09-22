#pragma once

class Algoritm
{
	int** net;
	int** way_net;
	char** picture;
	unsigned int width;
	unsigned int height;
	bool completed;
	int current_number;

	void clean_way_net();
	void DrawWays();
	int* findWay(int, int,int** = nullptr,  int step = 1);
	void transform_way_net();
	void fill_first();
	int* FindNumberCoords();
	bool indexValid(int, int);
	bool unvisited(int, int);
	int* NumberInNeighbros(int, int, int);
	void printPicture();
public:
	Algoritm(int** field, unsigned int width, unsigned int height);
	void start_algoritm();
	~Algoritm();
};