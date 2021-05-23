#pragma once
#include <QStringList>

namespace Description
{

class Description
{

    QStringList m_headerDescription;
    QStringList m_contentDescription;
    QString m_contentDetails;

public:

    void AddHeader(const QString& header)
    {
        m_headerDescription.push_back(header);
    }

    void AddContent(const QString& content)
    {
        m_contentDescription.push_back(content);
    }

    void AddContent()
    {
        m_contentDescription.push_back(m_contentDetails);
        m_contentDetails = "";
    }

    QStringList GetHeaders() const { return m_headerDescription; }
    QStringList GetContents() const { return m_contentDescription; }

    QString& GetContentDetails() { return m_contentDetails; }

    void Clear()
    {
        m_headerDescription = QStringList{};
        m_contentDescription = QStringList{};
    }
};

} // namespace Description
