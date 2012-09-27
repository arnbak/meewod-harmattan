#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include <QCoreApplication>

class Settings : public QSettings
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = 0) : QSettings(QSettings::UserScope,
                                                       QCoreApplication::instance()->organizationName(),
                                                       QCoreApplication::instance()->applicationName(),
                                                       parent) {}

    Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value)
    {
        QSettings::setValue(key, value);
    }

    Q_INVOKABLE inline QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const
    {
        return QSettings::value(key, defaultValue);
    }
};

Q_DECLARE_METATYPE(Settings*)

#endif // SETTINGS_HPP
