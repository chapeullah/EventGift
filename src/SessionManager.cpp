#include "SessionManager.h"

void SessionManager::createSession(const std::string &email)
{
    std::ofstream file(".session");
    file << email;
}

std::time_t SessionManager::getSessionExpirationTime()
{
    return std::time(nullptr) + sessionDuration_.count();
}

std::string SessionManager::getSessionEmail()
{
    std::ifstream file(".session");
    std::string email;
    file >> email;
    return email;
}

void SessionManager::deleteSessionEmail()
{
    std::ofstream file(".session", std::ios::trunc);
}