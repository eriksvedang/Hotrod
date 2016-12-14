#include "hotrod.h"
#include <dlfcn.h>
#include <unistd.h>
#include <assert.h>

char *hotrod_prefix = "hot_";
char *hotrod_dir = ".";
char *hotrod_compiler = "clang";
bool hotrod_print_compile_command = true;
char **hotrod_extra_includes = (char*[]) { NULL }; /* Null terminated array of header file names. */

void hotrod_ensure_func(const char *fn_name, void **dylib_out_ptr, void **fn_out_ptr) {
  char *filename;
  char *dylib_name;
  asprintf(&filename, "%s/%s%s.c", hotrod_dir, hotrod_prefix, fn_name);
  asprintf(&dylib_name, "%s/%s%s.so", hotrod_dir, hotrod_prefix, fn_name);

  // Ensure file
  FILE *file = fopen(filename, "r");
  if(!file) {
    printf("Creating file %s\n", filename);
    file = fopen(filename, "w");
    assert(file);
    fprintf(file, "void %s() {\n  printf(\"%s\\n\");\n}\n", fn_name, fn_name);
  }
  fclose(file);

  // Create a long string with the extra includes (TODO: fix memory leaks)
  char *extra_includes_concatenated = "";
  char **includes_iterator = hotrod_extra_includes;
  while(*includes_iterator) {
    asprintf(&extra_includes_concatenated, "-include %s ", *includes_iterator);
    includes_iterator++;
  }
  
  // Compile code
  char *compile_cmd;
  asprintf(&compile_cmd, "%s -include stdio.h %s-shared -o %s %s",
           hotrod_compiler,
           extra_includes_concatenated,
           dylib_name,
           filename);
  
  if(hotrod_print_compile_command) {
    printf("%s\n", compile_cmd);
  }
  
  system(compile_cmd);

  // Load function from library 
  if(*dylib_out_ptr) {
    dlclose(*dylib_out_ptr);
  }
  *dylib_out_ptr = dlopen(dylib_name, RTLD_LAZY);
  if(!*dylib_out_ptr) {
    fprintf (stderr, "%s\n", dlerror());
    exit(1);
  }
  
  *fn_out_ptr = dlsym(*dylib_out_ptr, fn_name);

  // Cleanup
  free(filename);
  free(dylib_name);
}

