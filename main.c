#if 0
clang main.c struct.c -O0
exit
#endif

#include "nanoprofiler.h"
#include "nanoprofiler.c"
#include <stdlib.h>
#include <time.h>

enum {BYTES = 10000};

struct TYPE {
  unsigned char bytes[BYTES];
};

extern struct TYPE output;

#define BY_VAL 1

#if BY_VAL == 1
#ifdef _WIN32
__declspec(noinline) void
#else
void __attribute__ ((noinline))
#endif
procedure(struct TYPE input, struct TYPE * output) {
  for (int i = 0; i < BYTES; i += 1) {
    output->bytes[i] = input.bytes[i] + input.bytes[i];
  }
}
#else
#ifdef _WIN32
__declspec(noinline) void
#else
void __attribute__ ((noinline))
#endif
procedure(struct TYPE *input, struct TYPE *output) {
  for (int i = 0; i < BYTES; i += 1) {
    output->bytes[i] = input->bytes[i] + input->bytes[i];
  }
}
#endif

int main() {
  NanoprofilerAllocate(5000000);
  NanoprofilerBegin(0, "Main");

  srand(time(NULL));

  for (int i = 0; i < 10000; i += 1) {
    struct TYPE input;
    NanoprofilerBegin(0, "Generate input data");
    for (int j = 0; j < BYTES; j += 1) {
      input.bytes[j] = rand() % 255;
    }
    NanoprofilerEnd(0, "Generate input data");
    NanoprofilerBegin(0, "Procedure call");
    #if BY_VAL == 1
    procedure(input, &output);
    #else
    procedure(&input, &output);
    #endif
    NanoprofilerEnd(0, "Procedure call");
  }

  NanoprofilerEnd(0, "Main");
  NanoprofilerOutputAndFree(0);
}