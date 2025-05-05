#include "ClientServer.hpp"

#include "Logger.hpp"
#include "SessionManager.hpp"

httplib::Client ClientServer::client_("http://192.168.0.25:8080");

bool ClientServer::sendLoginRequest(
    const std::string &email, 
    const std::string &password
)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    Logger::info(
        "HTTP", "sendLoginRequest: SENDING " + stringRequest
    );
    httplib::Result result = 
        client_.Post("/login", stringRequest, "application/json");
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", "sendLoginRequest: RESULT \"" + result->body + "\""
        );
        return true;
    }
    Logger::error(
        "HTTP", "sendLoginRequest: RESULT = \"" + result->body + "\""
    );
    return false;
}

bool ClientServer::sendRegisterRequest(
    const std::string &email,
    const std::string &password
)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    Logger::info(
        "HTTP", "sendRegisterRequest: SENDING " + stringRequest
    );
    httplib::Result result = 
        client_.Post("/register", stringRequest, "application/json");
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", "sendRegisterRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", "sendRegisterRequest: RESULT " + result->body
    );
    return false;
}

bool ClientServer::sendVerifySessionRequest()
{
    std::string email = SessionManager::getSessionEmail();
    if (email == "") 
    {
        Logger::error(
            "APP", "sendVerifySessionRequest: session email IS EMPTY"
        );
        return false;
    }
    Logger::info(
        "HTTP", "sendVerifySessionRequest: SENDING " + email
    );
    httplib::Result result = 
        client_.Get(
            "/session/verify?email=" + email
        );
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", 
            "sendVerifySessionRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", 
        "sendVerifySessionRequest: RESULT " + result->body
    );
    return false;
}

bool ClientServer::sendDeleteSessionRequest()
{
    std::string email = SessionManager::getSessionEmail();
    if (email == "") 
    {
        Logger::error(
            "APP", "sendDeleteSessionRequest: session email IS EMPTY"
        );
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    std::string stringRequest = jsonRequest.dump();
    Logger::info(
        "HTTP", "sendDeleteSessionRequest: SENDING " + stringRequest
    );
    httplib::Result result = 
        client_.Post("/session/delete", stringRequest, "application/json");
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", 
            "sendDeleteSessionRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", 
        "sendDeleteSessionRequest: RESULT " + result->body
    );
    return false;
}

bool ClientServer::sendCreateEventRequest(
    const std::string &title,
    const std::string &place,
    const std::string &date,
    const std::string &time,
    const std::string &description,
    const std::vector<std::string> &gifts
)
{
    if (SessionManager::getSessionEmail() == "") 
    {
        Logger::error("APP", "sendCreateEventRequest: session email IS EMPTY");
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = SessionManager::getSessionEmail();
    jsonRequest["title"] = title;
    jsonRequest["place"] = place;
    jsonRequest["date"] = date;
    jsonRequest["time"] = time;
    jsonRequest["description"] = description;
    jsonRequest["gifts"] = gifts;

    std::string stringRequest = jsonRequest.dump();
    Logger::info("HTTP", "sendCreateEventRequest: SENDING " + stringRequest);

    httplib::Result result = 
        client_.Post(
            "/event/create",
            stringRequest,
            "application/json"
        );
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", "sendCreateEventRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", "sendCreateEventRequest: RESULT " + result->body
    );
    return false;
}

bool ClientServer::sendCreateEventMemberRequest(
    const std::string &inviteCode
)
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::error(
            "APP", "sendCreateEventMemberRequest: session email IS EMPTY"
        );
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["inviteCode"] = inviteCode;

    std::string stringRequest = jsonRequest.dump();
    Logger::info(
        "HTTP", "sendCreateEventMemberRequest: SENDING " + stringRequest
    );
    httplib::Result result = 
        client_.Post(
            "/event/members/create",
            stringRequest,
            "application/json"
        );
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", 
            "sendCreateEventMemberRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", 
        "sendCreateEventMemberRequest: RESULT " + result->body
    );
    return false;
}

bool ClientServer::sendDeleteEventMemberRequest()
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::error(
            "APP", "sendDeleteEventMemberRequest: session email IS EMPTY"
        );
        return false;
    }
    Logger::info(
        "HTTP", "sendDeleteEventMemberRequest: SENDING " + email
    );
    httplib::Result result = 
        client_.Get("/event/members/delete?email=" + email);
    if (result->body == "OK")
    {
        Logger::info(
            "HTTP", 
            "sendDeleteEventMemberRequest: RESULT " + result->body
        );
        return true;
    }
    Logger::error(
        "HTTP", 
        "sendDeleteEventMemberRequest: RESULT " + result->body
    );
    return false;
}

