#ifndef RESOURCE_CONFIG_H
#define RESOURCE_CONFIG_H

#include <filesystem>

class DayTemplate;

class Resource_Getter
{

public:
    Resource_Getter(const std::filesystem::path& filesystem_path);
    const std::filesystem::path& Get_Station_File() const noexcept;
    const std::vector<std::pair<std::string, std::vector<std::pair<DayTemplate, std::filesystem::path>>>>& Get_Line_Files() const noexcept;
private:
    std::filesystem::path m_path_to_Station_File;
    std::vector<std::pair<std::string, std::vector<std::pair<DayTemplate, std::filesystem::path>>>> m_line_data;
};

#endif //RESSOURCE_CONFIG_H