{
  "targets": [
    {
      "target_name": "zstd",
      "cflags": [ "-O3" ],
      "libraries": [
        "-Wl,-rpath,./lib",
        "-L./lib",
        "-lzstd"
      ],
      "sources": [ "src/zstd.cc" ]
    }
  ]
}
