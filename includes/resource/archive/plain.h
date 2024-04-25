#ifndef RESSOURCE_ARCHIVE_PLAIN
#define RESSOURCE_ARCHIVE_PLAIN

// STL
#include <filesystem>
#include <utility>

// Network
#include "includes/network/station.h"
#include "includes/network/scheduled_line.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Resource is a namespace used to designate every inormation that come from third party data and used to represent Network data
namespace Resource
{
	/////////////////////////////////////////////////////////////////
	/// @brief Archive represent way of opening global file ressources
	namespace Archive
	{
		////////////////////////////////////////////////////////////
		/// @brief Plain represent plaintext archive with a JSON file that reference other files
		namespace Plaine
		{
			/////////////////////////////////////////////////////////////////////
			/// @brief                    Open a scheduled network ressource by providing the json descriptive file
			/// @param plain_archive_path Path to the JSON file explaining the Scheduled network and referencing the other files
			/// @return                   A pair containing the list of the station and the list of scheduled lines
			std::pair<std::vector<Network::Station>,std::vector<Network::Scheduled_Line>> Parse_Scheduled_Network_Resource(std::filesystem::path && plain_archive_path);
		}// Plaine

	}// Archive

}// Resource

#endif