std::vector<std::string> ClientServer::getEventMembers()
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::info("APP", "getEventMembers: session email IS EMPTY ");
        return {};
    }
    Logger::info("HTTP", "getEventMembers: SENDING " + email);
    httplib::Result result = 
        client_.Get("/event/members/get?email=" + email);
    nlohmann::json jsonResponse = nlohmann::json::parse(result->body);
    if (jsonResponse["result"] == false)
    {
        Logger::error(
            "HTTP", "getEventMembers: RESULT " + jsonResponse["result"].dump()
        );
        return {};
    }
    std::vector<std::string> members = jsonResponse["members"];
    Logger::info(
        "HTTP", "getEventMembers: RESULT " + jsonResponse["members"].dump()
    );
    return members;
}

std::vector<std::pair<std::string, std::string>> ClientServer::getEventGifts()
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::error("APP", "getEventGifts: session email IS EMPTY");
        return {};
    }
    Logger::info("HTTP", "getEventGifts: SENDING " + email);
    httplib::Result result = 
        client_.Get("/event/gifts/get?email=" + email);
    nlohmann::json jsonResponse = nlohmann::json::parse(result->body);
    if (jsonResponse["result"] == false)
    {
        Logger::error(
            "HTTP", 
            "getEventGifts: RESULT " + jsonResponse["result"].dump()
        );
        return {};
    }
    std::vector<std::pair<std::string, std::string>> gifts = 
        jsonResponse["gifts"];
    Logger::info(
        "HTTP", 
        "getEventGifts: RESULT " + jsonResponse["result"].dump()
    );
    return gifts;
}


bool ClientServer::sendDeleteEventRequest()
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::error("APP", "sendDeleteEventRequest: session email IS EMPTY");
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    std::string stringRequest = jsonRequest.dump();
    Logger::info("HTTP", "sendDeleteEventRequest: SENDING " + stringRequest);
    httplib::Result result = 
        client_.Post("/event/delete", stringRequest, "application/json");
    if (result->body == "OK")
    {
        Logger::info("HTTP", "sendDeleteEventRequest: RESULT " + result->body);
        return true;
    }
    Logger::error("HTTP", "sendDeleteEventRequest: RESULT " + result->body);
    return false;
}

std::string ClientServer::getInviteCode()
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty())
    {
        Logger::error("APP", "getInviteCode: session email IS EMPTY");
        return "";
    }
    Logger::info("HTTP", "getInviteCode: SENDING " + email);
    httplib::Result result = 
        client_.Get("/event/inviteCode/get?email=" + email);
    if (result->body != "FAIL")
    {
        Logger::info("HTTP", "getInviteCode: RESULT " + result->body);
        return result->body;
    }
    Logger::error("HTTP", "getInviteCode: RESULT " + result->body);
    return "";
}

nlohmann::json ClientServer::getEventInfo()
{
    nlohmann::json jsonResponse;
    std::string email = SessionManager::getSessionEmail();
    if (email.empty()) 
    {
        Logger::error("APP", "getEventInfo: session email IS EMPTY");
        jsonResponse["result"] = false;
        return jsonResponse;
    }
    Logger::info("HTTP", "getEventInfo: SENDING " + email);
    httplib::Result result = client_.Get("/event/info/get?email=" + email);
    jsonResponse = nlohmann::json::parse(result->body);
    if (jsonResponse["result"] == false)
    {
        Logger::error("HTTP", "getEventInfo: RESULT " + jsonResponse.dump());
        return jsonResponse;
    }
    Logger::info("HTTP", "getEventInfo: RESULT " + jsonResponse.dump());
    return jsonResponse;
}

bool ClientServer::sendSelectGiftRequest(const std::string &giftName)
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty())
    {
        Logger::error("APP", "sendSelectGiftRequest: session email IS EMPTY");
        return false;
    }
    if (giftName.empty())
    {
        Logger::error("APP", "sendSelectGiftRequest: gift name IS EMPTY");
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["giftName"] = giftName;
    std::string stringRequest = jsonRequest.dump();
    Logger::info("HTTP", "sendSelectGiftRequest: SENDING " + stringRequest);
    httplib::Result result = 
        client_.Post("/gifts/select", stringRequest, "application/json");
    if (result->body == "FAIL")
    {
        Logger::error("HTTP", "sendSelectGiftRequest: RESULT " + result->body);
        return false;
    }
    Logger::info("HTTP", "sendSelectGiftRequest: RESULT " + result->body);
    return true;
}

bool ClientServer::sendUnselectGiftRequest(const std::string &giftName)
{
    std::string email = SessionManager::getSessionEmail();
    if (email.empty())
    {
        Logger::error("APP", "sendUnselectGiftRequest: session email IS EMPTY");
        return false;
    }
    if (giftName.empty())
    {
        Logger::error("APP", "sendUnselectGiftRequest: gift name IS EMPTY");
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["giftName"] = giftName;
    std::string stringRequest = jsonRequest.dump();
    Logger::info("HTTP", "sendUnselectGiftRequest: SENDING " + stringRequest);
    httplib::Result result = 
        client_.Post("/gifts/unselect", stringRequest, "application/json");
    if (result->body == "FAIL")
    {
        Logger::error("HTTP", "sendUnselectGiftRequest: RESULT " + result->body);
        return false;
    }
    Logger::info("HTTP", "sendUnselectGiftRequest: RESULT " + result->body);
    return true;
}