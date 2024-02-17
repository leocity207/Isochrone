#ifndef RESSOURCE_ARCHIVE_PLAIN
#define RESSOURCE_ARCHIVE_PLAIN

// STL
#include <filesystem>
#include <utility>

// Network
#include "includes/network/station.h"
#include "includes/network/scheduled_line.h"

namespace Resource
{
	namespace Archive
	{
		namespace Plaine
		{
			std::pair<std::vector<Network::Station>,std::vector<Network::Scheduled_Line>> Parse_Scheduled_Network_Resource(std::filesystem::path && plain_archive_path);
		}// Plaine

	}// Archive

}// Resource

#endif