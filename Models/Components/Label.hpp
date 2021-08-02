#pragma once
#include <QObject>

#include <QDebug>

namespace Components {

class LabelInfo
{
    QString m_name;
    QString m_text;
    QString m_placeholderText;
    bool isEditing;
    int m_lineCount;
    int m_maxLength;
    bool m_isReadOnly;
    bool isFilled;
    std::function<bool(const QString&)> m_validate;

public:
    LabelInfo() = default;

    LabelInfo(const QString& name, const QString& text, const QString& placeholderText,
              bool ignoreWhitespaces, int lineCount, bool isReadOnly, std::function<bool(const QString&)> validator)
        : m_name{name}, m_text{text}, m_placeholderText{placeholderText},
          isEditing{ignoreWhitespaces}, m_lineCount{lineCount}, m_isReadOnly{isReadOnly},
          isFilled{false}, m_validate{validator}
    {}

    void setName(const QString& name) { m_name = name; }
    QString name() const { return m_name; }

    void setText(const QString& text) { isFilled = true; m_text = text; }
    QString text() const { return m_text; }

    QString placeholderText() const { return m_placeholderText; }
    void setPlaceholderText(const QString &placeholderText) { m_placeholderText = placeholderText; }

    bool getIsEditing() const { return isEditing; }
    void setIsEditing(bool value) { isEditing = value; }

    int getLineCount() const { return m_lineCount; }
    void setLineCount(int lineCount) { m_lineCount = lineCount; }

    void setValidator(std::function<bool(const QString&)> validate) { m_validate = validate; }
    bool executeValidator(const QString& text) { return m_validate(text); }

    bool getIsReadOnly() const { return m_isReadOnly; }
};


class Label : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString placeholderText READ placeholderText /*NOTIFY*/)
    Q_PROPERTY(bool isEditing READ getIsEditing CONSTANT)
    Q_PROPERTY(int lineCount READ getLineCount CONSTANT)
    Q_PROPERTY(bool isReadOnly READ getIsReadOnly CONSTANT)

    LabelInfo m_info;

signals:
    void textChanged();

public:
    Label(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setData(const LabelInfo& info) { m_info = info; }

    void setName(const QString& name) { m_info.setName(name); }
    QString name() const { return m_info.name(); }

    void setText(const QString& text) { m_info.setText(text); }
    QString text() const { return m_info.text(); }

    QString placeholderText() const { return m_info.placeholderText(); }
    void setPlaceholderText(const QString &placeholderText) { m_info.setPlaceholderText(placeholderText); }

    bool getIsEditing() const { return m_info.getIsEditing(); }
    void setIsEditing(bool value) { m_info.setIsEditing(value); }

    bool getIsReadOnly() const { return m_info.getIsReadOnly(); }

    int getLineCount() const { return m_info.getLineCount(); }
    void setLineCount(int lineCount) { m_info.setLineCount(lineCount); }

    void setValidator(std::function<bool(const QString&)> validate) { m_info.setValidator(validate); }

    Q_INVOKABLE bool validate(const QString& str) { qDebug() << "validate" << str; return m_info.executeValidator(str); }
};

}
