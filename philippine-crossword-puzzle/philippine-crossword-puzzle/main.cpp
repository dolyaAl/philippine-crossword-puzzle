#include "Algoritm2.h"
#include <iostream>
using namespace std;

bool iValid(int x)
{
	return x >= 0 && x <= 9;
}

int main()
{
	int** source = new int* [50];
	int width, height;
	cin >> width >> height;
	for (int i = 0; i < 50; ++i)
	{
		source[i] = new int[50]{ 0 };
	}
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cin >> source[j][i];
		}
	}
	cout << endl << endl;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cout << source[j][i] << " ";
		}
		cout << endl;
	}

	Algoritm2 a(source, width, height);
	a.feel_all_ways();
	vector<vector<vector<int>>>::iterator i;
	vector<vector<int>> temp1;
	vector<vector<int>>::iterator j;
	vector<int> temp2;
	vector<int>::iterator k;
	for (i = a.all_ways.begin(); i != a.all_ways.end(); ++i)
	{
		temp1 = *i;
		for (j = temp1.begin(); j != temp1.end(); ++j)
		{
			temp2 = *j;
			for (k = temp2.begin(); k != temp2.end(); ++k)
			{
				cout << *k;
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	a.find_picture();
	return EXIT_SUCCESS;
}