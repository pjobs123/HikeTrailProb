// yamlTest1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{

	std::vector<double> speeds;  // This will be used to hold the speeds of each hiker in the group.
	double fastest = 0., ttime = 0.;
	int i, j;
	YAML::Node bridges;
	bridges = YAML::LoadFile("hiker.yaml");
	if (bridges.IsNull())
	{
		std::cerr << "hiker.yaml not found" << std::endl;
		return 0100;
	}

	// Iterate across all bridges.
	for (i = 0; i < bridges.size(); i++)
	{
		// Iterate across each hiker on the bridge.
		for (j = 0; j < bridges[i]["hikers"].size(); j++)
		{
			// Keep track of the fastest hiker in the group.
			fastest = std::max(fastest, bridges[i]["hikers"][j]["speed"].as<double>());
			// Add the hikers on this bridge to the group.
			speeds.push_back(bridges[i]["hikers"][j]["speed"].as<double>());
		}

		// Sum up speeds of all hikers.  This sum adds in the fastest hiker and does not include the fastest hiker return trip.
		for (double iv : speeds)
			ttime += bridges[i]["length"].as<double>() / iv;

		// If there is more than one hiker, corrections need to be made to add the return trips for the fastest hiker.
		if (speeds.size() > 1)
		{
			// Remove fastest hiker time.
			ttime -= (bridges[i]["length"].as<double>() / fastest);
			// Remove return time of fastest hiker for last trip plus one for for the hiker count.
			ttime += (bridges[i]["length"].as<double>() / fastest) * (speeds.size() - 2);
		}
	}

	std::cout << "The total time is: " << ttime << " minutes." << std::endl;

	return 0;
}
