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

#include "developermode.h"

#include <QFile>
#include <QDBusInterface>
#include <QFileSystemWatcher>

DeveloperMode::DeveloperMode(QQuickItem* parent)
    : QObject { parent }
    , m_available(QFile::exists("/usr/bin/sshd"))
    , m_enabled(false)
{
    QDBusConnection systemDBusConnection = QDBusConnection::systemBus();

    QFileSystemWatcher sshdWatcher;
    sshdWatcher.addPath("/usr/bin/sshd");
    connect(&sshdWatcher, &QFileSystemWatcher::fileChanged, this, &DeveloperMode::onSshDChanged);

    QDBusInterface dbInterface(
        "org.nemomobile.developermode", "/", "org.nemomobile.developermode", systemDBusConnection);

    if (dbInterface.isValid()) {
        if (dbInterface.property("enabled").toBool()) {
            m_enabled = true;
        }
    } else {
        qWarning("Developermode systemd interface not found");
    }

    QDBusConnection::systemBus().connect(
        QString(),
        "org.nemomobile.developermode",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(propertiesChanged(QString, QVariantMap, QStringList)));
}

void DeveloperMode::setEnabled(bool enable)
{
    if (!m_available) {
        return;
    }

    if (m_enabled != enable) {
        m_enabled = enable;

        propagateEnabled();
        emit enabledChanged();
    }
}

void DeveloperMode::propagateEnabled()
{
    QDBusInterface dbInterface(
        "org.nemomobile.developermode",
        "/",
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus());

    if (!dbInterface.isValid()) {
        qWarning("Developermode systemd interface not found");
        return;
    }
    QDBusMessage reply = dbInterface.call(
        "Set",
        "org.nemomobile.developermode",
        "enabled",
        QVariant::fromValue(QDBusVariant(m_enabled)));

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << Q_FUNC_INFO << "ERROR" << reply.errorMessage() << m_enabled;
    }
}

void DeveloperMode::onSshDChanged(QString path)
{
    bool ssdAvaileble = QFile::exists("/usr/bin/sshd");
    if (ssdAvaileble != m_available) {
        m_available = ssdAvaileble;
        emit availableChanged();
    }
}

void DeveloperMode::propertiesChanged(const QString&, const QVariantMap& properties, const QStringList&)
{
    bool enabled = properties.value("enabled", QString()).toBool();
    if (enabled != m_enabled) {
        m_enabled = enabled;
        enabledChanged();
    }
}
