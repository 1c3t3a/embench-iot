OUT_DIR = build/
CC=clang
LDFLAGS =-Wl,--initial-memory=65536 -Wl,--max-memory=65536 -Wl,-zstack-size=10000 -Wl,--global-base=32778 -Wl,-stack-first -Wl,-no-entry -Wl,--export-all
CFLAGS =--target=wasm32 -nostdlib -O3 -flto 
OPTFLAGS = --strip-debug --strip-dwarf
DEFAULTS = config/wasm32/boards/generic/boardsupport.c -Iconfig/wasm32/boards/generic/ -Isupport/ -I.

EXEC1 = $(OUT_DIR)crc32.wasm
EXEC2 = $(OUT_DIR)mont64.wasm
EXEC3 = $(OUT_DIR)qrduino.wasm
EXEC4 = $(OUT_DIR)libedn.wasm
EXEC5 = $(OUT_DIR)aes.wasm
EXEC6 = $(OUT_DIR)matmult.wasm

ALL_EXECS = $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6)
all: $(ALL_EXECS)

$(EXEC1): 
	$(CC) $(CFLAGS) -o $(EXEC1) support/main.c src/crc32/crc_32.c util.c $(DEFAULTS) $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC1) $(OPTFLAGS) $(EXEC1)

$(EXEC2): 
	$(CC) $(CFLAGS) -o $(EXEC2) support/main.c src/aha-mont64/mont64.c util.c $(DEFAULTS) $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC2) $(OPTFLAGS) $(EXEC2)

$(EXEC3):
	$(CC) $(CFLAGS) -o $(EXEC3) support/main.c src/qrduino/qrtest.c src/qrduino/qrencode.c src/qrduino/qrframe.c string.c $(DEFAULTS) -Isrc/qrduino/ $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC3) $(OPTFLAGS) $(EXEC3)

$(EXEC4):
	$(CC) $(CFLAGS) -o $(EXEC4) support/main.c src/edn/libedn.c string.c $(DEFAULTS) $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC4) $(OPTFLAGS) $(EXEC4)

$(EXEC5):
	$(CC) $(CFLAGS) -o $(EXEC5) support/main.c src/nettle-aes/nettle-aes.c string.c $(DEFAULTS) $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC5) $(OPTFLAGS) $(EXEC5)

$(EXEC6):
	$(CC) $(CFLAGS) -o $(EXEC6) support/main.c src/matmult-int/matmult-int.c string.c $(DEFAULTS) $(LDFLAGS)
	wasm-opt -Oz -o $(EXEC6) $(OPTFLAGS) $(EXEC6)

clean:
	rm -rf $(ALL_EXECS)
