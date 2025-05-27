import QtQuick
import QtQuick.Controls
import QtProtobuf
import QtGrpc
import ClientQtQuick.Proto


Window {
    width: 300
    height: 200
    visible: true
    title: "Qt Quick Client"

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

    property helloRequest req  // QML_VALUE_TYPE

    function finishCallback(response: helloReply): void {
        greetingLabel.text = response.message
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
    }
}

