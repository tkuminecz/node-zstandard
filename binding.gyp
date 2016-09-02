{
  "targets": [
    {
      "target_name": "zstd",
      "cflags": [ "-O3 -Wall" ],
      "libraries": [
        "-Wl,-rpath",
        "-L./lib",
        "-lzstd"
      ],
      "sources": [ "src/zstd.cc" ]
    }
  ]
}
