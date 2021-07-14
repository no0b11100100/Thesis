#pragma once
#include <QString>
#include <QDebug>

#include <memory>


namespace Controller
{

class DefaultView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text CONSTANT)
public:
    DefaultView(QObject* parent = nullptr)
        : QObject{parent}
    {}

    QString text() { return QString("DefaultView"); }
};

class DefaultViewWithTables : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text CONSTANT)
public:
    DefaultViewWithTables(QObject* parent = nullptr)
        : QObject{parent}
    {}

    QString text() { return QString("DefaultViewWithTables"); }
};

class Controller : public QObject {
    Q_OBJECT

    std::unique_ptr<QObject> m_view;
    Q_PROPERTY(QObject* view READ view NOTIFY viewChanged)

    template <typename Dest, typename Src>
    bool cast(Src* src){
      if(typeid(*src) == typeid(Dest)){
        return true;
      }
      return false;
    }

signals:
    void viewChanged();
public:
    Controller(QObject* parent = nullptr)
        : QObject{parent},
          m_view{ std::make_unique<DefaultViewWithTables>(parent)}
    {}

    QObject* view() {
        return m_view.get();
    }

    Q_INVOKABLE void trigger() {
        qDebug() << "trigger";
        if(cast<DefaultView>(m_view.get()))
        {
            qDebug() << "trigger 1";
            m_view.reset(new DefaultViewWithTables(this));
        } else if(cast<DefaultViewWithTables>(m_view.get()))
        {
            qDebug() << "trigger 2";
            m_view.reset(new DefaultView(this));
        }
        emit viewChanged();
    }
};

} // namespace Controller
