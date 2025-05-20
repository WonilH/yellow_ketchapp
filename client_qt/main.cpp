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

#include "imagestorage.qpb.h"
#include "imagestorage_client.grpc.qpb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::unique_ptr<imagestorage::Greeter::Client> greeter = std::make_unique<imagestorage::Greeter::Client>();
    std::unique_ptr<imagestorage::ImageService::Client> imageClient = std::make_unique<imagestorage::ImageService::Client>();

    greeter->attachChannel(std::make_shared<QGrpcHttp2Channel>(QUrl("grpc://localhost:50051")));


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
        // resultLabel->setText(QString::fromStdString(reply.message()));
    });

    QObject::connect(loadButton, &QPushButton::clicked, [&]() {
        imagestorage::ImageListRequest req;
        auto reply = imageClient->ListImages(req);
        imageList->clear();
        // for (const auto &name : reply.filenames())
        //     imageList->addItem(QString::fromStdString(name));
    });

    QObject::connect(downloadButton, &QPushButton::clicked, [&]() {
        auto item = imageList->currentItem();
        if (!item)
            return;
        imagestorage::ImageRequest req;
        req.setFilename(item->text());
        auto reply = imageClient->GetImage(req);
        QDir().mkpath("downloads");
        QFile file("downloads/" + item->text());
        if (file.open(QIODevice::WriteOnly)) {
            // file.write(QByteArray::fromStdString(reply.data()));
            file.close();
            QMessageBox::information(&window, "Downloaded", "Saved to " + file.fileName());
        }
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
