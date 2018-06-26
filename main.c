#if 0
clang main.c struct.c -O0
exit
#endif

#include "nanoprofiler.h"
#include <stdlib.h>
#include <time.h>

#define NANOPROFILER_FOR_EACH(LABEL) \
  LABEL(NP_MAIN) \
  LABEL(NP_GENERATE_INPUT_DATA) \
  LABEL(NP_PROCEDURE_CALL) \

#define NANOPROFILER_LABEL_AS_ENUM(ENUM) ENUM,
#define NANOPROFILER_LABEL_AS_STRING(STRING) #STRING,
enum NANOPROFILER_ENUM {NANOPROFILER_FOR_EACH(NANOPROFILER_LABEL_AS_ENUM)};
static const char * NANOPROFILER_STRINGS[] = {NANOPROFILER_FOR_EACH(NANOPROFILER_LABEL_AS_STRING)};

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
  NanoprofilerBegin(0, NP_MAIN);

  srand(time(NULL));

  for (int i = 0; i < 10000; i += 1) {
    struct TYPE input;
    NanoprofilerBegin(0, NP_GENERATE_INPUT_DATA);
    for (int j = 0; j < BYTES; j += 1) {
      input.bytes[j] = rand() % 255;
    }
    NanoprofilerEnd(0, NP_GENERATE_INPUT_DATA);
    NanoprofilerBegin(0, NP_PROCEDURE_CALL);
    #if BY_VAL == 1
    procedure(input, &output);
    #else
    procedure(&input, &output);
    #endif
    NanoprofilerEnd(0, NP_PROCEDURE_CALL);
  }

  NanoprofilerEnd(0, NP_MAIN);
  NanoprofilerOutputAndFree(0, NANOPROFILER_STRINGS);
}