import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import LDM 1.0

Window {
    width: 800; height: 600
    title: "Downloader"
    visible: true

    GrabberViewModel {
        id: grabberViewModel
    }

    TextField {
        id: queryInput

        anchors {
            left: parent.left
            top: parent.top
            right: booruSelector.left
            leftMargin: 8
            topMargin: 8
            rightMargin: 8
        }

        height: 32

        placeholderText: "Ex: blue_sky 1girl"
    }

    ComboBox {
        id: booruSelector

        anchors {
            top: parent.top
            right: searchButton.left
            rightMargin: 8
            topMargin: 8
        }

        width: 100
        height: 32

        model: ["Gelbooru", "Safebooru"]
    }

    Button {
        id: searchButton

        anchors {
            right: parent.right
            top: parent.top
            topMargin: 8
            rightMargin: 8
        }

        width: 60
        height: 32

        text: "Search"

        onClicked: grabberViewModel.runSearch(booruSelector.currentText, queryInput.text)
    }

    TabBar {
        id: mainTabBar

        anchors {
            top: searchButton.bottom
            left: parent.left
            right: parent.right
            topMargin: 8
            leftMargin: 8
            rightMargin: 8
        }

        contentHeight: 32

        TabButton {
            width: implicitWidth

            text: "Grabber"
        }

        TabButton {
            width: implicitWidth

            text: "Download manager"
        }
    }

    StackLayout {
        id: mainTabContent

        anchors {
            top: mainTabBar.bottom
            left: parent.left
            right: parent.right
            bottom: downloadButton.top
            leftMargin: 8
            rightMargin: 8
            bottomMargin: 8
        }

        currentIndex: mainTabBar.currentIndex

        Item {
            id: grabberView

            ScrollView {
                anchors.fill: parent
                anchors.topMargin: 8

                visible: parent.state !== "no_result"

                Flow {
                    spacing: 8
                    width: mainTabContent.width

                    Repeater {
                        model: grabberViewModel.queriedImages

                        Item {
                            width: thumbnail.width
                            height: thumbnail.height

                            Image {
                                id: thumbnail

                                width: Math.max(implicitWidth, implicitHeight)
                                height: Math.max(implicitWidth, implicitHeight)

                                fillMode: Image.PreserveAspectFit
                                source: item.imageThumbnailUrl
                            }

                            CheckBox {
                                id: isInDownloadList

                                anchors {
                                    left: parent.left
                                    leftMargin: 8
                                    top: parent.top
                                    topMargin: 8
                                }

                                checkState: grabberViewModel.isImageMarkedForDownload(item.fullImageUrl) ? Qt.Checked : Qt.Unchecked

                                nextCheckState: function () {
                                    if (checkState === Qt.Unchecked) {
                                        downloadSettingsDialog.show();
                                    } else {
                                        grabberViewModel.removeImageFromDownloadList(item.fullImageUrl);
                                    }

                                    return Qt.Unchecked;
                                }
                            }

                            ImageDownloadSettingsDialog {
                                id: downloadSettingsDialog

                                grabber: grabberViewModel
                                image: item

                                onImageAddedToDownloadList: isInDownloadList.checkState = Qt.Checked;
                            }
                        }
                    }
                }
            }

            Text {
                anchors.centerIn: parent

                text: "No result."
                visible: parent.state === "no_result"
            }

            Connections {
                target: grabberViewModel

                function onQueryStarted() {
                    grabberView.state = "";
                }

                function onQueryFinished() {
                    if(grabberViewModel.queriedImages.rowCount() === 0) {
                        grabberView.state = "no_result";
                    }
                }

                function onErrorOccured(errorMessage) {
                    //TODO
                }
            }

            states: [
                State {
                    name: "no_result"
                }
            ]
        }
    }

    Button {
        id: downloadButton

        anchors {
            bottom: parent.bottom
            right: cancelButton.left
            bottomMargin: 8
            rightMargin: 8
        }

        width: 80; height: 32

        text: "Download"
    }

    Button {
        id: cancelButton

        height: 32
        width: 80

        anchors {
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 8
            rightMargin: 8
        }

        text: "Cancel"
    }
}