// A small example of how the Hotrod library can be used.
// To build and run:
// $ make
// $ make run

#include "hotrod.h"

int main() {
  hotrod_print_compile_command = true; // see what compiler commands are invoked
  for(int i = 0; i < 3; i++) {
    HOTROD(stuff); // will only be compiled the first time in the loop
  }
}
