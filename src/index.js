var zstd = require('../build/Release/zstd');

module.exports.compress = zstd.compress;
module.exports.decompress = zstd.decompress;
