#include <iostream>
#include "Algoritm.h"
using namespace std;

int main()
{
	int w = 0;
	int h = 0;
	unsigned int width = 50;
	unsigned int height = 50;
	int** field = new int* [width];
	for (int i = 0; i < width; ++i)
	{
		field[i] = new int[height];
	}
	std::cout << "Enter width" << std::endl;
	cin >> w;
	std::cout << "Enter height" << std::endl;
	cin >> h;
	std::cout << "Enter field" << std::endl;
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			cin >> field[j][i];
		}
	}
		
	Algoritm A(field, w, h);
	A.start_algoritm();


	return EXIT_SUCCESS;
}