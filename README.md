# Hotrod

// A small example how the Hotrod library can be used

// 1. Include it!
#include "hotrod.h"

int main() {
  // 2. Somewhere in your code where you want a reloadable function, invoke the HOTROD macro:
  HOTROD(stuff);

  // Psst! You can also send arguments to the function like this:
  // HOTROD(mess, 100, "hello")

  // 3. Compile the code, and then run it!
  
  // A file called 'hot_stuff.c' will be created, containing a stub function that you're supposed to change.
  // When the line with the macro is executed again (at runtime), and the file has changed, your code will recompile.
}

int main() {
  hotrod_dir = "./temp";
  hotrod_extra_includes = (char*[]) { "heh.h", NULL };
  HOTROD(woot, 1000)
}
