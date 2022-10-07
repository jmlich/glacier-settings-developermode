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

#include "qdbuserror.h"
#include "systemdconnector.h"
#include "userspaceconnector.h"
#include <QCoreApplication>
#include <QObject>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QObject obj;

    SystemDConnector conn;
    UserSpaceConnector uconn(&obj);

    QDBusConnection::systemBus().registerObject("/", &obj);

    if (!QDBusConnection::systemBus().registerService("org.nemomobile.developermode")) {
        qFatal("%s", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    QObject::connect(&conn, &SystemDConnector::sshActiveChanged, &uconn, &UserSpaceConnector::setEnabled);
    QObject::connect(&uconn, &UserSpaceConnector::enabledChanged, &conn, &SystemDConnector::enableDeveloperMode);

    return a.exec();
}
