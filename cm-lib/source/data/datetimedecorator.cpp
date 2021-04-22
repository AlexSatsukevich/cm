#include "datetimedecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class DatetimeDecorator::Implementation
{
public:
    Implementation(DatetimeDecorator* _datetimeDecorator,
                   const QDateTime& _value)
        : datetimeDecorator(_datetimeDecorator)
        , value(_value)
    {
    }
    DatetimeDecorator* datetimeDecorator{nullptr};
    QDateTime value;
};

DatetimeDecorator::DatetimeDecorator(Entity* parentEntity,
                                     const QString& key,
                                     const QString& label,
                                     const QDateTime& value)
    : DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
}

DatetimeDecorator::~DatetimeDecorator()
{
}

const QDateTime& DatetimeDecorator::value() const
{
    return implementation->value;
}

const QString DatetimeDecorator::toIso8601String() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString(Qt::ISODate);
    }
}

const QString DatetimeDecorator::toPrettyDateString() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString( "d MMM yyyy" );
    }
}

const QString DatetimeDecorator::toPrettyTimeString() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString( "hh:mm ap" );
    }
}

const QString DatetimeDecorator::toPrettyString() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString( "ddd d MMM yyyy @ HH:mm:ss" );
    }
}

DatetimeDecorator& DatetimeDecorator::setValue(const QDateTime& value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue DatetimeDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void DatetimeDecorator::update(const QJsonObject& _jsonObject)
{
    if (_jsonObject.contains(key())) {
        // setValue(_jsonObject.value(key()).toObject());
    } else {
        setValue(QDateTime());
    }
}

}}
