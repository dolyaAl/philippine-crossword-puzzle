#include "Algoritm2.h"
#include <iostream>

Graph::Graph(int size, int num, vector<int> source)
{
	current_num = num;
	vector<vector<int>> temp2;
	paths = temp2;
	g = source;
	this->size = size;
}

void Graph::find_path_rec(int u, bool* visited, vector<int>& path, uint steps)
{
	if (steps > current_num - 1)
	{
		return;
	}
	visited[u] = true;
	path.push_back(u);
	if (g[u] == current_num && steps == current_num - 1)
	{
		paths.push_back(path);
	}
	else
	{
		if (iValid(u + 1) && !visited[u + 1])
		{
			find_path_rec(u + 1, visited, path, steps + 1);
		}
		if (iValid(u - 1) && !visited[u - 1])
		{
			find_path_rec(u - 1, visited, path, steps + 1);
		}
		if (iValid(u + size) && !visited[u + size])
		{
			find_path_rec(u + size, visited, path, steps + 1);
		}
		if (iValid(u - size) && !visited[u - size])
		{
			find_path_rec(u - size, visited, path, steps + 1);
		}
	}

	path.pop_back();
	visited[u] = false;
}

void Graph::find_paths(int s)
{
	bool* visited = new bool[size * size]{ 0 };
	vector<int> path;
	for (int i = 0; i < size * size; ++i)
	{
		if (g[i] != 0 && g[i] != current_num)
		{
			visited[i] = true;
		}
	}
	find_path_rec(s, visited, path);
}

void Graph::print(vector<int>* path)
{
	for (auto i = path->begin(); i != path->end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void Graph::update_paths_coords(pair<int, int> xy, int big_size)
{
	vector<vector<int>>::iterator i;
	vector<int>* temp;
	for (i = paths.begin(); i != paths.end(); ++i)
	{
		temp = &*i;
		for (auto j = temp->begin(); j != temp->end(); ++j)
		{
			*j = *j + (xy.first - current_num) +
				(*j / size) * (big_size - size) +
				(xy.second - current_num) * big_size;
		}
	}
}

bool Graph::iValid(int x)
{
	return x >= 0 && x < size * size;
}

vector<vector<int>> Graph::get_paths(const int big_size, int current_num, vector<int>& source, pair<int,int> start_coords_p)
{
	int start_coords = start_coords_p.first + start_coords_p.second * big_size;
	Graph p(big_size, current_num, source);
	p.find_paths(start_coords);
	return p.paths;
}


Algoritm2::Algoritm2(int** source, int w, int h):pic_wid(w), pic_hei(h)
{
	max_num = max_number(source);
	size = 50 + 2 * max_num;
	vector<vector<vector<int>>> temp_a_w(max_num + 1);
	vector<vector<vector<int>>> temp_w(max_num + 1);
	all_ways = temp_a_w;
	ways = temp_w;
	this->source = new int* [size]{ 0 };
	this->picture = new char* [size]{ 0 };
	this->nums_count = new int[max_num + 1]{ 0 };
	for (int i = 0; i < size; ++i)
	{
		this->source[i] = new int[size]{ 0 };
		this->picture[i] = new char [size]{ 0 };
		
	}
	for (int i = max_num; i < size - max_num; ++i)
	{
		for (int j = max_num; j < size - max_num; ++j)
		{
			this->source[i][j] = source[i - max_num][j - max_num];
		}
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			picture[i][j] = '0';
			if (this->source[i][j] == 1)
			{
				picture[i][j] = '#';
			}
		}
	}
	feel_nums_count_and_nums_coords();
	pair_count_f();
	current_num = 2;
}

Algoritm2::~Algoritm2()
{
	for (int i = 0; i < size; ++i)
	{
		delete this->source[i];
		delete this->picture[i];
	}
	delete this->source;
	delete this->picture;
}

int Algoritm2::max_number(int ** src)
{
	int max = 0;
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			if (max <= src[i][j])
			{
				max = src[i][j];
			}
		}
	}
	return max;
}

void Algoritm2::feel_nums_count_and_nums_coords()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (source[i][j] != 0)
			{
				nums_count[source[i][j]]++;
				all_num_coords.push_back(i + j * size);
			}
		}
	}
	for (int i = 2; i <= max_num; ++i)
	{
		if (nums_count[i] % 2 != 0)
		{
			impossible = true;
		}
	}
}

/*vector<pair<int, int>> Algoritm2::cur_nums_around(int x, int y)
{
	vector<pair<int, int>> coords_ar;
	pair<int, int> p;
	int k = 0;
	for (int i = x - (current_num - 1);
		 i < (x + (current_num - 1)) + current_num && k >= 0; ++i)
	{
		i <= x ? ++k : --k;
		for (int j = y - (k - 1); j < y + k; ++j)
		{
			if ((i != x || j != y) && source[i][j] == current_num)
			{
				p.first = i;
				p.second = j;
				coords_ar.push_back(p);
			}
		}
	}
	return coords_ar;
}*/

