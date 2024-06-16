import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Qt.labs.animation

Window {
	id: root

	width: 800
	height: 600

	title: `Dataset "${viewModel.dataset.name}" (${viewModel.dataset.path}) - LoraDatasetManager`
	visible: true

	//required property DatasetViewerViewModel viewModel
	property int currentItemIndex: 0 //should be named currentImageIndex

	Item {
		anchors.fill: parent

		visible: viewModel.images.length !== 0


		RoundButton {
			id: previousImageButton

			anchors {
				left: parent.left
				leftMargin: 8
				verticalCenter: imageArea.verticalCenter
			}

			enabled: root.currentItemIndex !== 0
			text: "<"
			onClicked: root.currentItemIndex--
		}

		ScrollView {
			id: imageArea

			anchors {
				top: parent.top
				left: previousImageButton.right
				right: parent.horizontalCenter
				bottom: navigationArea.top
				margins: 8
				rightMargin: 4
			}

			contentWidth: image.width * image.scale
			contentHeight: image.height * image.scale

			Image {
				id: image

				width: imageArea.width
				height: imageArea.height


				fillMode: Image.PreserveAspectFit
				source: "file://" + viewModel.images[root.currentItemIndex].path
				transformOrigin: Item.TopLeft

				WheelHandler {
					id: imageWheelHandler

					property: "scale"
					targetTransformAroundCursor: false
					//TODO: handle modifiers to move up/down/left/right
				}

				BoundaryRule on scale {
					minimum: 1.0
					maximum: 5.0
				}
			}

		}

		Item {
			id: tagEditorAreaContainer

			anchors {
				top: parent.top
				left: parent.horizontalCenter
				right: nextImageButton.left
				bottom: navigationArea.top
				margins: 8
				leftMargin: 4
			}

			Frame {
				id: tagEditorArea

				anchors.fill: parent

				padding: 0

				visible: viewModel.images[root.currentItemIndex].associatedTagfile !== null

				ScrollView {
					anchors.fill: parent

					TextArea {
						text: viewModel.images[root.currentItemIndex].associatedTagfile?.tags ?? ""
						placeholderText: "Write your tags here..."
						wrapMode: TextEdit.WrapAnywhere
					}
				}
			}


			Text {
				anchors.centerIn: parent

				horizontalAlignment: Text.AlignHCenter
				onLinkActivated: (link) => console.log(link)
				text: "No tags found for this image.<br/><a href=\"#\">Create a file to start tagging...</a>"
				textFormat: Text.RichText
				visible: viewModel.images[root.currentItemIndex].associatedTagfile === null

				//TODO: display cursor when hovering the link. see https://stackoverflow.com/questions/78030298/how-to-make-links-within-a-qml-text-element-show-pointing-hand-mouse-cursor-wh
				//TODO: handle click on link (onLinkActivated)
			}
		}


		RoundButton {
			id: nextImageButton

			anchors {
				right: parent.right
				rightMargin: 8
				verticalCenter: tagEditorAreaContainer.verticalCenter
			}

			enabled: root.currentItemIndex !== viewModel.images.length - 1
			text: ">"
			onClicked: root.currentItemIndex++
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

			Text {
				id: imageTitle

				anchors.centerIn: parent

				font.pointSize: 20
				text: viewModel.images[root.currentItemIndex].name
			}
		}
	}

	Text {
		anchors.centerIn: parent

		horizontalAlignment: Text.AlignHCenter
		text: "This dataset is empty.\nAdd images to this dataset (for instance with the integrated grabber)\nto start edition."
		visible: viewModel.images.length === 0
	}
}
