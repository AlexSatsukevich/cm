#include "mastercontroller.h"

#include "networking/networkaccessmanager.h"
#include "networking/webrequest.h"

using namespace cm::models;
using namespace cm::networking;
using namespace cm::rss;


namespace cm {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController, framework::IObjectFactory *_objectFactory)
        : masterController(_masterController)
    {
        databaseController = _objectFactory->createDatabaseController(masterController);
        navigationController = _objectFactory->createNavigationController(masterController);
        newClient = _objectFactory->createClient(masterController);
        clientSearch = _objectFactory->createClientSearch(masterController, databaseController);

        networkAccessManager = _objectFactory->createNetworkAccessManager(masterController);
        rssWebRequest = new WebRequest(masterController, networkAccessManager,
                                       QUrl("http://feeds.bbci.co.uk/news/rss.xml?edition=uk"));

        QObject::connect(rssWebRequest, &WebRequest::requestComplete,
                         masterController, &MasterController::onRssReplyReceived);

        commandController = _objectFactory->createCommandController(
                    masterController,
                    databaseController,
                    navigationController,
                    newClient,
                    clientSearch,
                    rssWebRequest);
    }

    IDatabaseController* databaseController{nullptr};
    MasterController* masterController{nullptr};
    INavigationController* navigationController{nullptr};
    ICommandController* commandController{nullptr};
    QString welcomeMessage = "Welcome to the Client Management system!";
    Client* newClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    INetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* rssWebRequest{nullptr};
    RssChannel* rssChannel{nullptr};
};

MasterController::MasterController(QObject *parent, framework::IObjectFactory *objectFactory)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, objectFactory));
}

MasterController::~MasterController()
{
}

IDatabaseController *MasterController::databaseController()
{
    return implementation->databaseController;
}

Client* MasterController::newClient()
{
    return implementation->newClient;
}

ClientSearch *MasterController::clientSearch()
{
    return implementation->clientSearch;
}

RssChannel *MasterController::rssChannel()
{
    return implementation->rssChannel;
}

void MasterController::selectClient(Client *client)
{
    emit implementation->navigationController->goEditClientView(client);
}

void MasterController::onRssReplyReceived(int statusCode, QByteArray body)
{
    qDebug() << "Received RSS request response code " << statusCode << ":";
    qDebug() << body;

    if(implementation->rssChannel) {
        implementation->rssChannel->deleteLater();
        implementation->rssChannel = nullptr;
        emit rssChannelChanged();
    }

    implementation->rssChannel = RssChannel::fromXml(body, this);
    emit rssChannelChanged();
}

INavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

ICommandController *MasterController::commandController()
{
    return implementation->commandController;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

}}
