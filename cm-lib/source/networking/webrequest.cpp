#include "webrequest.h"

#include <QMap>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace cm {

namespace networking { // Private Implementation

static const QMap<QNetworkReply::NetworkError, QString> networkErrorMapper = {
    { QNetworkReply::ConnectionRefusedError, "The remote server refused the connection (the server is not accepting requests)."},
    /* ...section shortened in print for brevity...*/
    {QNetworkReply::UnknownServerError, "An unknown error related to the server response was detected."}
};

class WebRequest::Implementation
{

public:
    Implementation(WebRequest* _webRequest,
                   INetworkAccessManager* _networkAccessManager,
                   const QUrl& _url)
        : webRequest(_webRequest)
        , networkAccessManager(_networkAccessManager)
        , url(_url)
    {}

    WebRequest* webRequest{nullptr};
    INetworkAccessManager* networkAccessManager{nullptr};
    QUrl url {};
    QNetworkReply* reply {nullptr};

public:
    bool isBusy() const {
        return isBusy_;
    }
    void setIsBusy(bool value) {
        if (value != isBusy_) {
            isBusy_ = value;
            emit webRequest->isBusyChanged();
        }
    }

private:
    bool isBusy_{false};
};

}

namespace networking {  // Structors

WebRequest::WebRequest(QObject* parent, INetworkAccessManager* networkAccessManager, const QUrl& url)
    : QObject(parent)
    , IWebRequest()
{
    implementation.reset(new WebRequest::Implementation(this, networkAccessManager, url));
}

WebRequest::~WebRequest()
{
}

}

namespace networking { // Methods

void WebRequest::execute()
{
    if(implementation->isBusy()) {
        return;
    }

    if(!implementation->networkAccessManager->isNetworkAccessible()) {
        emit error("Network not accessible");
        return;
    }

    implementation->setIsBusy(true);

    QNetworkRequest request;
    request.setUrl(implementation->url);

    implementation->reply = implementation->networkAccessManager->get(request);

    if(implementation->reply != nullptr) {
        connect(implementation->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
        connect(implementation->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);
    }
}

bool WebRequest::isBusy() const
{
    return implementation->isBusy();
}

void WebRequest::setUrl(const QUrl& url)
{
    if(url != implementation->url) {
        implementation->url = url;
        emit urlChanged();
    }
}

QUrl WebRequest::url() const
{
    return implementation->url;
}

}

namespace networking { // Private Slots

void WebRequest::replyDelegate()
{
    implementation->setIsBusy(false);

    if (implementation->reply == nullptr) {
        emit error("Unexpected error - reply object is null");
        return;
    }

    disconnect(implementation->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
    disconnect(implementation->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);

    auto statusCode = implementation->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    auto responseBody = implementation->reply->readAll();
    auto replyStatus = implementation->reply->error();

    implementation->reply->deleteLater();

    if (replyStatus != QNetworkReply::NoError) {
        emit error(networkErrorMapper[implementation->reply->error()]);
    }

    emit requestComplete(statusCode, responseBody);
}

void WebRequest::sslErrorsDelegate(const QList<QSslError>& errors)
{
    QString sslError;

    for (const auto& error : errors) {
        sslError += error.errorString() + "\n";
    }

    emit error(sslError);
}

}}
