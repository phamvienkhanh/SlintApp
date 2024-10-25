#ifndef _CORE_UTILS_H_
#define _CORE_UTILS_H_

#include <uv.h>

void allocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
void freeWriteReqCb(uv_write_t* req, int status);
void freePipeCb(uv_handle_t* handle);

size_t randomId();

#endif