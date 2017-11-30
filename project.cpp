#include <iostream>
#include <stdlib.h>     /* exit, rand */
#include <fstream> 		//file input
#include <string>
#include <cstdlib>
#include <ctime>


#include "node.cpp"
#include "packet.cpp"


using namespace std;

const int number_of_routers = 10;
node* routers[number_of_routers];

string start_node;
string end_node;

struct path {
  std::string current_path;
  int current_weight;
};


void initial_setup(int argc, char *argv[]);
void compute_paths();
void send_packets(bool keyboard_input);

int main(int argc, char *argv[])
{

	bool keyboard_input;	

	if(argc != 5)
	{
		cout << "\n\nERROR!\n\nPlease ensure you are entering the start node, end node, paths file, and !\n\n";
		exit(0);
	}

	if(stoi(argv[4]) == 0)
	{
		keyboard_input = false;
	}
	else
	{
		keyboard_input = true;
	}

	initial_setup(argc, argv);


	//debug
	// for(int router_number = 0; router_number < number_of_routers; router_number++)
	// {
	// 	cout << routers[router_number];
	// 	cout << "\n";
	// }

	compute_paths();

	send_packets(keyboard_input);



	// //debug
	// printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	// for(int router_number = 0; router_number < number_of_routers; router_number++)
	// {
	// 	cout << routers[router_number];
	// 	cout << "\n";
	// }
	// printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



	return 0;
}


void initial_setup(int argc, char *argv[])
{
	//setup for random values
	srand(time(NULL));


	//test if paths file exists
	ifstream inputfile;
	inputfile.open(argv[3]);

	if(!inputfile.is_open())
	{
		cout << "The file '" << argv[3] << "' cannot be found.\nExiting program!\n";
		exit(1);
	}



	//get the start and end nodes
	start_node = argv[1];
	end_node = argv[2];

	//check if the nodes are out of range
	if(stoi(start_node) < 0 || stoi(start_node) > 9 || stoi(end_node) < 0 || stoi(end_node) > 9)
	{
		cout << "The start or end node are out of range.\nPlease ensure the values are between 0 and 9.\nExiting program!\n";
		exit(1);
	}



	//create all nodes with random failure values
	for(int router_number = 0; router_number < number_of_routers; router_number++)
	{
		//ensure the start node has no failure value
		if(router_number == atoi(argv[1]))
		{
			routers[router_number] = new node(std::to_string(router_number), 0);
		}

		//ensure the end node has no failure value
		else if(router_number == atoi(argv[2]))
		{
			routers[router_number] = new node(std::to_string(router_number), 0);
		}

		//the node is not a start or end node
		else
		{
			//int range from 0 to 80
			int random_value = 0;
			random_value = rand() % 81;

			routers[router_number] = new node(std::to_string(router_number), random_value);
		}
	}




	//used for file input variables
	int temp1 = 0, temp2 = 0, temp3 = 0;
	int start_router = 0;
	int end_router = 0;
	int weight = 0;

	while(!inputfile.eof())
	{
		inputfile >> start_router;
		inputfile >> end_router;
		inputfile >> weight;

		//ensure duplicates are not being added
		if(temp1 != start_router ||
			temp2 != end_router ||
			temp3 != weight)
		{
			//assign previous variables for next check
			temp1 = start_router;
			temp2 = end_router;
			temp3 = weight;

			//debugging on gethering file variables
			//cout << start_router << " " << end_router << " " << weight << endl;

			//add this new path to the graph
			routers[start_router]->add_neighbor(routers[end_router],weight);
		}

	}

	//close the file
	inputfile.close();










	// routers[0]->add_neighbor(routers[1],2);
	// routers[0]->add_neighbor(routers[2],7);

	// routers[1]->add_neighbor(routers[0],2);
	// routers[1]->add_neighbor(routers[3],9);

	// routers[2]->add_neighbor(routers[0],7);
	// routers[2]->add_neighbor(routers[3],5);
	// routers[2]->add_neighbor(routers[5],10);

	// routers[3]->add_neighbor(routers[1],9);
	// routers[3]->add_neighbor(routers[2],5);
	// routers[3]->add_neighbor(routers[4],8);
	// routers[3]->add_neighbor(routers[5],4);

	// routers[4]->add_neighbor(routers[3],8);
	// routers[4]->add_neighbor(routers[6],5);

	// routers[5]->add_neighbor(routers[2],10);
	// routers[5]->add_neighbor(routers[3],4);
	// routers[5]->add_neighbor(routers[6],3);
	// routers[5]->add_neighbor(routers[7],2);

	// routers[6]->add_neighbor(routers[4],5);
	// routers[6]->add_neighbor(routers[5],3);
	// routers[6]->add_neighbor(routers[8],6);

	// routers[7]->add_neighbor(routers[5],2);

	// routers[8]->add_neighbor(routers[6],6);

	// //routers[9]->add_neighbor(routers[1],1);



	//debug
	// for(int router_number = 0; router_number < number_of_routers; router_number++)
	// {
	// 	cout << routers[router_number];
	// 	cout << "\n";
	// }
}


