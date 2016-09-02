CC=gcc
CFLAGS=-c -Wall -O3 -I deps/zstd/lib/ -I deps/zstd/lib/common/

SRC_DIR=deps/zstd
BUILD_DIR=build/lib
LIB_FILE=$(BUILD_DIR)/libzstd.a

COMMON=$(SRC_DIR)/lib/common/zstd_common.c
COMPRESS=$(SRC_DIR)/lib/compress/zstd_compress.c
DECOMPRESS=$(SRC_DIR)/lib/decompress/zstd_decompress.c

all: lib

lib: $(BUILD_DIR) $(LIB_FILE)

$(LIB_FILE): $(BUILD_DIR)/common.o $(BUILD_DIR)/compress.o $(BUILD_DIR)/decompress.o
	ar cr $(LIB_FILE) $(BUILD_DIR)/common.o $(BUILD_DIR)/compress.o $(BUILD_DIR)/decompress.o

$(BUILD_DIR)/common.o: deps/zstd/lib/common/zstd_common.c
	$(CC) $(CFLAGS) $(COMMON) -o $(BUILD_DIR)/common.o

$(BUILD_DIR)/compress.o: build/lib deps/zstd/lib/compress/zstd_compress.c
	$(CC) $(CFLAGS) $(COMPRESS) -o $(BUILD_DIR)/compress.o

$(BUILD_DIR)/decompress.o: build/lib deps/zstd/lib/decompress/zstd_decompress.c
	$(CC) $(CFLAGS) $(DECOMPRESS) -o $(BUILD_DIR)/decompress.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
