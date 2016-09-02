{
  "targets": [
    {
      "target_name": "zstd",
      "cflags": [ "-O3" ],
      "libraries": [ "-lzstd", "-L/usr/local/lib" ],
      "sources": [ "src/zstd.cc" ]
    }
  ]
}
