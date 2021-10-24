#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>
#include <framework/command.h>
#include "inavigationcontroller.h"
#include "idatabasecontroller.h"
#include "models/client.h"
#include "models/clientsearch.h"
#include "networking/iwebrequest.h"
#include "controllers/icommandcontroller.h"

namespace cm {
namespace controllers {

class CMLIB_EXPORT CommandController: public ICommandController
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_createClientViewContextCommands READ ui_createClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_findClientViewContextCommands READ ui_findClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_editClientViewContextCommands READ ui_editClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_rssViewContextCommands READ ui_rssViewContextCommands CONSTANT)
public:
    explicit CommandController(QObject* _parent = nullptr,
                               INavigationController* _navigationController = nullptr,
                               IDatabaseController* _databaseController = nullptr,
                               models::Client* _newClient = nullptr,
                               models::ClientSearch* _clientSearch = nullptr,
                               networking::IWebRequest* _rssWebRequest = nullptr);

    ~CommandController();

    QQmlListProperty<framework::Command> ui_createClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_findClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_editClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_rssViewContextCommands() override;

public slots:
    void onCreateClientSaveExecuted() override;
    void onFindClientSearchExecuted() override;
    void onEditClientSaveExecuted() override;
    void onEditClientDeleteExecuted() override;
    void onRssRefreshExecuted() override;

    void setSelectedClient(cm::models::Client*) override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif // COMMANDCONTROLLER_H
