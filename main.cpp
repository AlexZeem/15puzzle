#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Logic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Logic logic;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("logic", &logic);
    engine.load(QUrl(QStringLiteral("qrc:/res/qml/main.qml")));

    return app.exec();
}
