#pragma once

class Algoritm
{
	int** net;
	int** way_net;
	char** picture;
	int** source;
	int width;
	int height;
	bool completed;
	int current_number;


	Algoritm(int** field, int width, int height);
	~Algoritm();

	void clean_way_net();
	void transform_way_net();

	int* findWay(int, int,int** = nullptr,  int step = 1);
	
	bool indexValid(int, int);
	bool unvisited(int, int);
	int* NumberInNeighbros(int, int, int);
	void update();

	int* FindNumberCoords_1();
	int* FindNumberCoords_2();
	int* FindNumberCoords_3();
	int* FindNumberCoords_4();
	bool algoritm_1();
	bool algoritm_2();
	bool algoritm_3();
	bool algoritm_4();

	void printPicture();
	void fill_number_one();
	void DrawWays();
	void start_algoritm();
public:
	static void do_algoritm();
};