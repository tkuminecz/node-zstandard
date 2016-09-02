var zstd = require('../build/Release/zstd');

/**
 * Compressses data
 */
module.exports.compress = function compress(data) {
	return zstd.compress(data);
}

/**
 * Decompresses data
 */
module.exports.decompress = function decompress(buf) {
	return zstd.decompress(buf);
}