void compute_paths()
{


	for(int current_node = 0; current_node < number_of_routers; current_node++)
	{


		std::vector<path> paths_taken;

		//compute first values
		for(int num_neighbors = 0; num_neighbors < routers[current_node]->get_list_cout(); num_neighbors++)
		{
	      	node* get_node_name = routers[current_node]->get_node_in_list(num_neighbors);

			path temp;
			temp.current_path = std::to_string(current_node) + get_node_name->get_node_name();
			temp.current_weight = routers[current_node]->get_node_in_list_weight(num_neighbors);

			// cout << temp.current_path << ", ";
			// cout << temp.current_weight << "\n";

			paths_taken.push_back(temp);
		}





		//int count = 0;
		//while(count != 0)
		while(!paths_taken.empty())
		{
			//get the current node we are at
			path temp = paths_taken.front();
			char char_current_node = temp.current_path.back();
			int int_current_node = (int)char_current_node - 48;


			//if the node has found the destination
			//add it to our list of paths to take
			if(temp.current_path.find_first_of(end_node) < 99)
			{
				//debugging
				// cout << "HIT   ";
				// cout << temp.current_path << " -- ";
				// cout << temp.current_weight << " -- ";
				// cout << temp.current_path.front()  << "\n\n";

				//get the node index 
				int node_index = temp.current_path.front() - 48;

				//push the value into the class
				routers[node_index]->add_path(temp.current_path, temp.current_weight);
			}

			//if the node has NOT found the destination
			else
			{
				//loop through all neighbors to find best path to end
				for(int num_neighbors = 0; num_neighbors < routers[int_current_node]->get_list_cout(); num_neighbors++)
				{

					node* get_node_name = routers[int_current_node]->get_node_in_list(num_neighbors);

					// //debugging
					// cout << "\n" << temp.current_path << "   " << get_node_name->get_node_name() << "\n";
					// cout << temp.current_path.find(get_node_name->get_node_name());

					//if the the traveling node hasn't gone to this node yet, add it
					if(temp.current_path.find(get_node_name->get_node_name()) == 18446744073709551615)
					{

						path new_path = temp;

						new_path.current_path = temp.current_path + get_node_name->get_node_name();
						new_path.current_weight = temp.current_weight + routers[int_current_node]->get_node_in_list_weight(num_neighbors);
					
						paths_taken.push_back(new_path);
					}
				}
			}

			//remove element from front
			paths_taken.erase(paths_taken.begin());

			//debugging
			//cout << "\n\n\n\n";
			//count++;
		}
	}


}


