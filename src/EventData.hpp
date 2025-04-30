#pragma once

#include <string>
#include <vector>

struct EventData
{
    std::string 
        inviteCode, ownerEmail, title, place, date, time, description;
    std::vector<std::pair<std::string, bool>> members;
    std::vector<std::pair<std::string, bool>> gifts;
};