/*-----------------------------------------------------------------------------
* FILE         : packet.cpp
* DESCRIPTION  : The implemenation file for the packet class. Implements all of
*              : the methods for the packet class. 
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>

#include "packet.h"


using namespace std;

/*-----------------------------------------------------------------------------
* FUNCTION     : packet()
* DESCRIPTION  : The parameterized constructor for the packet class. Sets the
*              : path taken, the current location, and the total weight of the
*              : path
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
packet::packet(int location, int size)
{
  this->path_taken = std::to_string(location);
  this->packet_location = location;
  this->total_weight_taken = size;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : addtopath()
* DESCRIPTION  : Adds the input node_name to the total path string.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
void packet::addtopath(string node_name)
{
  this->path_taken = this->path_taken + node_name;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_location()
* DESCRIPTION  : Returns the current location of the packet.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int packet::get_location()
{
  return this->packet_location;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : increment_total_weight()
* DESCRIPTION  : Adds the input value to the total weight of the path taken.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
void packet::increment_total_weight(int value)
{
  this->total_weight_taken = this->total_weight_taken + value;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_total_weight_taken()
* DESCRIPTION  : Returns the total weight of the path taken.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
int packet::get_total_weight_taken()
{
  return this->total_weight_taken;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : get_path_taken()
* DESCRIPTION  : Returns the complete path taken as a string.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
string packet::get_path_taken()
{
  return this->path_taken;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : set_locaiton()
* DESCRIPTION  : Sets the current location of the packet to the input node_name
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
void packet::set_location(int node_name)
{
  this->packet_location = node_name;
}

/*-----------------------------------------------------------------------------
* FUNCTION     : operator<<()
* DESCRIPTION  : Overloads the insertion operator for the packet class. Prints
*              : all of the relevant information for the packet class in a 
*              : convenient format.
* VERSION      : 1.0
* NOTES        : 
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& os, packet& packet_info)  
{  
    os << "\nPacket Current Location: " << packet_info.get_location() << endl;
    os << "Total Weight Taken: " << packet_info.get_total_weight_taken() << endl;
    os << "Path Taken: " << packet_info.get_path_taken() << endl;

    os << "\n\n";


    return os;  
}
