/*-----------------------------------------------------------------------------
* FILE         : node.cpp
* DESCRIPTION  : The implementation file for the node class. Implements all of
*              : the node class methods. 
* VERSION      : 1.0
* NOTES        : Includes overloaded insertion operator
-----------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <stdlib.h>     /* exit, rand */
#include <string>
#include <algorithm> //sorting for vectors

#include "node.h"


using namespace std;

/*-----------------------------------------------------------------------------
* FUNCTION     : node()
* DESCRIPTION  : The parameterized constructor for the node class. 
* VERSION      : 1.0
* NOTES        : Sets the probability of failure in the node, the name of the 
*              : node, and activates the node.
-----------------------------------------------------------------------------*/
node::node(std::string name, int percent_of_failing)
{
    this->percent_of_failing = percent_of_failing;
    this->node_name = name;
    node_is_on = true;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_percent_of_failing()
* DESCRIPTION  : Returns the node's probability of failing
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int node::get_percent_of_failing()
{
  return percent_of_failing;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_list_count()
* DESCRIPTION  : Returns the size of the node's list
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int node::get_list_count()
{
  return list_count;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_node_name()
* DESCRIPTION  : Returns the node's name
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
std::string node::get_node_name()
{
  return node_name;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_node_in_list()
* DESCRIPTION  : Returns the node's neighbor via that neighbor's index
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
node* node::get_node_in_list(int index_value)
{
  //bound checking
  if(index_value <= list_count)
  {
    return neighbors[index_value];
  }
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_node_in_list_weight()
* DESCRIPTION  : Returns the weight over the path to the neighbor specified
*              : by the index_value
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int node::get_node_in_list_weight(int index_value)
{
  //bound checking
  if(index_value <= list_count)
  {
    return neighbors_weights[index_value];
  }
}

/*-----------------------------------------------------------------------------
* FUNCTION     : add_path()
* DESCRIPTION  : Adds the input path to the total optimal path
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
* FUNCTION     : add_neighbor()
* DESCRIPTION  : Adds a neighboring node to the list of registered neighbors
*              : and path weight to that neighbor
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
void node::add_neighbor(node* neighbor, int weight)
{
  if(list_count != 9)
  {
    neighbors[list_count] = neighbor;
    neighbors_weights[list_count] = weight;

    list_count++; 
  }
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_number_of_optimal_paths()
* DESCRIPTION  : Returns the number of optimal paths found.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int node::get_number_of_optimal_paths()
{
  return path_optimal_paths.size();
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_optimal_path()
* DESCRIPTION  : Returns an optimal path in the list of optimal paths via the 
*              : input index. 
* VERSION      : 1.0
* NOTES        : Will either return a valid path or the empty string
-----------------------------------------------------------------------------*/
string node::get_optimal_path(int index)
{
  if(index <= path_optimal_paths.size())
  {
    path temp = path_optimal_paths.at(index);
    return temp.current_path;
  }
  return "";
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_optimal_weight()
* DESCRIPTION  : Returns the total weight of the selected optimal path.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int node::get_optimal_weight(int index)
{
  if(index <= path_optimal_paths.size())
  {
    path temp = path_optimal_paths.at(index);
    return temp.current_weight;
  }
  return 0;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : is_node_on()
* DESCRIPTION  : Returns the on/off status of the node.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
bool node::is_node_on()
{
  return node_is_on;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : set_node_status()
* DESCRIPTION  : Sets the node status to the input boolean status
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
void node::set_node_staus(bool status)
{
  node_is_on = status;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : compute_on_or_off()
* DESCRIPTION  : Decides whether the node has failed or not based on a random 
*              : number compared to the node's probability of failure.
* VERSION      : 1.0
* NOTES        : See comments in the implementation for details.
-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
* FUNCTION     : operator<<()
* DESCRIPTION  : The insertion operator overloaded for the node class. Prints
*              : to the selected output stream all of the details of the node 
*              : in a convenient format.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& os, node* print_node)  
{  
    os << "\nNode: " << print_node->get_node_name() << endl;
    os << "Percent Of Failing: " << print_node->get_percent_of_failing() << endl;

    if(print_node->is_node_on() == true)
    {
      os << "Is node on: True" << endl; 
    }
    else
    {
      os << "Is node on: False" << endl;
    }

    for(int number_of_neighbors = 0; number_of_neighbors < print_node->get_list_count(); number_of_neighbors++)
    {
      node* array_print_node = print_node->get_node_in_list(number_of_neighbors);
      
      os << "\tNode: " << array_print_node->get_node_name();
      os << ", Weight: " << print_node->get_node_in_list_weight(number_of_neighbors);
      os << endl;
    }

    if(print_node->get_number_of_optimal_paths() > 0)
    {
      os << "\n\nOptimal Paths:\n";

      for(int optimal_path = 0; optimal_path < print_node->get_number_of_optimal_paths(); optimal_path++)
      {
          os << "\tPath: " << print_node->get_optimal_path(optimal_path);
          os << ", Weight: " << print_node->get_optimal_weight(optimal_path) << endl;
      }
    }

    os << "\n\n";


    return os;  
}
