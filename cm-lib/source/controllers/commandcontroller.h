#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>
#include <framework/command.h>
#include "navigationcontroller.h"
#include "idatabasecontroller.h"
#include "models/client.h"
#include "models/clientsearch.h"

namespace cm {
namespace controllers {

class CMLIB_EXPORT CommandController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_createClientViewContextCommands READ ui_createClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_findClientViewContextCommands READ ui_findClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_editClientViewContextCommands READ ui_editClientViewContextCommands CONSTANT)
public:
    explicit CommandController(QObject* _parent = nullptr,
                               NavigationController* _navigationController = nullptr,
                               IDatabaseController* _databaseController = nullptr,
                               models::Client* _newClient = nullptr,
                               models::ClientSearch* _clientSearch = nullptr);

    ~CommandController();

    QQmlListProperty<framework::Command> ui_createClientViewContextCommands();
    QQmlListProperty<framework::Command> ui_findClientViewContextCommands();
    QQmlListProperty<framework::Command> ui_editClientViewContextCommands();

public slots:
    void onCreateClientSaveExecuted();
    void onFindClientSearchExecuted();
    void onEditClientSaveExecuted();
    void onEditClientDeleteExecuted();

    void setSelectedClient(cm::models::Client*);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif // COMMANDCONTROLLER_H
