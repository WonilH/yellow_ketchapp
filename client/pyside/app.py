import grpc
import sys
from PySide6 import QtWidgets

import proto.helloworld_pb2 as helloworld_pb2
import proto.helloworld_pb2_grpc as helloworld_pb2_grpc


def send_request(channel, name):
    stub = helloworld_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(helloworld_pb2.HelloRequest(name=name))
    return response.message




def main(channel):
    app = QtWidgets.QApplication(sys.argv)

    window = QtWidgets.QWidget()
    window.setWindowTitle("gRPC Client")

    layout = QtWidgets.QVBoxLayout()

    form_layout = QtWidgets.QHBoxLayout()
    name_label = QtWidgets.QLabel("Name:")
    name_edit = QtWidgets.QLineEdit()
    form_layout.addWidget(name_label)
    form_layout.addWidget(name_edit)

    send_button = QtWidgets.QPushButton("Send")
    result_label = QtWidgets.QLabel()


    def on_send():
        result_label.setText(send_request(channel, name_edit.text()))

    send_button.clicked.connect(on_send)


    layout.addLayout(form_layout)
    layout.addWidget(send_button)
    layout.addWidget(result_label)

    window.setLayout(layout)
    window.show()

    app.exec()


if __name__ == "__main__":
    with grpc.insecure_channel("localhost:50051") as channel:
        main(channel)

