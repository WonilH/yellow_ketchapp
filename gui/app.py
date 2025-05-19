import grpc
import sys
import os
from PySide6 import QtWidgets

import proto.imagestorage_pb2 as imagestorage_pb2
import proto.imagestorage_pb2_grpc as imagestorage_pb2_grpc


def send_request(channel, name):
    stub = imagestorage_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(imagestorage_pb2.HelloRequest(name=name))
    return response.message


def list_images(channel):
    stub = imagestorage_pb2_grpc.ImageServiceStub(channel)
    resp = stub.ListImages(imagestorage_pb2.ImageListRequest())
    return resp.filenames


def download_image(channel, filename):
    stub = imagestorage_pb2_grpc.ImageServiceStub(channel)
    resp = stub.GetImage(imagestorage_pb2.ImageRequest(filename=filename))
    return resp.data


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

    image_list = QtWidgets.QListWidget()
    load_button = QtWidgets.QPushButton("Load Images")
    download_button = QtWidgets.QPushButton("Download Selected")

    def on_send():
        result_label.setText(send_request(channel, name_edit.text()))

    send_button.clicked.connect(on_send)

    def on_load():
        image_list.clear()
        for name in list_images(channel):
            image_list.addItem(name)

    def on_download():
        item = image_list.currentItem()
        if item is None:
            return
        data = download_image(channel, item.text())
        os.makedirs("downloads", exist_ok=True)
        path = os.path.join("downloads", item.text())
        with open(path, "wb") as f:
            f.write(data)
        QtWidgets.QMessageBox.information(window, "Downloaded", f"Saved to {path}")

    load_button.clicked.connect(on_load)
    download_button.clicked.connect(on_download)

    layout.addLayout(form_layout)
    layout.addWidget(send_button)
    layout.addWidget(result_label)
    layout.addWidget(load_button)
    layout.addWidget(image_list)
    layout.addWidget(download_button)

    window.setLayout(layout)
    window.show()

    app.exec()


if __name__ == "__main__":
    with grpc.insecure_channel("localhost:50051") as channel:
        main(channel)

