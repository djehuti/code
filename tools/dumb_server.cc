// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include <cstdlib>

#include "pistache/endpoint.h"

using namespace ::Pistache;

class HelloHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
         response.send(Http::Code::Ok, "Hello, World");
    }
};

int main(int, char *[]) {
    Http::listenAndServe<HelloHandler>("*:8080");
    return EXIT_SUCCESS;
}
