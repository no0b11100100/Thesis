#pragma once
#include <QObject>

class Details : public QObject {
    Q_OBJECT
public:
    Details(QObject* parent = nullptr)
        : QObject{parent}
    {}
};
