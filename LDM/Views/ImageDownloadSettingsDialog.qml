import QtQuick
import QtQuick.Controls

import LDM.ViewModels 1.0

Window {
    id: window

    required property var image
    required property GrabberViewModel grabber

    signal imageAddedToDownloadList()

    minimumWidth: maximumWidth
    minimumHeight: maximumHeight
    maximumWidth: 400
    maximumHeight: 136

    modality: Qt.ApplicationModal
    flags: Qt.Dialog

    Text {
        id: nameFieldLabel

        anchors {
            left: parent.left
            leftMargin: 8
            verticalCenter: nameField.verticalCenter
        }

        text: "Download as:"
    }

    TextField {
        id: nameField

        anchors {
            left: nameFieldLabel.right
            top: parent.top
            right: parent.right
            leftMargin: 8
            topMargin: 8
            rightMargin: 8
        }

        height: 32

        placeholderText: "Leave empty to use the default name"
    }

    Text {
        id: taggingStrategyLabel

        anchors {
            left: parent.left
            leftMargin: 8
            verticalCenter: taggingStrategy.verticalCenter
        }

        text: "Image tagging:"
    }

    CheckBox {
        id: taggingStrategy

        anchors {
            left: taggingStrategyLabel.right
            top: nameField.bottom
            right: parent.right
            leftMargin: 8
            topMargin: 8
            rightMargin: 8
        }

        height: 32

        checkState: Qt.Checked
        text: "Download associated tags"
    }

    Button {
        anchors {
            top: taggingStrategy.bottom
            right: cancelButton.left
            topMargin: 16
            rightMargin: 8
        }

        height: 32

        text: "Download"
        onClicked: () => {
            grabber.addImageToDownloadList(image, nameField.text, taggingStrategy.checkedState === true);
            imageAddedToDownloadList();
            window.close();
        }
    }

    Button {
        id: cancelButton

        anchors {
            top: taggingStrategy.bottom
            right: parent.right
            topMargin: 16
            rightMargin: 8
        }

        height: 32

        text: "Cancel"
        onClicked: window.close()
    }
}
