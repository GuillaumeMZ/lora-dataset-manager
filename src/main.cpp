#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDir>
#include <QDirIterator>
#include <QQmlContext>

#include "models/LocalDataset.hpp"
#include "viewmodels/DatasetViewerViewModel.hpp"

#include "models/LocalDataset.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication _(argc, argv);


    LocalDataset dataset(QString("/home/guillaume/Documents/test_dataset"));
    DatasetViewerViewModel viewModel(&dataset);
    dataset.load();

    QQmlApplicationEngine engine;
    //engine.loadFromModule("LDM.src.views", "Main");
    engine.rootContext()->setContextProperty("viewModel", &viewModel);

    //TODO: reorganize the project files to use QQmlApplicationEngine::loadFromModule instead of this
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/LDM/src/views/main.qml")));

    return QGuiApplication::exec();
}
