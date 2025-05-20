#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QtGrpc/QGrpcCallOptions>
#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>
#include <QtGrpc/QGrpcCallReply>

#include "imagestorage.qpb.h"
#include "imagestorage_client.grpc.qpb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::unique_ptr<imagestorage::Greeter::Client> greeter = std::make_unique<imagestorage::Greeter::Client>();
    std::unique_ptr<imagestorage::ImageService::Client> imageClient = std::make_unique<imagestorage::ImageService::Client>();

    auto channel = std::make_shared<QGrpcHttp2Channel>(QUrl("http://localhost:50051"));
    greeter->attachChannel(channel);
    imageClient->attachChannel(channel);


    QWidget window;
    window.setWindowTitle("gRPC Client");
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QHBoxLayout *form = new QHBoxLayout();
    QLabel *nameLabel = new QLabel("Name:");
    QLineEdit *nameEdit = new QLineEdit();
    form->addWidget(nameLabel);
    form->addWidget(nameEdit);

    QPushButton *sendButton = new QPushButton("Send");
    QLabel *resultLabel = new QLabel();

    QListWidget *imageList = new QListWidget();
    QPushButton *loadButton = new QPushButton("Load Images");
    QPushButton *downloadButton = new QPushButton("Download Selected");

    QObject::connect(sendButton, &QPushButton::clicked, [&]() {
        imagestorage::HelloRequest req;
        req.setName(nameEdit->text());
        auto reply = greeter->SayHello(req);
        auto *replyPtr = reply.release();
        QObject::connect(replyPtr, &QGrpcCallReply::finished, &window, [replyPtr, resultLabel]() {
            imagestorage::HelloReply resp;
            replyPtr->read(&resp);
            resultLabel->setText(resp.message());
            replyPtr->deleteLater();
        });
    });

    QObject::connect(loadButton, &QPushButton::clicked, [&]() {
        imagestorage::ImageListRequest req;
        auto reply = imageClient->ListImages(req);
        auto *replyPtr = reply.release();
        QObject::connect(replyPtr, &QGrpcCallReply::finished, imageList, [replyPtr, imageList]() {
            imagestorage::ImageListReply resp;
            replyPtr->read(&resp);
            imageList->clear();
            for (const auto &name : resp.filenames())
                imageList->addItem(name);
            replyPtr->deleteLater();
        });
    });

    QObject::connect(downloadButton, &QPushButton::clicked, [&]() {
        auto item = imageList->currentItem();
        if (!item)
            return;
        const QString filename = item->text();
        imagestorage::ImageRequest req;
        req.setFilename(filename);
        auto reply = imageClient->GetImage(req);
        auto *replyPtr = reply.release();
        QObject::connect(replyPtr, &QGrpcCallReply::finished, &window, [replyPtr, filename, &window]() {
            imagestorage::ImageData resp;
            replyPtr->read(&resp);
            QDir().mkpath("downloads");
            QFile file("downloads/" + filename);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(resp.data());
                file.close();
                QMessageBox::information(&window, "Downloaded", "Saved to " + file.fileName());
            }
            replyPtr->deleteLater();
        });
    });

    layout->addLayout(form);
    layout->addWidget(sendButton);
    layout->addWidget(resultLabel);
    layout->addWidget(loadButton);
    layout->addWidget(imageList);
    layout->addWidget(downloadButton);

    window.show();
    return app.exec();
}
