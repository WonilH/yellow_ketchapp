#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtProtobufQtCoreTypes>

int main(int argc, char *argv[])
{
    QtProtobuf::registerProtobufQtCoreTypes();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.loadFromModule("ClientQtQuick", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
