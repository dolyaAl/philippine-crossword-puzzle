#pragma once

class Algoritm
{
	int** net;
	int** way_net;
	char** picture;
	int width;
	int height;
	bool completed;
	int current_number;


	Algoritm(int** field, int width, int height);
	void start_algoritm();
	~Algoritm();
	void clean_way_net();
	void DrawWays();
	int* findWay(int, int,int** = nullptr,  int step = 1);
	void transform_way_net();
	void fill_number_one();
	int* FindNumberCoords();
	bool indexValid(int, int);
	bool unvisited(int, int);
	int* NumberInNeighbros(int, int, int);
	void printPicture();
public:
	static void do_algoritm();
};