#include "objectfactory.h"
#include "controllers/databasecontroller.h"
#include "controllers/navigationcontroller.h"
#include "networking/networkaccessmanager.h"
#include "networking/webrequest.h"
#include "controllers/commandcontroller.h"

namespace cm {
namespace framework {

ObjectFactory::ObjectFactory(QObject *parent)
    : IObjectFactory(parent)
{
}

models::Client *ObjectFactory::createClient(QObject *parent) const
{
    return new models::Client(parent);
}

models::ClientSearch *ObjectFactory::createClientSearch(QObject *parent, controllers::IDatabaseController *databaseController) const
{
    return new models::ClientSearch(parent, databaseController);
}

controllers::ICommandController *ObjectFactory::createCommandController(
        QObject *parent,
        controllers::IDatabaseController *databaseController,
        controllers::INavigationController *navigationController,
        models::Client *newClient,
        models::ClientSearch *clientSearch,
        networking::IWebRequest *rssWebRequest) const
{
    return new controllers::CommandController(parent, navigationController, databaseController, newClient, clientSearch, rssWebRequest);
}

controllers::IDatabaseController *ObjectFactory::createDatabaseController(QObject *parent) const
{
    return new controllers::DatabaseController(parent);

}

controllers::INavigationController *ObjectFactory::createNavigationController(QObject *parent) const
{
    return new controllers::NavigationController(parent);
}

networking::INetworkAccessManager *ObjectFactory::createNetworkAccessManager(QObject *parent) const
{
    return new networking::NetworkAccessManager(parent);
}

networking::IWebRequest *ObjectFactory::createWebRequest(QObject *parent, networking::INetworkAccessManager *networkAccessManager, const QUrl &url) const
{
    return new networking::WebRequest(parent, networkAccessManager, url);
}

}
}
