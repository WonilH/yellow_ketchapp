#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtGrpc/QGrpcCallOptions>
#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>
#include <QtGrpc/QGrpcCallReply>

#include "helloworld.qpb.h"
#include "helloworld_client.grpc.qpb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::unique_ptr<helloworld::Greeter::Client> greeter = std::make_unique<helloworld::Greeter::Client>();

    auto channel = std::make_shared<QGrpcHttp2Channel>(QUrl("http://localhost:50051"));
    greeter->attachChannel(channel);


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


    QObject::connect(sendButton, &QPushButton::clicked, [&]() {
        helloworld::HelloRequest req;
        req.setName(nameEdit->text());
        auto reply = greeter->SayHello(req);
        auto *replyPtr = reply.release();
        QObject::connect(replyPtr, &QGrpcCallReply::finished, &window, [replyPtr, resultLabel]() {
            helloworld::HelloReply resp;
            replyPtr->read(&resp);
            resultLabel->setText(resp.message());
            replyPtr->deleteLater();
        });
    });


    layout->addLayout(form);
    layout->addWidget(sendButton);
    layout->addWidget(resultLabel);

    window.show();
    return app.exec();
}
