// AOV specific case-generation feature.

#include "aoclient.h"
#include "casegeneratorloader.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const QString CaseGeneratorLoader::CONFIGURATION_FILE = "config/casegenerator.json";

CaseGeneratorLoader::CaseGeneratorLoader() {}

CaseGeneratorLoader::~CaseGeneratorLoader() {}

void CaseGeneratorLoader::loadConfig()
{
    qDebug("Entered");
    QFile config(CONFIGURATION_FILE);
    if (!config.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open file" << CONFIGURATION_FILE
                   << "ErrorString:" << config.errorString();
        return;
    }

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(config.readAll(), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Unable to parse json." << error.errorString();
        return;
    }

    QJsonObject document_body = document.object();
    for (const QString& key : document_body.keys()) {
        QJsonArray prompt_array = document_body[key].toArray();

        QList<CaseGeneratorValue> case_values;
        for (int array_index = 0; array_index < prompt_array.size(); array_index++) {
            QJsonObject prompt_value = prompt_array[array_index].toObject();
            CaseGeneratorValue value;
            value.message = prompt_value["message"].toString();

            if (prompt_value.contains("metadata")) {
                QJsonObject metadata = prompt_value["metadata"].toObject();
                for (const QString& metadata_key : metadata.keys()) {
                    QJsonObject modifier_data = metadata[metadata_key].toObject();
                    ModifierData data;
                    data.placeholder_type = modifier_data["type"].toString();
                    data.max_inserts = modifier_data["iterations"].toInt(0);
                    value.modifiers.insert(metadata_key, data);
                }
            }
            case_values.append(value);
        }
        m_data.insert(key, case_values);
    }
}

void AOClient::cmdCasegen(int argc, QStringList argv)
{
    // Ignore.
}
