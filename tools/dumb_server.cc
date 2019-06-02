// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include <cstdlib>

#include "gflags/gflags.h"
#include "glog/logging.h"
#include "pistache/endpoint.h"

using namespace ::Pistache;

class HelloHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        LOG(INFO) << "Serving a request";
         response.send(Http::Code::Ok, "Hello, World");
    }
};

DEFINE_string(listen_address, "*:8080", "The address on which to listen");

int main(int argc, char *argv[]) {
    ::gflags::SetUsageMessage("A stupid server");
    ::gflags::SetVersionString("0.0.1");
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);
    ::google::InitGoogleLogging(argv[0]);

    Address addr(FLAGS_listen_address);
    auto opts = Http::Endpoint::options().threads(1)
        .flags(Flags<Tcp::Options>(Tcp::Options::ReuseAddr));
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    LOG(INFO) << "Serving on " << FLAGS_listen_address;
    server.serve();

    return EXIT_SUCCESS;
}
