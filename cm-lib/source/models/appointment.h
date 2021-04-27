#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QObject>
#include <cm-lib_global.h>
#include <data/stringdecorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIB_EXPORT Appointment : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(cm::data::StringDecorator* ui_name MEMBER name CONSTANT)

public:
    explicit Appointment(QObject* parent = nullptr);
    Appointment(QObject* parent, const QJsonObject& json);

    data::StringDecorator* name{nullptr};
};

}}

#endif // APPOINTMENT_H
