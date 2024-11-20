// MIT License
//
// Copyright (c) 2024 FridaDEV
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <malloc/malloc.h>
#include "arbcall.h"

static void* (*arbSym)(uint64_t arg, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6) = NULL;

uint64_t arbCall(arbcall_t call) {
    #if debug
    printf("[arbCall] hello from arbCall!\n");
    #endif

    // ask the loader
    arbSym = dlsym(RTLD_DEFAULT, call.symbol);
    if(arbSym == NULL) {
        return 1;
    }

    #if debug
    printf("[arbCall] loader said %s is at %p\n", call.symbol, arbSym);
    #endif

    // call
    void *result = arbSym(call.args[0], call.args[1], call.args[2], call.args[3], call.args[4], call.args[5]);

    #if debug
    printf("[arbCall] symbol returned %llu\n", (uint64_t)result);
    #endif

    arbSym = NULL;
    return (uint64_t)result;
}
