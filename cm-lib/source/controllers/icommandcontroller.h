#ifndef ICOMMANDCONTROLLER_H
#define ICOMMANDCONTROLLER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>
#include "framework/command.h"
#include "models/client.h"

namespace cm {
namespace controllers {

class CMLIB_EXPORT ICommandController : public QObject
{
    Q_OBJECT
public:
    ICommandController(QObject* parent) : QObject(parent){}
    virtual ~ICommandController(){}

    virtual QQmlListProperty<framework::Command> ui_createClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_findClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_editClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_rssViewContextCommands() = 0;

public slots:
    virtual void onCreateClientSaveExecuted() = 0;
    virtual void onFindClientSearchExecuted() = 0;
    virtual void onEditClientSaveExecuted() = 0;
    virtual void onEditClientDeleteExecuted() = 0;
    virtual void onRssRefreshExecuted() = 0;
    virtual void setSelectedClient(cm::models::Client*) = 0;
};

}} // namespase cm, controller


#endif // ICOMMANDCONTROLLER_H
