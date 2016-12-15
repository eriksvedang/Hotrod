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
This will create a file called 'hot_mess.c'. In this file there will be a stub function for you to fill in. Every time the line with the macro is executed (and you have changed the source file), the code will recompile and a new version of the function will be loaded in.

## Caveats

### Global variables
To access and change global variables in your main program, define them as extern at the top of your stub source file, like so:

```c
extern int global_x;

void foo() {
    global_x = 100;
}
```

Just including sharing a header file that contains the definition of a non-extern global variable will *not* work. The dynamic library will get its own memory location for this variable (because of default static linkage). 

Better solution: Declare each global variables as 'extern' in the header file and 'static' in the implementation file (of your normal source code). Now you can use these variables by including the header file in the stub function. Since the header contains an 'extern' declaration you don't need to add that in your file, just use the variable as normal.

### Duplicated definitions
Right now it's not possible to use the same name in two different HOTROD() invocations. If you want to call the same reloadable function in several places, just call it like a normal function except for in that one place. Please note that the code will only be reloaded when the line of the macro invocation is executed.

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
