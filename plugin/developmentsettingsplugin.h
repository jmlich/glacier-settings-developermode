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

#ifndef DEVELOPMENTSETTINGSPLUGIN_H
#define DEVELOPMENTSETTINGSPLUGIN_H

#include <glaciersettingsplugin.h>

class DevelopmentSettingsPlugin : public GlacierSettingsPlugin {
    Q_OBJECT
    Q_INTERFACES(GlacierSettingsPlugin)
    Q_PLUGIN_METADATA(IID "Glacier.SettingsPlugin")
public:
    DevelopmentSettingsPlugin(QObject* parent = nullptr);
    PluginCategory category() { return PluginCategory::Development; }
    QString id() { return "development"; }
    QString title() { return tr("Development"); }
    QString description() { return "Developmet tools and settings"; }
    QString qmlPath() { return "/usr/share/glacier-settings/plugins/development/development.qml"; }
    QString translationPath() { return "/usr/share/glacier-settings/translations/"; }
    QString icon() { return "/usr/share/glacier-settings/plugins/development/development.svg"; }
    bool enabled();

private slots:
    void onSshDChanged(QString path);

private:
    bool m_enabled;
};

#endif // DEVELOPMENTSETTINGSPLUGIN_H
