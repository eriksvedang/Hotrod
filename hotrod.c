#include "hotrod.h"
#include <dlfcn.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/stat.h>

char *hotrod_prefix = "hot_";
char *hotrod_dir = ".";
char *hotrod_compiler = "clang";
bool hotrod_print_compile_command = false;
char **hotrod_extra_includes = (char*[]) { NULL }; /* Null terminated array of header file names. */

void hotrod_ensure_func(const char *fn_name, void **dylib_out_ptr, void **fn_out_ptr, long int *timestamp_out_ptr) {
  char *filename;
  char *dylib_name;
  asprintf(&filename, "%s/%s%s.c", hotrod_dir, hotrod_prefix, fn_name);
  asprintf(&dylib_name, "%s/%s%s.so", hotrod_dir, hotrod_prefix, fn_name);

  // Skip re-compilation if the file hasn't changed
  struct stat attr;
  if(stat(filename, &attr) == 0) { // the file exists
    if(attr.st_mtime == *timestamp_out_ptr) {
      goto cleanup;
    }
  }
  *timestamp_out_ptr = attr.st_mtime;
  
  // Ensure file
  FILE *file = fopen(filename, "r");    
  if(!file) {
    printf("Creating file %s\n", filename);
    file = fopen(filename, "w");
    assert(file);
    fprintf(file, "void %s() {\n  printf(\"%s\\n\");\n}\n", fn_name, fn_name);
  }
  fclose(file);

  // Create a long string with the extra includes
  char *extra_includes_concatenated = NULL;
  char **includes_iterator = hotrod_extra_includes;
  while(*includes_iterator) {
    if(extra_includes_concatenated) {
      free(extra_includes_concatenated);
    }
    asprintf(&extra_includes_concatenated, "-include %s ", *includes_iterator);
    includes_iterator++;
  }
  
  // Compile code
  char *compile_cmd;
  asprintf(&compile_cmd, "%s -include stdio.h %s-shared -undefined dynamic_lookup -o %s %s",
           hotrod_compiler,
           extra_includes_concatenated ? extra_includes_concatenated : "",
           dylib_name,
           filename);
  
  if(hotrod_print_compile_command) {
    printf("Hotrod compile: %s\n", compile_cmd);
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
  cleanup:
  free(filename);
  free(dylib_name);
}

