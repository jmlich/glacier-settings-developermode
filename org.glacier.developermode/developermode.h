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

#ifndef DEVELOPERMODE_H
#define DEVELOPERMODE_H

#include <QDBusConnection>
#include <QObject>
#include <QQuickItem>

class DeveloperMode : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY availableChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit DeveloperMode(QQuickItem* parent = nullptr);

    bool available() { return m_available; }
    bool enabled() { return m_enabled; }

    void setEnabled(bool enable);

signals:
    void availableChanged();
    void enabledChanged();

private slots:
    void onSshDChanged(QString path);
    void propertiesChanged(const QString&, const QVariantMap& properties, const QStringList&);

private:
    bool m_available;
    bool m_enabled;
};

#endif // DEVELOPERMODE_H
