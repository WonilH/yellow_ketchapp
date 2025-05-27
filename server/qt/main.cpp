#include <QCoreApplication>
#include <QtGrpc/QGrpcServer>
#include <QtGrpc/QGrpcHttp2Server>

#include "helloworld.qpb.h"
#include "helloworld_service.grpc.qpb.h"

class GreeterServiceImpl : public helloworld::GreeterService
{
public:
    void SayHello(helloworld::HelloReply *response,
                  const helloworld::HelloRequest &request,
                  const QGrpcServerCallContext &) override
    {
        response->setMessage(QStringLiteral("Hello %1").arg(request.name()));
    }
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QGrpcHttp2Server server;
    GreeterServiceImpl service;

    server.start(50051);
    server.registerService(&service);

    return app.exec();
}
