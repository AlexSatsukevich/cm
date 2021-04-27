#include "contact.h"

using namespace cm::data;

namespace cm {
namespace models {

Contact::Contact(QObject *parent)
    : data::Entity(parent, "contact")
{
    contactTypeMapper = std::map<int, QString>
    {
        { Contact::eContactType::Unknown, "" }
        , { Contact::eContactType::Telephone, "Telephone" }
        , { Contact::eContactType::Email, "Email" }
        , { Contact::eContactType::Fax, "Fax" }
    };

    contactValue = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "contact", "Contact")));
    contactType = static_cast<EnumeratorDecorator*>(addDataItem(
        new EnumeratorDecorator(this, "contactType", "Contact Type", 0, contactTypeMapper)));
}

Contact::Contact(QObject *parent, const QJsonObject &json)
    : Contact(parent)
{
    update(json);
}

}}