void send_packets(bool keyboard_input)
{
	std::vector<packet> list_of_packets;

	packet create(stoi(start_node), 0);

	list_of_packets.push_back(create);

	//debugging
	//temp.addtopath("42");
	cout << create;

	int count = 0;

	while(!list_of_packets.empty())
	//while(count != 1)
	{
		//if keyboard input is requested by the user
		if(keyboard_input == true)
		{
			cout << "Please press the 'enter' key to continue the packet sending process\n\n";
			char input;
			input = getchar();
		}


		//iterate on making a node on/off
		for(int router_index = 0; router_index < number_of_routers; router_index++)
		{
			routers[router_index]->compute_on_or_off();
		}
		// routers[1]->set_node_staus(false);
		// routers[2]->set_node_staus(false);



		//get element from the front
		packet temp = list_of_packets.front();

		//remove element from front
		list_of_packets.erase(list_of_packets.begin());




		//debugging
		//cout << routers[temp.get_location()];



		bool use_this_path = true;
		int optimal_path_to_use = -1;
		int current_node_index_location = -1;

		//loop through all the optimal paths
		for(int optimal_path = 0; optimal_path < routers[temp.get_location()]->get_number_of_optimal_paths(); optimal_path++)
		{
			
			use_this_path = true;

			//access the node the packet is at
			routers[temp.get_location()]->get_optimal_path(optimal_path);

			//debugging
			// cout << routers[temp.get_location()]->get_optimal_path(optimal_path);
			// cout << "  " << temp.get_path_taken() << endl;

			//loop through the entire path
			//check if any of these nodes have been accessed before
			for(int string_index = 0; string_index < temp.get_path_taken().size(); string_index++)
			{
				//debugging
				//cout << "HI! --- " << string_index << " --- " << temp.get_path_taken().size() << endl;

				//ignore checking if the path contains the node we are currently at
				if(stoi(routers[temp.get_location()]->get_node_name()) == ( (int)(temp.get_path_taken().at(string_index) - 48) ) )
				{
					//do nothing

					//add index location for future use
					current_node_index_location = routers[temp.get_location()]->get_optimal_path(optimal_path).find(routers[temp.get_location()]->get_node_name());
					// cout << routers[temp.get_location()]->get_node_name() << endl;
					// cout << current_node_index_location << " ----";
					// exit(0);
				}

				//the node has been here, do not go
				else if(routers[temp.get_location()]->get_optimal_path(optimal_path).find(temp.get_path_taken().at(string_index)) != 18446744073709551615)
				{
					use_this_path = false;
					//debugging
					//cout << "AHH   --- " << temp.get_path_taken().at(string_index) << endl;
					break;
				}


			}


			//check if the path taken will result in going to a neighbor that is off
			//if node is off, do not go
			if(use_this_path == true)
			{

				//get the new node the packet is going to
				string add_to_path;
				add_to_path = routers[temp.get_location()]->get_optimal_path(optimal_path).at(current_node_index_location + 1);
				
				// //debugging, the paath interesting in taking
				//cout << add_to_path;

				//loop and check all neighors against the node that is requested to send packet
				for(int neighbor_check = 0; neighbor_check < routers[temp.get_location()]->get_list_cout(); neighbor_check++)
				{
					if(routers[temp.get_location()]->get_node_in_list(neighbor_check)->get_node_name() == add_to_path
						&& routers[temp.get_location()]->get_node_in_list(neighbor_check)->is_node_on() == false)
					{
						use_this_path = false;
						
						// //debugging, has a this node been previously used?
						//cout << "NOO   --- " << add_to_path << endl;
					}
				}
			}
			// if(routers[temp.get_location()]->get_optimal_path(optimal_path).find(temp.get_path_taken().at(string_index))
			// {

			// }


			//use this optimal path and break out of loop
			if(use_this_path == true)
			{
				optimal_path_to_use = optimal_path;
				break;
			}


		}


		//a path has been found
		if(use_this_path == true)
		{
			//debugging on path taken
			//cout << endl << current_node_index_location << "   " <<  routers[temp.get_location()]->get_optimal_path(optimal_path_to_use) << endl;


			//get the new node the packet is going to
			string add_to_path;
			add_to_path = routers[temp.get_location()]->get_optimal_path(optimal_path_to_use).at(current_node_index_location + 1);

			//get weight value of the path taken
			int path_weight;

			//find the neighbor that will be sent to
		    for(int number_of_neighbors = 0; number_of_neighbors < routers[temp.get_location()]->get_list_cout(); number_of_neighbors++)
		    {
		      node* array_print_node = routers[temp.get_location()]->get_node_in_list(number_of_neighbors);

		      //if the name matches, add the weight to the variable
		      if(add_to_path == array_print_node->get_node_name())
		      {
		      	path_weight = routers[temp.get_location()]->get_node_in_list_weight(number_of_neighbors);
		      }
	
		    }






			//add the weight taken to the packet
			temp.increment_total_weight(path_weight);

			//add the node name to the packet
			temp.addtopath(  add_to_path );

			//set packet to new node
			temp.set_location(stoi(add_to_path));


			//if the packet has reached the end, do nothing
			if(temp.get_location() == stoi(end_node))
			{
				//do nothing
			}
			//the packet has not reached the end, add back into vector
			else
			{
				list_of_packets.push_back(temp);
			}
		}
		//a path has not been found due to a node being off
		else
		{
			list_of_packets.push_back(temp);
		}


		//debugging
		cout << temp;
		count++;
	}

}