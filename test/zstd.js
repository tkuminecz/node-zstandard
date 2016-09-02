'use strict';

const test = require('tape'),
	zstd = require('../src/index');

test('zstandard compress/decompress', t => {
	t.plan(100);

	let bsize = 1024*1024;

	for (var i = 0; i < 100; i++) {
		var data = new Buffer(bsize);
		data.fill(''+i);

		var compressed = zstd.compress(data),
			decompressed = zstd.decompress(compressed);

		t.equal(decompressed.toString('base64'), data.toString('base64'));
	}

});

test('zstandard compress errors', t => {
	t.plan(1);

	try {
		zstd.compress('foo');
		t.fail('should have thrown an exception');
	}
	catch (err) {
		t.equal(err.message, 'Expected first argument to be a buffer');
	}

});

test('zstandard decompress errors', t => {
	t.plan(1);

	try {
		zstd.decompress('foo');
		t.fail('should have thrown an exception');
	}
	catch (err) {
		t.equal(err.message, 'Expected first argument to be a buffer');
	}

});
