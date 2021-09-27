#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <cm-lib_global.h>
#include <models/client.h>

namespace cm {
namespace controllers {

class CMLIB_EXPORT NavigationController : public QObject
{
    Q_OBJECT
public:
    explicit NavigationController(QObject* _parent = nullptr)
        : QObject(_parent)
    {}
signals:
    void goCreateClientView();
    void goDashboardView();
    void goEditClientView(cm::models::Client* client);
    void goFindClientView();
    void goRssView();
};

}
}

#endif // NAVIGATIONCONTROLLER_H
