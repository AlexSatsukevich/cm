#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <QList>
#include <QObject>
#include <QSslError>
#include <networking/inetworkaccessmanager.h>
#include <networking/iwebrequest.h>

namespace cm {
namespace networking {

class WebRequest : public QObject, public IWebRequest
{
    Q_OBJECT
public:
    WebRequest(QObject *parent, INetworkAccessManager* networkAccessManaager, const QUrl& url);
    WebRequest(QObject* parent = nullptr) = delete;
    ~WebRequest();

// IWebRequest interface
public:
    void execute() override;
    bool isBusy() const override;
    void setUrl(const QUrl &url) override;
    QUrl url() const override;

signals:
    void error(QString message);
    void isBusyChanged();
    void requestComplete(int statuseCode, QByteArray body);
    void urlChanged();

private slots:
    void replyDelegate();
    void sslErrorsDelegate(const QList<QSslError>& _errors);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // WEBREQUEST_H
