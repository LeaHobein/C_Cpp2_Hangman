#include "person.h"
#include <QProcessEnvironment>
#include <QDebug>

Person::Person() {
    getUsername();
}

std::string Person::getUsername()
{
    QString username = QProcessEnvironment::systemEnvironment().value("USERNAME");
    qDebug() << username;
    return username.toStdString();
}
