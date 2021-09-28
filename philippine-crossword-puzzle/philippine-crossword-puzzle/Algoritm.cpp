#include "Algoritm.h"
#include <iostream>

Algoritm::Algoritm(int** field, int width, int height) :net(field),
																		  width(width),
																		  height(height),
																	      completed(false),
	                                                                      current_number(2)
{
	way_net = new int* [width] {0};
	picture = new char* [width] {0};
	for (int i = 0; i < width; ++i)
	{
		way_net[i] = new int[height];
		picture[i] = new char[height];
		for (int j = 0; j < height; ++j)
		{
			picture[i][j] = '0';
		}
	};
	
}
Algoritm::~Algoritm()
{
	for (int i = 0; i < width; ++i)
	{
		delete net[i];
		delete way_net[i];
		delete picture[i];
	}
	delete net;
	delete way_net;
	delete picture;
}
void Algoritm::clean_way_net()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			way_net[i][j] = 0;
		}
	}
}
void Algoritm::printPicture()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << picture[j][i];
		}
		std::cout << std::endl;
	}
}
void Algoritm::do_algoritm()
{
	int w = 0;
	int h = 0;
	int width = 50;
	int height = 50;
	int** field = new int* [width];
	for (int i = 0; i < width; ++i)
	{
		field[i] = new int[height];
	}
	std::cout << "Enter width" << std::endl;
	std::cin >> w;
	if (w <= 2)
	{
		std::cout << "width is incorrect. Try again" << std::endl;
		return;
	}
	std::cout << "Enter height" << std::endl;
	std::cin >> h;
	if (h <= 2)
	{
		std::cout << "height is incorrect. Try again" << std::endl;
		return;
	}
	std::cout << "Enter field" << std::endl;
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			std::cin >> field[j][i];
		}
	}

	Algoritm A(field, w, h);
	A.start_algoritm();
}
void Algoritm::DrawWays()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (way_net[i][j] == 1)
			{
				picture[i][j] = '#';
			}
		}
	}
}
void Algoritm::start_algoritm()
{
	clean_way_net();
	fill_number_one();

	int* start_coords = nullptr;
	start_coords = FindNumberCoords();
	
	transform_way_net();
	
	while (start_coords != nullptr && current_number < width * height)
	{
		int* target_coords = findWay(start_coords[0], start_coords[1], way_net);
		if (target_coords == nullptr)
		{
			std::cout << "unreal to find pair for " << current_number << " with coords x = " << start_coords[0] << " y = " << start_coords[1] << std::endl;
			return;
		}
		way_net[target_coords[0]][target_coords[1]] = 1;
		net[target_coords[0]][target_coords[1]] = 0;

		delete start_coords;
		delete target_coords;

		DrawWays();
		clean_way_net();
		
		start_coords = FindNumberCoords();
		if (start_coords != nullptr)
		{
			transform_way_net();
		}
	}
	printPicture();
}
int* Algoritm::findWay(int x, int y,int**steps, int step)
{
	int* target_coords = nullptr;
	if (!unvisited(x, y))
	{
		return nullptr;
	}
	steps[x][y] = 1;
	if (step > current_number - 1)
	{
		steps[x][y] = 0;
		return nullptr;
	}
	target_coords = NumberInNeighbros(x, y, step);
	if (target_coords != nullptr)
	{
		return target_coords;
	}
	target_coords = findWay(x + 1, y, steps, step + 1);
	if (target_coords != nullptr)
	{
		return target_coords;
	}
	target_coords = findWay(x - 1, y, steps, step + 1);
	if (target_coords != nullptr)
	{
		return target_coords;
	}
	target_coords = findWay(x, y + 1, steps, step + 1);
	if (target_coords != nullptr)
	{
		return target_coords;
	}
	target_coords = findWay(x, y - 1, steps, step + 1);
	if (target_coords != nullptr)
	{
		return target_coords;
	}
	steps[x][y] = 0;
	return nullptr;
}
void Algoritm::transform_way_net()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (net[i][j] == current_number)
			{
				way_net[i][j] = 2;
			}
		}
	}
}
void Algoritm::fill_number_one()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (net[i][j] == 1)
			{
				picture[i][j] = '#';
			}
		}
	}
}
int* Algoritm::FindNumberCoords()
{
	while (current_number < width*height)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (net[i][j] == current_number)
				{
					int* coords = new int[2]{ i,j };
					net[i][j] = 0;
					return coords;
				}
			}
		}
		current_number++;
	}
	return nullptr;
}
bool Algoritm::indexValid(int x, int y)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}
bool Algoritm::unvisited(int x, int y)
{
	if (indexValid(x, y))
	{
		return picture[x][y] == '0' && way_net[x][y] == 0;
	}
	return false;
}
int* Algoritm::NumberInNeighbros(int x, int y, int step)
{
	if (step != current_number - 1)
	{
		return nullptr;
	}
	int* target_coords = new int[2]{ 0 };
	if (indexValid(x - 1, y) && net[x - 1][y] == current_number)
	{
		target_coords[0] = x - 1;
		target_coords[1] = y;
		return target_coords;
	}
	
	if (indexValid(x, y + 1) && net[x][y + 1] == current_number)
	{
		target_coords[0] = x;
		target_coords[1] = y + 1;
		return target_coords;
	}

	if (indexValid(x, y - 1) && net[x][y - 1] == current_number)
	{
		target_coords[0] = x;
		target_coords[1] = y - 1;
		return target_coords;
	}

	if (indexValid(x + 1, y) && net[x + 1][y] == current_number)
	{
		target_coords[0] = x + 1;
		target_coords[1] = y;
		return target_coords;
	}
	return nullptr;
}
;

