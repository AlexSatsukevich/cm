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
    Implementation(CommandController* _commandController, IDatabaseController* _databaseController, Client* _newClient)
        : commandController(_commandController)
        , databaseController(_databaseController)
        , newClient(_newClient)
    {
        Command* createClientSaveCommand = new Command(commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect(createClientSaveCommand, &Command::executed, commandController, &CommandController::onCreateClientSaveExecuted );
        createClientViewContextCommands.append( createClientSaveCommand );
    }

    CommandController* commandController{nullptr};
    QList<Command*> createClientViewContextCommands{};
    IDatabaseController* databaseController{nullptr};
    Client* newClient{nullptr};
};

CommandController::CommandController(QObject* parent, IDatabaseController* databaseController, Client* newClient)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, newClient));
}

CommandController::~CommandController()
{
}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, &implementation->createClientViewContextCommands);
}

void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newClient->key(),
                                                  implementation->newClient->id(),
                                                  implementation->newClient->toJson());
    qDebug() << "New client saved.";
}

}}
