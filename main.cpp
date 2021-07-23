#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "include/controller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Controller::Controller, 1>("MyModel", 1, 0, "Controller");
    qmlRegisterUncreatableType<Controller::DefaultView>("View1", 1, 0, "DefaultView", "just model");
    qmlRegisterUncreatableType<Controller::DefaultViewWithTables>("View2", 1, 0, "DefaultViewWithTables", "just model");

    const QUrl url(QStringLiteral("qrc:/UI/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
