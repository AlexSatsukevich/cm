#ifndef INAVIGATIONCONTROLLER_H
#define INAVIGATIONCONTROLLER_H

#include <QObject>
#include "cm-lib_global.h"
#include "models/client.h"

namespace cm {
namespace controllers {

class CMLIB_EXPORT INavigationController : public QObject
{
    Q_OBJECT
public:
    INavigationController(QObject *parent = nullptr)
        : QObject(parent) {}
    virtual ~INavigationController() {}

signals:
    void goCreateClientView();
    void goDashboardView();
    void goEditClientView(cm::models::Client* client);
    void goFindClientView();
    void goRssView();
};

}
}

#endif // INAVIGATIONCONTROLLER_H
