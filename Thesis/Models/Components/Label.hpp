#pragma once
#include <QObject>

namespace Components {

class Label : public QObject
{
    QString m_name;
    QString m_text;
    QString m_placeholderText;
    bool isEditing;
    int m_lineCount;
    std::function<bool(const QString&)> m_validate;

    Q_PROPERTY(QString text READ text WRITE setText /*NOTIFY*/)
    Q_PROPERTY(QString placeholderText READ placeholderText /*NOTIFY*/)
    Q_PROPERTY(QString isEditing READ getIsEditing CONSTANT)
    Q_PROPERTY(QString lineCount READ getLineCount CONSTANT)

public:
    Label(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setName(const QString& name) { m_name = name; }
    QString name() const { return m_name; }

    void setText(const QString& text) { m_text = text; }
    QString text() const { return m_text; }

    QString placeholderText() const { return m_placeholderText; }
    void setPlaceholderText(const QString &placeholderText) { m_placeholderText = placeholderText; }

    bool getIsEditing() const { return isEditing; }
    void setIsEditing(bool value) { isEditing = value; }

    int getLineCount() const { return m_lineCount; }
    void setLineCount(int lineCount) { m_lineCount = lineCount; }

    void setValidator(std::function<bool(const QString&)> validate) { m_validate = validate; }

    Q_INVOKABLE bool validate(const QString& str) { return m_validate(str); }
};

}
