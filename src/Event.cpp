#include "Event.hpp"

#include "ClientServer.hpp"

#include "nlohmann/json.hpp"

#include "Logger.hpp"

Event::Event()
{
    nlohmann::json infoJsonResponse = ClientServer::getEventInfo();
    std::vector<std::string> members = ClientServer::getEventMembers();
    std::vector<std::pair<std::string,std::string>> gifts = 
        ClientServer::getEventGifts();
    if (
        infoJsonResponse["result"] == false || 
        members.empty() ||
        gifts.empty()
    )
    {
        Logger::error(
            "DEBUG", 
            "infoJsonResponse[\"result\"] == false "
               "OR members.empty() OR gifts.empty()"
        );
        return;
    }
    eventData_.title =       infoJsonResponse.value("title", "");
    eventData_.place =       infoJsonResponse.value("place", "");
    eventData_.date =        infoJsonResponse.value("date", "");
    eventData_.time =        infoJsonResponse.value("time", "");
    eventData_.description = infoJsonResponse.value("description", "");
    eventData_.inviteCode =  infoJsonResponse.value("inviteCode", "");
    eventData_.ownerEmail =  infoJsonResponse.value("ownerEmail", "");

    eventData_.members = members;
    eventData_.gifts = gifts;
}