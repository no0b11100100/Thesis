#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "include/controller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
//    Algorithm::RC4::encode(QString("привет"), "5");
//    Steganography::encode("/home/drago/Desktop/C++/Thesis/Thesis/close1.png", "test text"); // /home/drago/Pictures/byte.png
//    Steganography::decode();
//    Algorithm::SDES::encode("11000010", "10000000");
//    Algorithm::Permutation::encode("пример маршрутной перестановки", "3,1,4,2,5");
//    Algorithm::CaesarCipher::encode("я", 2);
    QQmlApplicationEngine engine;

    qmlRegisterType<Controller::Controller, 1>("MyModel", 1, 0, "Controller");

    const QUrl url(QStringLiteral("qrc:/UI/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
