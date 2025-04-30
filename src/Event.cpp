#include "Event.hpp"

#include "ClientServer.hpp"

#include "nlohmann/json.hpp"

Event::Event()
{
    nlohmann::json jsonResponse = ClientServer::updateEvent();
    if (jsonResponse["result"] == false)
    {
        return;
    }
    eventData_.title =       jsonResponse.value("title", "");
    eventData_.place =       jsonResponse.value("place", "");
    eventData_.date =        jsonResponse.value("date", "");
    eventData_.time =        jsonResponse.value("time", "");
    eventData_.description = jsonResponse.value("description", "");
    eventData_.ownerEmail =  jsonResponse.value("ownerEmail", "");
    eventData_.inviteCode =  jsonResponse.value("inviteCode", "");

}