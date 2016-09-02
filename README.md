# node-zstandard

zstandard bindings for Node

## Getting started

#### Prerequisites
This project requires the zstandard library (`libzstd`) to be installed on your system. Generally, you can install it via your system's package manager, but you can always compile and install it yourself.

#### Installation
Add the zstandard module to your project:

```
$ npm install zstandard
```

## Usage
```
var zstd = require('zstandard');

let buf = new Buffer();

// pass a buffer and get back a compressed buffer
let compressed = zstd.compress(buf);

// pass a compressed buffer and get back the original data
let decompressed = zstd.decompress(compressed);

```

## API
#### compress(data: Buffer): Buffer

Compresses data. Takes and returns a `Buffer` object.

#### decompress(data: Buffer): Buffer

Decompresses data. Takes and returns a `Buffer` object.
