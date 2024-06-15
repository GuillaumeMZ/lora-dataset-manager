import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
	id: root

	width: 800
	height: 600

	visible: true

	//required property DatasetViewerViewModel viewModel
	property int currentItemIndex: 0

	Item {
		anchors.fill: parent

		visible: viewModel.images.length !== 0

		Frame {
			anchors {
				top: parent.top
				left: parent.left
				right: parent.horizontalCenter
				bottom: navigationArea.top
				margins: 8
				rightMargin: 4
			}

			Image {
				anchors.fill: parent

				fillMode: Image.PreserveAspectFit
				source: "file://" + viewModel.images[root.currentItemIndex].path
			}
		}

		Frame {
			anchors {
				top: parent.top
				left: parent.horizontalCenter
				right: parent.right
				bottom: navigationArea.top
				margins: 8
				leftMargin: 4
			}
		}

		Frame {
			id: navigationArea

			height: 50

			anchors {
				left: parent.left
				right: parent.right
				bottom: parent.bottom
				margins: 8
			}
		}
	}

	Text {
		anchors.centerIn: parent

		visible: viewModel.images.length === 0
	}
}
