#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>

#include <QDir>
#include <QDirIterator>
#include <QQmlContext>

#include "LDM/Models/LocalDataset.hpp"
#include "LDM/ViewModels/DatasetViewerViewModel.hpp"

#include "LDM/Models/LocalDataset.hpp"

int main(int argc, char *argv[])
{
    Q_IMPORT_QML_PLUGIN(LDM_ModelsPlugin)
    Q_IMPORT_QML_PLUGIN(LDM_ViewModelsPlugin)
    Q_IMPORT_QML_PLUGIN(LDM_ViewsPlugin)

    QGuiApplication _(argc, argv);


    LocalDataset dataset(QString("/home/guillaume/Documents/test_dataset"));
    DatasetViewerViewModel viewModel(&dataset);
    dataset.load();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("viewModel", &viewModel); //TODO: instantiate directly in QML
    engine.loadFromModule("LDM.Views", "Grabber");

    return QGuiApplication::exec();
}
