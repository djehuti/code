// Copyright (c) 2019 Ben Cox <cox@djehuti.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdlib>

#include "gflags/gflags.h"
#include "glog/logging.h"
#include "pistache/endpoint.h"

using namespace ::Pistache;

class HelloHandler : public Http::Handler {
 public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request &request, Http::ResponseWriter response) {
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
    auto opts =
        Http::Endpoint::options().threads(1).flags(Flags<Tcp::Options>(Tcp::Options::ReuseAddr));
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    LOG(INFO) << "Serving on " << FLAGS_listen_address;
    server.serve();

    return EXIT_SUCCESS;
}
