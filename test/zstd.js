'use strict';

const test = require('tape'),
	zstd = require('../src/index');

test('zstandard compress/decompress', t => {
	let bsize = 1024*1024;

	for (var i = 0; i < 100; i++) {
		var data = new Buffer(bsize);
		data.fill(''+i);

		var compressed = zstd.compress(data),
			decompressed = zstd.decompress(compressed);

		t.equal(decompressed.toString('base64'), data.toString('base64'));
	}

	t.end();
});
