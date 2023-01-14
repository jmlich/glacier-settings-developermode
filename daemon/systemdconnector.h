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

#ifndef SYSTEMDCONNECTOR_H
#define SYSTEMDCONNECTOR_H

#include <QDBusConnection>
#include <QDBusPendingCallWatcher>
#include <QObject>

static const QString s_serviceName = QStringLiteral("org.freedesktop.systemd1");
static const QString s_servicePath = QStringLiteral("/org/freedesktop/systemd1/unit/sshd_2eservice");

static const QString s_unitIface = QStringLiteral("org.freedesktop.systemd1.Unit");

static const QString s_propertiesIface = QStringLiteral("org.freedesktop.DBus.Properties");
static const QString s_propertyActiveState = QStringLiteral("ActiveState");

class SystemDConnector : public QObject {
    Q_OBJECT
public:
    explicit SystemDConnector(QObject* parent = nullptr);

signals:
    void sshActiveChanged(bool active);

public slots:
    void enableDeveloperMode(bool enable);

private slots:
    void propertiesChanged(const QString&, const QVariantMap& properties, const QStringList&);
    void startSShdState(QDBusPendingCallWatcher* watcher);

private:
    QDBusConnection m_systemDBusConnection;

    bool m_sshdActive;
};

#endif // SYSTEMDCONNECTOR_H
