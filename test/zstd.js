'use strict';

const test = require('tape'),
	zstd = require('../src/index');

console.log('test', zstd);

function isSame(a, b) {
	if (a.length !== b.length) return false;
	for (var i = 0; i < a.length; i++) {
		if (a[i] !== b[i]) return false;
	}
	return true;
};

test('', t => {
	t.plan(100);

	for (var i = 0; i<100; i++) {

		var bsize = 1024*1024;
		var data = new Buffer(bsize);
		data.fill('A');

		var compressed = zstd.compress(data);
		var decompressed = zstd.decompress(compressed);

		t.equal(decompressed, data);
	}
});
