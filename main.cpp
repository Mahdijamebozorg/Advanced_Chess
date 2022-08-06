#include "backend.hpp"
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    app.setOrganizationName("none");

//    app.setWindowIcon(QIcon("icon.png"));

    QQmlApplicationEngine engine;

    BackEnd bknd;

    auto root_contex = engine.rootContext(); //to add backend to root
    root_contex->setContextProperty("bknd", &bknd);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
