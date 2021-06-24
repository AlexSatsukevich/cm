#include "commandcontroller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;
using namespace cm::models;

namespace cm {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController, NavigationController* _navigationController, IDatabaseController* _databaseController, Client* _newClient, models::ClientSearch* _clientSearch)
        : commandController(_commandController)
        , navigationController(_navigationController)
        , databaseController(_databaseController)
        , newClient(_newClient)
        , clientSearch(_clientSearch)
    {
        Command* createClientSaveCommand = new Command(commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect(createClientSaveCommand, &Command::executed, commandController, &CommandController::onCreateClientSaveExecuted );
        createClientViewContextCommands.append( createClientSaveCommand );

        Command* findClientSearchCommand = new Command( commandController, QChar( 0xf002 ), "Search" );
        QObject::connect( findClientSearchCommand, &Command::executed, commandController, &CommandController::onFindClientSearchExecuted );
        findClientViewContextCommands.append( findClientSearchCommand );

        Command* editClientSaveCommand = new Command( commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect( editClientSaveCommand, &Command::executed, commandController, &CommandController::onEditClientSaveExecuted );
        editClientViewContextCommands.append( editClientSaveCommand );

        Command* editClientDeleteCommand = new Command( commandController, QChar( 0xf235 ), "Delete" );
        QObject::connect( editClientDeleteCommand, &Command::executed, commandController, &CommandController::onEditClientDeleteExecuted );
        editClientViewContextCommands.append( editClientDeleteCommand );
    }

    CommandController* commandController{nullptr};
    QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
    NavigationController* navigationController{nullptr};
    IDatabaseController* databaseController{nullptr};
    Client* newClient{nullptr};
    Client* selectedClient{nullptr};
    ClientSearch* clientSearch{nullptr};
};

CommandController::CommandController(QObject* parent, NavigationController* navigationController, IDatabaseController* databaseController, Client* newClient, models::ClientSearch* clientSearch)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, navigationController, databaseController, newClient, clientSearch));
}

CommandController::~CommandController()
{
}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, &implementation->createClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_findClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, &implementation->findClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, &implementation->editClientViewContextCommands);
}

void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newClient->key(),
                                                  implementation->newClient->id(),
                                                  implementation->newClient->toJson());

    emit implementation->navigationController->goFindClientView();

    qDebug() << "New client saved.";
}

void CommandController::onFindClientSearchExecuted()
{
    qDebug() << "You executed the Search command!";

    implementation->clientSearch->search();
}

void CommandController::onEditClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->updateRow(
                implementation->selectedClient->key(),
                implementation->selectedClient->id(),
                implementation->selectedClient->toJson());

    qDebug() << "Updated client saved.";
}

void CommandController::onEditClientDeleteExecuted()
{
    qDebug() << "You executed the Delete command!";

    implementation->databaseController->deleteRow(implementation->selectedClient->key(), implementation->selectedClient->id());
    implementation->selectedClient = nullptr;

    qDebug() << "Client deleted.";

    implementation->clientSearch->search();
    emit implementation->navigationController->goDashboardView();
}

void CommandController::setSelectedClient(Client *client)
{
    implementation->selectedClient = client;
}

}}
