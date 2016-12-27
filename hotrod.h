#ifndef HOTROD_H
#define HOTROD_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char *hotrod_prefix;
char *hotrod_dir;
char *hotrod_compiler;
bool hotrod_print_compile_command;
char **hotrod_extra_includes;

void hotrod_ensure_func(const char *fn_name, void **dylib_out_ptr, void **fn_out_ptr, long int *timestamp_out_ptr);

#define HOTROD(name, ...)                                               \
  static void *name##_lib = NULL;                                       \
  static void (*name)() = NULL;                                         \
  static long int name##_timestamp = 0;                                 \
  hotrod_ensure_func(#name, &name##_lib, (void*)&name, &name##_timestamp); \
  name(__VA_ARGS__);

#define HOTROD_LATER(name, ...)                                         \
  hotrod_ensure_func(#name, &name##_lib, (void*)&name, &name##_timestamp); \
  name(__VA_ARGS__);

#endif
