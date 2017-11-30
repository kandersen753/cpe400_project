#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
#include <string>

using namespace std;



class node
{



	public:

		//Constructorss
		node(std::string name, int percent_of_failing);

		int get_percent_of_failing();
		int get_list_cout();
		std::string get_node_name();
		node* get_node_in_list(int index_value);
		int get_node_in_list_weight(int index_value);


		int get_number_of_optimal_paths();
		string get_optimal_path(int index);
		int get_optimal_weight(int index);
		bool is_node_on();

		void set_node_staus(bool status);
		void add_path(string path, int weight);
		void add_neighbor(node* neighbor, int weight);

		void compute_on_or_off();


	private:
		//member values

		//keep track of the neighbors and their values
		std::string node_name = "";
		int list_count = 0;
		node* neighbors[9];
		int neighbors_weights[9];


		//keep track of node activated/deactivated
		int percent_of_failing = 0;
		bool node_is_on;



		//store all the path values from the current node to the destination
		struct path {
			std::string current_path;
			int current_weight;
			bool operator<(const path &other_path) const{ return this->current_weight < other_path.current_weight; }
		};
		path temp_path;
		std::vector<path> path_optimal_paths;




};

#endif
