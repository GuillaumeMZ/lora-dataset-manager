#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "viewmodels/GrabberViewModel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication _(argc, argv);

	QQmlApplicationEngine engine;
	qmlRegisterType<GrabberViewModel>("LDM", 1, 0, "GrabberViewModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return QGuiApplication::exec();
}
