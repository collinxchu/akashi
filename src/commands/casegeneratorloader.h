#pragma once

#include <QList>
#include <QMap>
#include <QString>

struct ModifierData
{
    QString placeholder_type;
    int max_inserts;
};

struct CaseGeneratorValue
{
    QString message;
    QMap<QString, ModifierData> modifiers;
};

class CaseGeneratorLoader
{
public:
    static const QString CONFIGURATION_FILE;

    explicit CaseGeneratorLoader();
    virtual ~CaseGeneratorLoader();

    void loadConfig();

private:
    QMap<QString, QList<CaseGeneratorValue>> m_data;
};
