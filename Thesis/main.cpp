#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "MainModel.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Controller::Controller, 1>("MainModel", 1, 0, "MyModel");
    qmlRegisterUncreatableType<Controller::DefaultView>("DefaultView", 1, 0, "DefaultView", "DefaultView eror");
    qmlRegisterUncreatableType<Controller::DefaultViewWithTables>("DefaultViewWithTables", 1, 0, "DefaultViewWithTables", "DefaultViewWithTables eror");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
