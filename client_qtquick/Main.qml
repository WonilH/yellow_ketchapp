import QtQuick
import QtQuick.Controls
import QtProtobuf
import QtGrpc
import QtCore
import ClientQtQuick.Proto


Window {
    width: 400
    height: 300
    visible: true
    title: "QtProtobuf QML Client"

    GrpcHttp2Channel {
        id: grpcChannel
        hostUri: "http://localhost:50051"
    }

    GrpcCallOptions {
        id: grpcCallOptions
        deadlineTimeout: 6000
    }

    GreeterClient {
        id: greeter
        channel: grpcChannel.channel
    }

    ImageServiceClient {
        id: imageClient
        channel: grpcChannel.channel
    }

    property helloRequest req
    property imageListRequest listReq
    property imageRequest imageReq

    ListModel {
        id: imagesModel
    }

    // Q_INVOKABLE void SayHello(const imagestorage::HelloRequest &arg, const QJSValue &callback, const QJSValue &errorCallback, const QtGrpcQuickPrivate::QQmlGrpcCallOptions *options = nullptr);
    // Q_INVOKABLE void ListImages(const imagestorage::ImageListRequest &arg, const QJSValue &callback, const QJSValue &errorCallback, const QtGrpcQuickPrivate::QQmlGrpcCallOptions *options = nullptr);
    // Q_INVOKABLE void GetImage(const imagestorage::ImageRequest &arg, const QJSValue &callback, const QJSValue &errorCallback, const QtGrpcQuickPrivate::QQmlGrpcCallOptions *options = nullptr);


    function finishCallback(response: helloReply): void {
        greetingLabel.text = response.message
        console.log(response.message)
    }

    function errorCallback(error): void {
        console.log(
            `Error callback executed. Error message: "${error.message}" Code: ${error.code}`
        );
    }


    Column {
        anchors.centerIn: parent
        spacing: 6

        TextField {
            id: nameField
            placeholderText: "Name"
            width: parent.width * 0.7
        }

        Button {
            text: "Send"
            onClicked: {
                req.name = nameField.text
                greeter.SayHello(req, finishCallback, errorCallback, grpcCallOptions);
            }
        }

        Text {
            id: greetingLabel
            text: ""
        }

        Button {
            id: loadButton
            text: "Load Images"
            onClicked: {
                imageClient.ListImages(listReq, function(resp: imageListReply) {
                    imagesModel.clear()
                    for (let i = 0; i < resp.filenames.length; ++i)
                        imagesModel.append({ name: resp.filenames[i] })
                }, errorCallback, grpcCallOptions)
            }
        }

        ListView {
            id: imageList
            width: parent.width * 0.7
            height: 120
            model: imagesModel
            model: imagesModel
            delegate: Item {
                width: parent.width
                height: TextMetrics.height + 4 // Add some padding
                TextMetrics {
                    id: TextMetrics
                    text: name
                    elide: Text.ElideRight
                    width: parent.width
                }
                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    width: parent.width
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Update SwipeView's current index when an item is clicked
                        photoSwipeView.currentIndex = index
                    }
                }
            }
            // REMOVED: onCurrentIndexChanged: photoSwipeView.currentIndex = currentIndex
        }

        SwipeView {
            id: photoSwipeView
            width: parent.width * 0.7
            height: 200 // Or any appropriate height
            model: imagesModel
            clip: true // Clip items to view bounds

            delegate: Item { // Changed from Image to Item
                width: photoSwipeView.width
                height: photoSwipeView.height

                Image {
                    id: imageItem // Added id to reference status
                    anchors.fill: parent
                    source: "file:///downloads/" + name
                    fillMode: Image.PreserveAspectFit

                    background: Rectangle {
                        color: "lightgray"
                        // Visible when image is loading, error, or null
                        visible: imageItem.status !== Image.Ready 
                    }
                }

                Text {
                    anchors.centerIn: parent
                    width: parent.width * 0.8 // Constrain width for better wrapping
                    text: "Image not downloaded. Please select from list and click 'Download Selected'."
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                    color: "black" // Ensure visibility against lightgray background
                    // Visible only when the image has an error (e.g., not found)
                    visible: imageItem.status === Image.Error 
                }
            }
            // Synchronize ListView's current index when SwipeView's current index changes
            onCurrentIndexChanged: imageList.currentIndex = currentIndex
        }

        Button {
            text: "Download Selected"
            onClicked: {
                if (imageList.currentIndex < 0)
                    return
                imageReq.filename = imagesModel.get(imageList.currentIndex).name
                imageClient.GetImage(imageReq, function(resp: imageData) {
                    var path = "downloads/" + imageReq.filename
                    if (fileWriter.save(path, resp.data))
                        console.log("Saved to " + path)
                }, errorCallback, grpcCallOptions)
            }
        }
    }
}
