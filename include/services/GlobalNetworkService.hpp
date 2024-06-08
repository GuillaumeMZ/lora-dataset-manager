#pragma once

#include <QNetworkAccessManager>

class GlobalNetworkService
{
    public:
        GlobalNetworkService() = delete;
        GlobalNetworkService(const GlobalNetworkService&) = delete;
        GlobalNetworkService(GlobalNetworkService&&) = delete;
        GlobalNetworkService& operator=(const GlobalNetworkService&) = delete;
        GlobalNetworkService& operator=(GlobalNetworkService&&) = delete;

        static QNetworkAccessManager& get()
        {
            static QNetworkAccessManager networkAccessManager;
            return networkAccessManager;
        }
};