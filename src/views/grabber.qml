import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800; height: 600
    title: "Downloader"
    visible: true

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

        onClicked: grabber.runSearch(booruSelector.currentText, queryInput.text)
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

        height: 300

        currentIndex: mainTabBar.currentIndex

        Item {
            ScrollView {
                anchors.fill: parent
                anchors.topMargin: 8

                Flow {
                    spacing: 8
                    width: mainTabContent.width

                    Repeater {
                        model: grabber.queriedImages

                        Image {
                            width: 250; height: 250

                            fillMode: Image.PreserveAspectFit
                            source: item.imageThumbnailUrl
                        }
                    }
                }
            }
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