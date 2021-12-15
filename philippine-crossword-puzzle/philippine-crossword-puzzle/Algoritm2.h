#pragma once
#include <vector>


using namespace std;

class Graph
{
	typedef unsigned int uint;
	vector <int> g;
	vector <vector<int>> paths;
	int size;
	uint current_num = 0;

	Graph(int size, int num, vector<int> source);

	void find_path_rec(int u, bool* visited, vector<int>& path, uint steps = 0);
	void find_paths(int s);
	void print(vector<int>* path);
	void update_paths_coords(pair<int, int> xy, int big_size);
	bool iValid(int x);
public:
	static vector<vector<int>> get_paths(const int big_size,

		                                 int current_num,

										 vector<int>& source,
 
		                                 pair<int,int> start_coords_p);
};

class Algoritm2
{
public:
	int** source;
	vector<vector<vector<int>>> all_ways;
	vector<vector<vector<int>>> ways;
	vector<int> all_num_coords;
	char** picture;
	int current_num;
	int max_num;
	int* nums_count;
	bool impossible = false;
	int size;
	int pair_count;
	int pic_wid;
	int pic_hei;

	Algoritm2(int** source, int w, int h);
	~Algoritm2();

	int max_number(int** src);
	void feel_nums_count_and_nums_coords();
	//vector<pair<int, int>> cur_nums_around(int x, int y);
	void put_paths(vector<vector<int>>& paths);
	bool is_new(vector<int>& to_test);
	bool differ_with_num_coords(vector<int>& to_test);
	bool in_field(vector<int>& to_test);
	bool coord_in_field(int coord);
	void feel_all_ways();
	void find_picture();
	vector<vector<int>>::iterator find_way(int coord, vector<vector<int>>& all_w_v);
	bool the_only_one(vector<vector<int>>& all_w_v, int to_test);
	void get_the_only_ones(vector<vector<int>>& pic, vector<vector<int>>& all_w_v);
	void find_pic_rec(vector<vector<int>>& pic, 
					  vector<vector<int>>& pic_rec, 
		              vector<vector<int>>& all_w_vec, 
		              vector<vector<int>>::iterator& i, 
		              vector<int>& n_w_n, 
		              vector<int>& num_w_added);
	bool have_same_coords(vector<vector<int>>& selection, vector<int>& test);
	vector<int> current_src(int x, int y);
	void pair_count_f();
};