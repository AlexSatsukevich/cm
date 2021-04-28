#include "mastercontroller.h"

using namespace cm::models;

namespace cm {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController)
        : masterController(_masterController)
    {
        navigationController = new NavigationController(masterController);
        commandController = new CommandController(masterController);
        newClient = new Client(masterController);
    }

    MasterController* masterController{nullptr};
    NavigationController* navigationController{nullptr};
    CommandController* commandController{nullptr};
    QString welcomeMessage = "Welcome to the Client Management system!";
    Client* newClient{nullptr};
};

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

Client* MasterController::newClient()
{
    return implementation->newClient;
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
