//shared object file: can be used my multiple programs.

// compile program to make it into a object file. 
// gcc –std=c11 –Wall -c -o display.o display.c –fPIC


//a shared object 
//gcc –std=c11 –Wall -shared -o libdisplay.so display.o–fPIC

//then use library as #include "display.h"
//can use already compiled code (display.o) file and use the library



// place library in /usr/lib and link to program using 
// gcc –std=c11 –Wall fractal.c –lmylib –lSDL2

// won't run until you write this:
// export LD_LIBRARY_PATH=/mnt/d/fractal:$LD_LIBRARY_PATH

//libdisplay file lives seperately
//-LSDL finds the library for you automatically

//copy libdisplay.so file into usr/lib folder
//now you can run program without having the library in the same folder.
//dont need the path of the library

// make modules, combine modules in shared objects and put it into usr/lib folder and call upon it when compiling using -L"name of so file without lib"
