# Hotrod

This is a very small library (one function + one macro) that helps you live reload C code.
It should work fine on Unix systems. Patches for making it run on Windows are most welcome!

## How to use it

### 1. Include it
```c
#include "hotrod.h"
```

### 2. Use the HOTROD macro somewhere in your code where you want a hot-reloadable function
```c
int main() {
  HOTROD(mess, 100, "hello");
}
```

This is equivalent of the following normal function call. Remember to replace it with this in production!
```c
int main() {
  mess(100, "hello");
}
```

### 3. Compile your program and run it
This will create a file called 'hot_stuff.c'. In this file there will be a stub function for you to fill in. Every time the line with the macro is executed (and you have changed the source file), the code will recompile and a new version of the function will be loaded in.

## Example
Check out 'example.c' in this repository.

## Extra options
There are a few extra options you can set from anywhere in your program (most likely at the start).

### The directory where the hotrod *.c and *.so files should be stored.
```c
hotrod_dir = "./temp";
```

### A NULL terminated list of extra include files.
```c
hotrod_extra_includes = (char*[]) { "my_engine.h", "gfx.h", NULL };
```

### A flag to enable printing of compiler command.
```c
hotrod_print_compile_command = true;
```

### A variable for changing (or removing) the prefix for files emitted by hotrod.
```c
char *hotrod_prefix = "";
```

### A variable for changing what compiler to use (default is clang).
```c
char *hotrod_compiler = "gcc";
```

# License
(C) Erik Svedäng 2016

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
