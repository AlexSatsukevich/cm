#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <cm-lib_global.h>
#include <data/stringdecorator.h>
#include <data/enumeratordecorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIB_EXPORT Contact : public data::Entity
{
    enum eContactType {
        Unknown = 0,
        Telephone,
        Email,
        Fax
    };

    Q_OBJECT
    Q_PROPERTY(cm::data::EnumeratorDecorator* ui_contactType MEMBER contactType CONSTANT)
    Q_PROPERTY(cm::data::StringDecorator* ui_contactValue MEMBER contactValue CONSTANT)

public:
    explicit Contact(QObject* parent = nullptr);
    Contact(QObject* parent, const QJsonObject& json);

    std::map<int, QString> contactTypeMapper;

    data::EnumeratorDecorator* contactType{nullptr};
    data::StringDecorator* contactValue{nullptr};
};

}}

#endif // CONTACT_H
