
#include "base_services.h"

#include <functional>

#include "log.h"
#include "utils.h"

BaseServices::BaseServices(/* args */) {}

BaseServices::~BaseServices() {}

void BaseServices::setSockPath(const std::string& sockPath) { _sockPath = sockPath; }

void BaseServices::onNewConnection(uv_stream_t* server, int status) {
    if (status == -1) {
        return;
    }

    uv_pipe_t* client = (uv_pipe_t*)malloc(sizeof(uv_pipe_t));
    uv_pipe_init(_loop, client, 0);

    uv_stream_t* stream = (uv_stream_t*)client;
    if (uv_accept(server, stream) == 0) {
        fprintf(stdout, "accept connect\n");

        Connection* con = new Connection;
        _connects.push_back(con);

        con->setStream(stream);        
        con->onMessage([this, con](const std::string& mesg) {
            onMessage(*con, mesg);
        });
        con->onClose([this, con](){
            log("==== onClose");
            std::remove(_connects.begin(), _connects.end(), con);
        });
    } 
    else {
        uv_close((uv_handle_t*)stream, NULL);
    }
}

void BaseServices::newConnection(uv_stream_t* server, int status) {
    BaseServices* self = (BaseServices*)server->data;
    if (self) {
        self->onNewConnection(server, status);
    }
}

void BaseServices::run() {
    _loop = uv_default_loop();

    uv_pipe_t server;
    uv_pipe_init(_loop, &server, 0);
    server.data = this;

    uv_fs_t req;
    uv_fs_unlink(_loop, &req, _sockPath.c_str(), NULL);

    int r;
    if ((r = uv_pipe_bind(&server, _sockPath.c_str()))) {
        fprintf(stderr, "Bind error %s\n", uv_err_name(r));
        return;
    }

    if ((r = uv_listen((uv_stream_t*)&server, 128, newConnection))) {
        fprintf(stderr, "Listen error %s\n", uv_err_name(r));
        return;
    }

    uv_run(_loop, UV_RUN_DEFAULT);
}
