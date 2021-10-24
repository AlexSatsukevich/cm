#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include <cm-lib_global.h>
#include <controllers/idatabasecontroller.h>
#include <controllers/icommandcontroller.h>
#include <controllers/inavigationcontroller.h>
#include <framework/iobjectfactory.h>
#include <models/client.h>
#include <models/clientsearch.h>
#include <rss/rsschannel.h>

namespace cm {
namespace controllers {

class CMLIB_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_welcomeMessage READ welcomeMessage CONSTANT )
    Q_PROPERTY( cm::controllers::IDatabaseController* ui_databaseController READ databaseController CONSTANT )
    Q_PROPERTY( cm::controllers::INavigationController* ui_navigationController READ navigationController CONSTANT )
    Q_PROPERTY( cm::controllers::ICommandController* ui_commandController READ commandController CONSTANT )
    Q_PROPERTY( cm::models::Client* ui_newClient READ newClient CONSTANT )
    Q_PROPERTY( cm::models::ClientSearch* ui_clientSearch READ clientSearch CONSTANT )
    Q_PROPERTY( cm::rss::RssChannel* ui_rssChannel READ rssChannel NOTIFY rssChannelChanged )

public:
    MasterController(QObject *parent, framework::IObjectFactory *objectFactory);
    ~MasterController();

    IDatabaseController* databaseController();
    INavigationController* navigationController();
    ICommandController* commandController();
    const QString& welcomeMessage() const;

    models::Client *newClient();
    models::ClientSearch *clientSearch();
    rss::RssChannel *rssChannel();

signals:
    void rssChannelChanged();

public slots:
    void selectClient(cm::models::Client *client);
    void onRssReplyReceived(int statusCode, QByteArray body);    

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif // MASTERCONTROLLER_H
