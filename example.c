// A small example of how the Hotrod library can be used.
// To build and run:
// $ make
// $ make run

#include "hotrod.h"

int main() {
  hotrod_print_compile_command = true; // Turn on this flag to print compiler commands that are invoked

  for(int i = 0; i < 3; i++) {
    HOTROD(stuff); // will only be compiled the first time in the loop
    stuff(); // The function can be called from other places in the same scope
  }

  // The function is not accessible here, because of the for-loop's scope.
}
