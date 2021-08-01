#pragma once
#include <QObject>

namespace Model {

class ModelWithTables : public QObject
{
    Q_OBJECT

public:
    ModelWithTables(QObject* parent = nullptr)
        : QObject{parent}
    {}
};

} // namespace Model
