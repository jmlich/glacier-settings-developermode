/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "systemdconnector.h"

#include <QDBusInterface>
#include <QDebug>

SystemDConnector::SystemDConnector(QObject *parent)
    : QObject{parent}
    , m_systemDBusConnection(QDBusConnection::systemBus())
    , m_sshdActive(false)
{
    if(!m_systemDBusConnection.isConnected()) {
        qFatal("Can't connect to system bus");
    }

    QDBusInterface dbInterface(
                s_serviceName
                , s_servicePath
                , s_interfce
                , m_systemDBusConnection);

    if (dbInterface.isValid () ) {
        if(dbInterface.property("ActiveState").toString() == "active") {
            m_sshdActive = true;
        }
    } else {
        qFatal("Systemd interface not found");
    }

    QDBusConnection::systemBus().connect(
                QString(),
                s_servicePath,
                s_propertiesIface,
                "PropertiesChanged",
                this,
                SLOT(propertiesChanged(QString, QVariantMap, QStringList)));
}

void SystemDConnector::enableDeveloperMode(bool enable)
{
    QString action = "Stop";
    if(enable) {
        action = "Start";
    }
    QDBusMessage msg = QDBusMessage::createMethodCall(
                s_serviceName,
                s_servicePath,
                s_unitIface,
                action);

    msg.setArguments({"replace"});
    QDBusConnection::systemBus().call(msg);
}

void SystemDConnector::propertiesChanged(const QString &, const QVariantMap &properties, const QStringList &)
{
    bool activeState = properties.value(s_propertyActiveState, QString()).toString() == "active";
    if(activeState != m_sshdActive) {
        if(activeState) {
            m_sshdActive = true;
        } else {
            m_sshdActive = false;
        }
        emit sshActiveChanged(m_sshdActive);
    }
}