void Algoritm2::put_paths(vector<vector<int>>& paths)
{
	vector<vector<int>>::iterator i;
	for (i = paths.begin(); i != paths.end(); ++i)
	{
		if (is_new(*i) && in_field(*i) && differ_with_num_coords(*i))
		{
			all_ways[current_num].push_back(*i);
		}
	}

}

bool Algoritm2::is_new(vector<int>& to_test)
{
	vector<vector<int>> cur_paths(all_ways[current_num]);

	vector<int> path(to_test);
	reverse(to_test.begin(), to_test.end());
	vector<int> rev_path(to_test);

	vector<vector<int>>::iterator i;
	for (i = all_ways[current_num].begin(); i != all_ways[current_num].end(); ++i)
	{
		if (*i == path)
		{
			return false;
		}
		if (*i == rev_path)
		{
			return false; 
		}
	}
	return true;
}

void Algoritm2::feel_all_ways()
{
	vector<vector<int>> paths;
	pair<int, int> start;
	vector<int> source_vec;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			source_vec.push_back(source[j][i]);
		}
	}
	while (current_num <= max_num)
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (source[i][j] == current_num)
				{
					start.first = i;
					start.second = j;
					paths = Graph::get_paths(size,
											 current_num,
											 source_vec, 
							                 start);
					put_paths(paths);
				}
			}
		}
		++current_num;
	}
}

vector<int> Algoritm2::current_src(int x, int y)
{
	vector<int> temp;
	for (int i = x - current_num; i < x + current_num + 1; ++i)
	{
		for (int j = y - current_num; j < y + current_num + 1; ++j)
		{
			temp.push_back(source[i][j]);
		}
	}
	return temp;
}

bool Algoritm2::in_field(vector<int>& to_test)
{
	for (auto i = to_test.begin(); i != to_test.end(); ++i)
	{
		if (!coord_in_field(*i))
		{
			return false;
		}
	}
	return true;
}

void Algoritm2::find_picture()
{
	int count = 0;
	vector<vector<int>> pic;
	vector<vector<int>> pic_rec;
	vector<vector<int>> all_w_vec;
	for (int i = 0; i < max_num + 1; ++i)
	{
		for (auto j = all_ways[i].begin(); j != all_ways[i].end(); ++j)
		{
			all_w_vec.push_back(*j);
		}
	}
	vector<vector<int>>::iterator i = all_w_vec.begin();
	int size1 = 0;
	int size2 = 1;
	while (size1 - size2 != 0)
	{
		size1 = pic.size();
		get_the_only_ones(pic, all_w_vec);
		while (i != all_w_vec.end())
		{
			if (have_same_coords(pic, *i))
			{
				i = all_w_vec.erase(i);
				if (i == all_w_vec.end())
				{
					break;
				}
			}
			else
			{
				++i;
			}
		}
		i = all_w_vec.begin();
		size2 = pic.size();
	}

	vector<int> num_ways_need(max_num + 1);
	vector<int> cur_num_ways(max_num + 1);
	vector<int> ways_added(max_num + 1);
	int num = 0;
	while (num != max_num)
	{
		num++;
		for (auto i = pic.begin(); i != pic.end(); ++i)
		{
			if ((*i).size() == num)
			{
				num_ways_need[num]++;
			}
		}
		num_ways_need[num] = nums_count[num] / 2 - num_ways_need[num];
	}
	num = 0;
	/*while (pic.size() != pair_count)
	{
		num++;
		if (num_ways_need[num] != 0)
		{
			for (auto i = all_w_vec.begin(); i != all_w_vec.end(); ++i)
			{
				if ((ways_added[(*i).size()] < num_ways_need[(*i).size()]) && 
					!have_same_coords(pic_rec, *i))
				{
					pic_rec.push_back(*i);
					pic.push_back(*i);
					ways_added[(*i).size()]++;
				}
				for (auto j = all_w_vec.begin(); j != all_w_vec.end(); ++j)
				{
					if (j != i)
					{
						if (!have_same_coords(pic_rec, *j))
						{
							cur_num_ways[(*j).size()]++;
						}
					}
				}
				int counter = 0;
				for (int j = 2; j < max_num + 1; ++j)
				{
					if (cur_num_ways[j] + ways_added[j] < num_ways_need[j])
					{
						++counter;
					}
				}
				if (counter != 0)
				{
					if (pic_rec.size() == 0)
					{
						i = all_w_vec.erase(i);
					}
					pic_rec.pop_back();
					pic.pop_back();
				}
				if (i == all_w_vec.end())
				{
					break;
				}
				for (int j = 0; j < max_num + 1; ++j)
				{
					cur_num_ways[j] = 0;
				}
			}
		}
	}*/

	vector<vector<int>>::iterator k = all_w_vec.begin();
	for (auto i = all_w_vec.begin(); i != all_w_vec.end() && (*i).size() == (*k).size(); ++i)
	{
		if (pic.size() != pair_count)
		{
			find_pic_rec(pic, pic_rec, all_w_vec, i, num_ways_need, ways_added);
		}
	}


	for (auto i = pic.begin(); i != pic.end(); ++i)
	{
		for (auto j = (*i).begin(); j != (*i).end(); ++j)
		{
			picture[*j % size][*j / size] = '#';
		}
	}
	for (int j = max_num; j < max_num + pic_hei; ++j)
	{
		for (int i = max_num; i < max_num + pic_wid; ++i)
		{
			cout << picture[i][j];
		}
		cout << endl;
	}
}

