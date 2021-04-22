#include "enumeratordecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class EnumeratorDecorator::Implementation
{
public:
    Implementation(EnumeratorDecorator* _enumeratorDecorator, const int _value, const std::map<int, QString>& descriptionMapper)
        : enumeratorDecorator(_enumeratorDecorator)
        , descriptionMapper(descriptionMapper)
        , value(_value)
    {
    }

    EnumeratorDecorator* enumeratorDecorator{nullptr};
    const std::map<int, QString>& descriptionMapper;
    int value;
};

EnumeratorDecorator::EnumeratorDecorator(Entity* parentEntity,
                           const QString& key,
                           const QString& label,
                           const int value,
                           const std::map<int, QString>& descriptionMapper)
    : DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value, descriptionMapper));
}

EnumeratorDecorator::~EnumeratorDecorator()
{
}

int EnumeratorDecorator::value() const
{
    return implementation->value;
}

QString EnumeratorDecorator::valueDescription() const
{
    if (implementation->descriptionMapper.find(implementation->value)
            != implementation->descriptionMapper.end()) {
        return implementation->descriptionMapper.at(implementation->value);
    } else {
        return {};
    }
}

EnumeratorDecorator& EnumeratorDecorator::setValue(const int value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void EnumeratorDecorator::update(const QJsonObject& _jsonObject)
{
    if (_jsonObject.contains(key())) {
        setValue(_jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}

}}
