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

#include "developmentsettingsplugin.h"

#include <QFile>
#include <QFileSystemWatcher>

DevelopmentSettingsPlugin::DevelopmentSettingsPlugin(QObject* parent)
    : m_enabled(false)
{
    QFileSystemWatcher sshdWatcher;
    sshdWatcher.addPath("/usr/bin/sshd");
    connect(&sshdWatcher, &QFileSystemWatcher::fileChanged, this, &DevelopmentSettingsPlugin::onSshDChanged);

    m_enabled = QFile::exists("/usr/bin/sshd");
}

bool DevelopmentSettingsPlugin::enabled()
{
    return m_enabled;
}

void DevelopmentSettingsPlugin::onSshDChanged(QString path)
{
    bool ssdAvaileble = QFile::exists("/usr/bin/sshd");
    if (ssdAvaileble != m_enabled) {
        m_enabled = ssdAvaileble;
        emit pluginChanged(id());
    }
}
