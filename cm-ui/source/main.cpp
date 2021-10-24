#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <framework/command.h>
#include <framework/iobjectfactory.h>
#include <framework/objectfactory.h>
#include <controllers/mastercontroller.h>
#include <controllers/commandcontroller.h>
#include <data/datetimedecorator.h>
#include <data/enumeratordecorator.h>
#include <data/intdecorator.h>
#include <rss/rsschannel.h>
#include <rss/rssimage.h>
#include <rss/rssitem.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<cm::controllers::MasterController>("CM", 1, 0, "MasterController", "Controller");
    qmlRegisterUncreatableType<cm::controllers::INavigationController>("CM", 1, 0, "NavigationController", "Interface");
    qmlRegisterUncreatableType<cm::controllers::ICommandController>("CM", 1, 0, "CommandController", "Interface");
    qmlRegisterType<cm::framework::Command>("CM", 1, 0, "Command");
    qmlRegisterType<cm::data::DatetimeDecorator>("CM", 1, 0, "DatetimeDecorator");
    qmlRegisterType<cm::data::EnumeratorDecorator>("CM", 1, 0, "EnumeratorDecorator");
    qmlRegisterType<cm::data::IntDecorator>("CM", 1, 0, "IntDecorator");
    qmlRegisterType<cm::data::StringDecorator>("CM", 1, 0, "StringDecorator");
    qmlRegisterType<cm::models::Address>("CM", 1, 0, "Address");
    qmlRegisterType<cm::models::Appointment>("CM", 1, 0, "Appointment");
    qmlRegisterType<cm::models::Client>("CM", 1, 0, "Client");
    qmlRegisterType<cm::models::Contact>("CM", 1, 0, "Contact");
    qmlRegisterType<cm::models::ClientSearch>("CM", 1, 0, "ClientSearch");
    qmlRegisterType<cm::rss::RssChannel>("CM", 1, 0, "RssChannel");
    qmlRegisterType<cm::rss::RssImage>("CM", 1, 0, "RssImage");
    qmlRegisterType<cm::rss::RssItem>("CM", 1, 0, "RssItem");

    cm::controllers::MasterController masterController(nullptr, new cm::framework::ObjectFactory());

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    auto rootContext = engine.rootContext();
    rootContext->setContextProperty("masterController", &masterController);

    const QUrl url(QStringLiteral("qrc:/views/MasterView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
