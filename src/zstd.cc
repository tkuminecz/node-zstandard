#include <cstdlib>
#include <node.h>
#include <node_buffer.h>

extern "C" {
  #include "../deps/zstd/lib/zstd.h"
}

#define ZSTDJS_BLOCK_SIZE 128 * (1U<<10) //128 KB
#define throwError(i,type,msg) (i->ThrowException(type( String::NewFromUtf8(i, msg) )))

const int compLevel = 3;

namespace zstandard {
  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::MaybeLocal;
  using v8::Object;
  using v8::String;
  using v8::Value;

  /**
   * Converts node buffer to char*
   */
  char * fromNodeBuffer(Local<Object> buf, size_t &len) {
    len = node::Buffer::Length(buf);
    return node::Buffer::Data(buf);
  }

  /**
   * Converts char* to node buffer
   */
  Local<Object> toNodeBuffer(Isolate *isolate, char *data, size_t len) {
    MaybeLocal<Object> result = node::Buffer::New(isolate, data, len);
    return result.ToLocalChecked();
  }

  /**
   * Compresses data
   */
  void Compress(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // validate args
    if (args.Length() < 1 || !node::Buffer::HasInstance(args[0])) {
      throwError(isolate, Exception::TypeError, "Expected first argument to be a buffer");
      return;
    }

    // convert node buffer
    Local<Object> srcBuffer = args[0]->ToObject();
    size_t srcSize;
    char *srcData = fromNodeBuffer(srcBuffer, srcSize);

    // allocate memory for compressed data
    size_t maxCompressedSize = ZSTD_compressBound(srcSize);
    char *compressedData = (char *)std::malloc(maxCompressedSize);
    if (!compressedData) {
      throwError(isolate, Exception::Error, "Not enough memory");
      return;
    }

    // actually compress the data
    size_t actualCompressedSize = ZSTD_compress(compressedData, maxCompressedSize, srcData, srcSize, compLevel);
    if (ZSTD_isError(actualCompressedSize)) {
      throwError(isolate, Exception::Error, "Error compressing data");
      return;
    }

    // return as a node buffer
    args.GetReturnValue().Set(toNodeBuffer(isolate, compressedData, actualCompressedSize));
  }

  /**
   * Decompresses data
   */
  void Decompress(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
  }

  /**
   * Initialize the module
   */
  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "compress", Compress);
    NODE_SET_METHOD(exports, "decompress", Decompress);
  }

  NODE_MODULE(zstandard, init);
}
