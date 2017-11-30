#include <iostream>
#include <vector>
#include <stdlib.h>     /* exit, rand */
#include <string>
#include <algorithm> //sorting for vectors

#include "node.h"


using namespace std;


node::node(std::string name, int percent_of_failing)
{
    this->percent_of_failing = percent_of_failing;
    this->node_name = name;
    node_is_on = true;
}

int node::get_percent_of_failing()
{
  return percent_of_failing;
}

int node::get_list_cout()
{
  return list_count;
}

std::string node::get_node_name()
{
  return node_name;
}

node* node::get_node_in_list(int index_value)
{
  //bound checking
  if(index_value <= list_count)
  {
    return neighbors[index_value];
  }
}

int node::get_node_in_list_weight(int index_value)
{
  //bound checking
  if(index_value <= list_count)
  {
    return neighbors_weights[index_value];
  }
}


void node::add_path(string path, int weight)
{

  //create path variable for vector
  this->temp_path.current_path = path;
  this->temp_path.current_weight = weight;

  //add variable to vector
  path_optimal_paths.push_back(this->temp_path);


  //sort the list due to new input
  std::sort(path_optimal_paths.begin(), path_optimal_paths.end());

  //clear temp
  this->temp_path.current_path = "";
  this->temp_path.current_weight = 0;


}

void node::add_neighbor(node* neighbor, int weight)
{
  if(list_count != 9)
  {
    neighbors[list_count] = neighbor;
    neighbors_weights[list_count] = weight;


    list_count++; 
  }
}

int node::get_number_of_optimal_paths()
{
  return path_optimal_paths.size();
}

string node::get_optimal_path(int index)
{
  if(index <= path_optimal_paths.size())
  {
    path temp = path_optimal_paths.at(index);
    return temp.current_path;
  }
  return "";
}

int node::get_optimal_weight(int index)
{
  if(index <= path_optimal_paths.size())
  {
    path temp = path_optimal_paths.at(index);
    return temp.current_weight;
  }
  return 0;
}

bool node::is_node_on()
{
  return node_is_on;
}


void node::set_node_staus(bool status)
{
  node_is_on = status;
}

void node::compute_on_or_off()
{

  //int range from 0 to 100
  int random_value = 0;
  random_value = rand() % 101;

  //if our random value is higher than our percent, node hasn't failed
  if(percent_of_failing <= random_value)
  {
    node_is_on = true;
  }
  else
  {
    node_is_on = false;
  }

}


//overload of cout << operator
ostream& operator<<(ostream& os, node* print_node)  
{  
    cout << "\nNode: " << print_node->get_node_name() << endl;
    cout << "Percent Of Failing: " << print_node->get_percent_of_failing() << endl;

    if(print_node->is_node_on() == true)
    {
      cout << "Is node on: True" << endl; 
    }
    else
    {
      cout << "Is node on: False" << endl;
    }



    for(int number_of_neighbors = 0; number_of_neighbors < print_node->get_list_cout(); number_of_neighbors++)
    {
      node* array_print_node = print_node->get_node_in_list(number_of_neighbors);

      //cout << print_node->get_node_in_list(number_of_neighbors);
      //cout << print_node->get_node_in_list(number_of_neighbors)
      
      cout << "\tNode: " << array_print_node->get_node_name();
      cout << ", Weight: " << print_node->get_node_in_list_weight(number_of_neighbors);
      cout << endl;
    }

    if(print_node->get_number_of_optimal_paths() > 0)
    {
      cout << "\n\nOptimal Paths:\n";

      for(int optimal_path = 0; optimal_path < print_node->get_number_of_optimal_paths(); optimal_path++)
      {
          cout << "\tPath: " << print_node->get_optimal_path(optimal_path);
          cout << ", Weight: " << print_node->get_optimal_weight(optimal_path) << endl;
      }
    }

    cout << "\n\n";


    return os;  
}
