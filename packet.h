/*-----------------------------------------------------------------------------
* FILE        	: packet.h
* DESCRIPTION 	: The header file for the packet class. Defines the methods and
*					: attributes for the packet class. We consider these packets
*					: to be somewhat "intelligent" in the sense that they "know"
*              : what path they have taken.
* VERSION     	: 1.0
* NOTES       	: 
-----------------------------------------------------------------------------*/
#ifndef PACKET
#define PACKET

#include <iostream>
#include <vector>
#include <string>

using namespace std;



class packet
{
	public:

		//Constructorss
		packet(int location, int size);

		void addtopath(string node_name);

		void increment_total_weight(int value);
		int get_location();
		int get_total_weight_taken();
		string get_path_taken();

		void set_location(int node_name);


	private:
		//member values

		int packet_location;
		int total_weight_taken;
		string path_taken;
};

#endif