void Algoritm2::find_pic_rec(vector<vector<int>>& pic,
							 vector<vector<int>>& pic_rec,
							 vector<vector<int>>& all_w_vec, 
							 vector<vector<int>>::iterator& i, 
							 vector<int>& num_w_need,
							 vector<int>& num_w_added)
{
	if (i == all_w_vec.end())
	{
		return;
	}
	pic_rec.push_back(*i);
	num_w_added[(*i).size()]++;
	
	if (pic_rec.size() == pair_count - pic.size())
	{
		if (pic.size() != pair_count)
		{
			for (auto j = pic_rec.begin(); j != pic_rec.end(); ++j)
			{
				pic.push_back(*j);
			}
		}
		return;
	}
	else
	{
		for (auto j = all_w_vec.begin(); j != all_w_vec.end() && pic.size() != pair_count; ++j)
		{
			if (num_w_added[(*j).size()] < num_w_need[(*j).size()])
			{
				if (!have_same_coords(pic_rec, *j))
				{
					find_pic_rec(pic, pic_rec, all_w_vec, j, num_w_need, num_w_added);
				}
			}
		}
	}
	pic_rec.pop_back();
	num_w_added[(*i).size()]--;
}

bool Algoritm2::the_only_one(vector<vector<int>>& all_w_v, int coord)
{
	int first = coord;
	int temp1 = 0;
	int temp2 = 0;
	int count = 0;
	
	for (auto i = all_w_v.begin(); i != all_w_v.end(); ++i)
	{
		temp1 = (*i).front();
		temp2 = (*i).back();
		if (temp1 == first || temp2 == first)
		{
			count++;
		}
	}
	return count == 1;
}

vector<vector<int>>::iterator Algoritm2::find_way(int coord, vector<vector<int>>& all_w_v)
{
	vector<vector<int>>::iterator k = all_w_v.end();
	for (auto i = all_w_v.begin(); i != all_w_v.end(); ++i)
	{
		if ((*i).front() == coord)
		{
			return i;
		}
		else if((*i).back() == coord)
		{
			return i;
		}
	}
	return k;
}

void Algoritm2::get_the_only_ones(vector<vector<int>>& pic, vector<vector<int>>& all_w)
{
	vector<vector<int>>::iterator i_temp;
	vector<int> temp;
	int counter = 0;
	for (auto i = all_num_coords.begin(); i != all_num_coords.end(); ++i)
	{
		if (the_only_one(all_w, *i))
		{
			i_temp = find_way(*i, all_w);
			if (i_temp != all_w.end())
			{
				temp = *i_temp;
				counter = 0;
				for (auto i = pic.begin(); i != pic.end(); ++i)
				{
					if (temp == *i)
					{
						counter++;
					}
				}
				if (counter == 0)
				{
					pic.push_back(temp);
				}
			}
		}
	}
}

void Algoritm2::pair_count_f()
{
	for (int i = 2; i < max_num + 1; ++i)
	{
		pair_count += nums_count[i] / 2;
	}
}

bool Algoritm2::coord_in_field(int coord)
{
	int x = coord % size;
	int y = coord / size;

	return (x >= max_num && x < pic_wid + max_num) &&
		   (y >= max_num && y < pic_hei + max_num);
}

bool Algoritm2::differ_with_num_coords(vector<int>& to_test)
{
	for (auto j = all_num_coords.begin(); j != all_num_coords.end(); ++j)
	{
		for (auto k = to_test.begin() + 1; k != to_test.end() - 1; ++k)
		{
			if (*k == *j)
			{
				return false;
			}
		}
	}
	return true;
}

bool Algoritm2::have_same_coords(vector<vector<int>>& selection, 
	                             vector<int>& test)
{

	for (auto i = selection.begin(); i != selection.end(); ++i)
	{
		for (auto j = (*i).begin(); j != (*i).end(); ++j)
		{
			for (auto k = test.begin(); k != test.end(); ++k)
			{
				if (*k == *j)
				{
					return true;
				}
			}
		}
	}
	return false;
}


