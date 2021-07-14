#include "displayfull.h"
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Allocate memory for a drawing state and initialise it
state *newState() {
  //TO DO
  state *s = malloc(sizeof(state));
  s->x = 0;
  s->y = 0; 
  s->tx = 0;
  s->ty = 0;
  s->tool = LINE;
  s->start = 0;
  s->end = 0;
  s->data = 0;
  return s; 
}

// Release all memory associated with the drawing state
void freeState(state *s) {
  free(s);
} 

// Extract an opcode from a byte (two most significant bits).
int getOpcode(byte b) {
  int opcode = (b & 0xC0)>>6;
  return opcode; 
}

// Extract an operand (-32..31) from the rightmost 6 bits of a byte.
int getOperand(byte b) {
  int sixthbit = (b & 0x20)>>5;     
  int operand  = (b & 0x1f);
  if(sixthbit == 1){
        operand = (operand)+(-32);
        return operand;}
  return operand; 
}


void D_DX(state*s, int operand){
    s->tx = (s->tx)+operand;}

void D_DY(display *d, state*s, int operand){
    s->ty = (s->ty)+operand;
    
    if((s->tool) == LINE){
        line(d, s->x, s->y, s->tx, s->ty);}  

    else if( s->tool ==BLOCK){
        block(d, s->x, s->y, abs((s->tx)-(s->x)), abs((s->ty)-(s->y)));
    }  
    s->x = s->tx;
    s->y = s->ty;
}

void D_Tool(display *d, state *s, int operand){
    switch (operand){
        case LINE:
            s->tool = LINE;
            break;
        case NONE:
            s->tool = NONE;
            break;
        case BLOCK:
            s->tool = BLOCK;
            break;
        case COLOUR:
            colour(d, s->data);
            break;
        case TARGETX:
            s->tx = s->data;
            break;
        case TARGETY: 
            s->ty = s->data;
            break;
        case SHOW:
            show(d);
            break;
        case PAUSE:
            pause(d, s->data);
            break;
        case NEXTFRAME:
            s->end = 1;
            break;
    }
    s->data = 0;
}

void D_Data(state *s, int operand){
    s->data = ((s->data)<<6)|(operand & 63);
}

// Execute the next byte of the command sequence.
void obey(display *d, state *s, byte op) {
  int opcode = getOpcode(op);   
  int operand = getOperand(op);

  switch(opcode){
      case DATA:
        D_Data(s, operand);
        break;
      case TOOL:
        D_Tool(d, s, operand);
        break;
      case DX:
        D_DX(s, operand);
        break;
      case DY:
        D_DY(d, s, operand);
        break;
  }
    s->start ++;
}

// Draw a frame of the sketch file. For basic and intermediate sketch files
// this means drawing the full sketch whenever this function is called.
// For advanced sketch files this means drawing the current frame whenever
// this function is called.
bool processSketch(display *d, void *data, const char pressedKey) {
    if(data == NULL){ 
        return (pressedKey == 27);}
        
        char *filename = getName(d);
        FILE *sketch = fopen(filename, "rb");
        state *s = (state*) data;
        fseek(sketch, s->start, 0);
        
        byte op = fgetc(sketch);
        while (!feof(sketch)&& (s->end != 1)) {
            obey(d, s, op);
            op = fgetc(sketch);
        }
        if (feof(sketch)){
            s->start = 0;
        }
        
        fclose(sketch);
        show(d);
        s->x=0;
        s->y=0;
        s->tx=0;
        s->ty=0;
        s->tool=LINE;
        s->data=0;
        s->end=0;
        return (pressedKey == 27);
}

// View a sketch file in a 200x200 pixel window given the filename
void view(char *filename) {
  display *d = newDisplay(filename, 200, 200);
  state *s = newState(); //new drawing state
  run(d, s, processSketch); //repeatedly call processSketch function
  freeState(s); 
  freeDisplay(d);
}

// Include a main function only if we are not testing (make sketch),
// otherwise use the main function of the test.c file (make test).

//2 compilation methods, testing or running
#ifndef TESTING
int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./sketch file\n");
    exit(1);
  } else view(args[1]); // otherwise view sketch file in argument
  return 0;
}
#endif
