#pragma once

#include "httplib.h"

class ServerClient
{
public:
    ServerClient();

    void sendRequest();

private:
    httplib::Client client_;
};