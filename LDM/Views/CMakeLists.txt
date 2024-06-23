qt_add_library(ldm_views STATIC)

qt_add_qml_module(ldm_views
    URI "LDM.Views"
    VERSION 1.0
    QML_FILES
        DatasetViewer.qml
        Grabber.qml
        ImageDownloadSettingsDialog.qml
        Main.qml
)
