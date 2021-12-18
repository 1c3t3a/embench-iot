#include <support.h>

void initialise_board() {}

#define WASM_IMPORT(function, signature) \
    __attribute__((import_module("env"), import_name(function))) signature

WASM_IMPORT("start_trigger", void start_trigger(void));
WASM_IMPORT("stop_trigger", void stop_trigger(void));

