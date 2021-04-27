#include "appointment.h"

using namespace cm::data;

namespace cm {
namespace models {

Appointment::Appointment(QObject *parent)
    : data::Entity(parent, "appointment")
{
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Nmae")));
}

Appointment::Appointment(QObject *parent, const QJsonObject &json)
    : Appointment(parent)
{
    update(json);
}

}}
