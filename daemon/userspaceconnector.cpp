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

#include "userspaceconnector.h"
#include "systemdconnector.h"

#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDebug>

UserSpaceConnector::UserSpaceConnector(QObject* obj)
    : QDBusAbstractAdaptor(obj)
    , m_enabled(false)
{
    QDBusConnection systemConnection = QDBusConnection::systemBus();
    QDBusInterface dbInterface(
        s_serviceName, s_servicePath, s_interfce, systemConnection);

    if (dbInterface.isValid()) {
        if (dbInterface.property("ActiveState").toString() == "active") {
            m_enabled = true;
        }
        qDebug() << dbInterface.property("ActiveState").toString();
    } else {
        qFatal("Systemd interface not found");
    }
}

void UserSpaceConnector::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}
