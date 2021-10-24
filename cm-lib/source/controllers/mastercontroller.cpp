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
    Implementation(MasterController* _masterController)
        : masterController(_masterController)
    {
        databaseController = new DatabaseController(masterController);
        navigationController = new NavigationController(masterController);
        newClient = new Client(masterController);
        clientSearch = new ClientSearch(masterController, databaseController);        

        networkAccessManager = new NetworkAccessManager(masterController);
        rssWebRequest = new WebRequest(masterController, networkAccessManager,
                                       QUrl("http://feeds.bbci.co.uk/news/rss.xml?edition=uk"));

        QObject::connect(rssWebRequest, &WebRequest::requestComplete,
                         masterController, &MasterController::onRssReplyReceived);

        commandController = new CommandController(
                    masterController,
                    navigationController,
                    databaseController,
                    newClient,
                    clientSearch,
                    rssWebRequest);
    }

    DatabaseController* databaseController{nullptr};
    MasterController* masterController{nullptr};
    NavigationController* navigationController{nullptr};
    CommandController* commandController{nullptr};
    QString welcomeMessage = "Welcome to the Client Management system!";
    Client* newClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    NetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* rssWebRequest{nullptr};
    RssChannel* rssChannel{nullptr};
};

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

DatabaseController *MasterController::databaseController()
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

NavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

CommandController *MasterController::commandController()
{
    return implementation->commandController;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

}}
