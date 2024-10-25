
#include "utils.h"

#include <cstdlib>

#include "types.h"

void allocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void freeWriteReqCb(uv_write_t* req, int status) {
    if (status < 0) {
        fprintf(stderr, "Write error %s\n", uv_err_name(status));
    }

    WriteReq* wr = (WriteReq*)req;
    free(wr);
}

void freePipeCb(uv_handle_t* handle) {
    uv_pipe_t* pipe = (uv_pipe_t*)handle;
    free(pipe);
}

size_t randomId() { return std::rand(); }