#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "common/const.hpp"
#include "Models/MainModel.hpp"

// https://en.wikipedia.org/wiki/RC_algorithm

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<Components::Button> ("Button", 1, 0, "Button", "Button error");
    qmlRegisterType<Model::ViewModel, 1>("ViewModel", 1,0,"Model");
    qmlRegisterUncreatableType<Model::DefaultView>("DefaultView", 1, 0, "DefaultView", "DefaultView error");

    const QUrl url(QStringLiteral("qrc:/UI/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

/*
    **********Cipher**********
    XOR
    Cesier
    Vigenere
    Replacement
    Permutation
    RC2, RC4, RC5, RC6
    SDES, DES, 3DES
    RSA
    AES

    ***Under clarification***
    Blowfish
    Twofush
    Threefish
    CAST
    Camellia
    MARS
    Serpent
    IDEA
    3-WAY
    khufu
    Kuznechik
    SEAL
    WAKE
    CRAB ???
    Salsa20
    Magma(GOST)
    SAFER
    SQUARE

    ************HASH************
    MD2, MD4, MD5, (MD6)
    SHA-1, SHA-2, SHA-3
    SHAKE-128, SHAKE-256
    BLAKE, BLAKE2, (BLAKE3)

    ***********Other***********
    base64
    2->8, 2->10, 2->16
    8->2, 8->10, 8->16
    10->2, 10->8, 10->16
    16->2, 16->8, 16->8
*/
