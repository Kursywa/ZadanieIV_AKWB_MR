#include<iostream>
#include<fstream>
#include<vector>
#include <string>
#include<sstream>
#include<map>
#include<algorithm>
#include<time.h>

using namespace std;

//class initialization
vector<int> read_multiset(string file_name);
string get_file_name();
map<int, int> count_eligible_ncuts(int min, int max);
void check_input(vector<int> multiset, map<int, int> eligible_cuts);
int find_first_element_index(vector<int> multiset);
void find_solution(int first_element_index, int max_map_size, vector<int>& multiset, vector<int>& map,
	vector<int>& final_map, vector<int>& read_from_multiset);
bool check_vertex(vector<int> multiset, vector<int> map);
void print_result(double time, vector<int> final_map);

//global variables
const int MIN_CUT = 1;
const int MAX_CUT = 20;

//main
int main() {
	//file reading
	string file_name = get_file_name();
	vector<int> multiset = read_multiset(file_name);
	//creating a map for eligibile cuts
	map<int, int> eligible_cuts = count_eligible_ncuts(MIN_CUT, MAX_CUT);
	//checking the input
	check_input(multiset, eligible_cuts);
	
	//preparing data structures
	int first_element_index = find_first_element_index(multiset);
	vector<int> map = {};
	vector<int> final_map = {};
	vector<int> read_from_multiset(multiset.size());
	int max_map_size = eligible_cuts[multiset.size()] + 1;

	//finding the solution for this multiset
	clock_t begin = clock();
	find_solution(first_element_index, max_map_size, multiset, map, final_map, read_from_multiset);
	clock_t end = clock();

	//printing the result
	double time = (double)(end - begin) / (double)CLOCKS_PER_SEC;
	print_result(time, final_map);

	//testing
	cout << "Contents of multiset A: ";
	for (auto x : multiset) {
		cout << x << " ";
	}
}

//implementation of methods
vector<int> read_multiset(string file_name) {
	vector<int> multiset;
	ifstream file(file_name);
	string word;

	if (!file.is_open()) {
		cout << "Multiset file cannot be opened" << endl;
	}
	else {
		while (file >> word) {
			stringstream ss(word);
			int number;
			if (ss >> number) {
				multiset.push_back(number);
			}
		}
	}
	file.close();
	return multiset;
}

string get_file_name() {
	string file_name;
	cout << "Provide the name of a file of a multiset: ";
	cin >> file_name;
	file_name += ".txt";
	return file_name;
}

map<int, int> count_eligible_ncuts(int min, int max){ //counting eligible multiset size, based on equation with newton symbol 
	map<int, int> eligible_cuts;

		for (int k = min; k <= max; k++)
		{
			int a = ((k + 2) * (k + 1)) / 2;
			eligible_cuts[a] = k;
		}
	return eligible_cuts;
}

void check_input(vector<int> multiset, map<int,int> eligible_cuts) {
	//rather control flow than exception handling
	if (eligible_cuts.at(multiset.size()) != 0)
	{
		cout << "Map can be created for the provided multiset" << endl;
	}
	else {
		cout << "Map cannot be created for the provided multiset" << endl;
		exit(0);
	}
}

int find_first_element_index(vector<int> multiset) {
	sort(multiset.begin(), multiset.end());
	int first_element = multiset[multiset.size() - 1] - multiset[multiset.size() - 2];
	for (int index_of_first_element = 0; index_of_first_element < multiset.size(); index_of_first_element++) {
		if (multiset[index_of_first_element] == first_element) {
			return index_of_first_element;
		}
	}
}

void find_solution(int first_element_index, int max_map_size, vector<int>& multiset, vector<int>& map,
	vector<int>& final_map, vector<int>& read_from_multiset)
{
	if (map.size() == 0)
	{
		map.push_back(multiset[first_element_index]);
		read_from_multiset[first_element_index] = 1;
	}
	if (map.size() == max_map_size)
	{
		final_map = map;
		return;
	}
	for (int i = 0; i < multiset.size(); i++)
	{
		if (i == first_element_index)
		{
			continue;
		}
		else
		{
			if (read_from_multiset[i] == 1)
			{
				continue;
			}
			map.push_back(multiset[i]);
			bool check = check_vertex(multiset, map);
			read_from_multiset[i] = 1;
			if (check)
			{
				find_solution(first_element_index, max_map_size, multiset, map, final_map, read_from_multiset);
			}
			map.pop_back();
			read_from_multiset[i] = 0;
			if (final_map.size() != 0)
			{
				return;
			}
		}
	}
}


bool check_vertex(vector<int> multiset, vector<int> map)
{
	vector<int> tmp = {};
	int count_ = 0;
	for (int i = 0; i < map.size(); i++) // checking if tmp == multiset
	{
		for (int j = i; j < map.size(); j++)
		{
			count_ += map[j];
			tmp.push_back(count_);
		}
		count_ = 0;
	}

	for (int i = 0; i < multiset.size(); i++)
	{
		if (tmp.empty())
		{
			return true;
		}
		else if (count(tmp.begin(), tmp.end(), multiset[i])) 
		{
			tmp.erase(find(tmp.begin(), tmp.end(), multiset[i])); //deleting elements in tmp added in this tree vertex

		}
	}
	if (tmp.empty())
	{
		return true;
	}
	return false;
}

void print_result(double time, vector<int> final_map) {
	if (final_map.empty()) {
		cout << "Map cannot be found";
		exit(0);
	}
	cout << "Map for the provided instance: ";
	for (int i : final_map) {
		cout << i << " ";
	}
	cout << endl << "Time of processing the algorithm: " << time << " s." << endl;
}