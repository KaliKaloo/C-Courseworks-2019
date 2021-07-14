#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned char byte;
enum { PGM = 1, SK = 2};

int PGMorSK(char*filename);
char *toSKname(char*filename);
void convertPGM(char *currentFile);
int getWH_pgm(FILE*from);
int PGMtoSK(byte prevByte, byte val, byte*rgba_image, int width, int PosInPGM, int PosInSK);

void whichLine(int line, bool x);
void checkPGMorSK();
void checkToSKname();
void test();

int main(int n, char* args[n] ){

    if (n==1){ 
        test();
        }
    else if(n==2){
        int filetype = PGMorSK(args[1]);
        if(filetype == PGM){
            
             convertPGM(args[1]);}

        else if(filetype == SK){
             printf("In Progress...\n");}
         
        else{
         printf("Please enter only .sk or .pgm files\n");}
    }
    else{printf("Please input filename and desired converted filename.\nE.g. ./converter name.pgm name.sk\n");}
    return 0;
}



//FUNCTIONS
int PGMorSK(char*filename){
    int len = strlen(filename);
    if((filename[len-1])=='m') return PGM;
    else return SK;
}   

char *toSKname(char*filename){
    int len = strlen(filename);
    char *newname = malloc(sizeof(char)*len);
    strncpy(newname, filename, len);
    newname[len-1] = '\0';
    newname[len-2] = 'k';
    newname[len-3] = 's';
    printf("My image %s has been created\n", newname);
    return newname;
}

void convertPGM(char *currentFile){
    char *newFile = toSKname(currentFile);
    FILE *from = fopen(currentFile, "rb");
    FILE *to= fopen( newFile, "wb");

    if(from == NULL||to== NULL){
        printf("Cannot convert image\n");
        exit(1);}

    byte ch = fgetc(from); //skip P
    for (int i = 0; i<=1; i++){ // skips 5 " "
        ch = fgetc(from);}

    int width = getWH_pgm(from), height = getWH_pgm(from), pixels = height*width;
    int maxval=0;
    ch = fgetc(from); //maxval beginning
    while (!feof(from)&&!(ch == 32 || ch == 10 || ch == 13 || ch == 9)){
        maxval = maxval*10 + ((int)ch -'0');
        ch = fgetc(from);} 

    byte rgba_image[pixels*100], prevByte = ch, val = fgetc(from);
    int PosInPGM = 0, PosInSK = 0;

    while(!feof(from) && maxval < 256){ 
        PosInSK = PosInSK + PGMtoSK(prevByte, val, rgba_image, width, PosInPGM, PosInSK); 
        prevByte = val;
        val = fgetc(from);
        PosInPGM++;}

	fwrite(rgba_image, 1, PosInSK, to);
    free(newFile);
    fclose(from);
    fclose(to);
}

int getWH_pgm(FILE*from){
    byte ch = fgetc(from);
    int result=0;
    while (!feof(from)&&!(ch == 32 || ch == 10 || ch == 13 || ch == 9)){    
        result = result*10 + ((int)ch -'0');
        ch = fgetc(from);}
    return result;
}

int PGMtoSK(byte prevByte, byte val, byte*rgba_image, int width, int PosInPGM, int PosInSK){

    int p = PosInPGM % width;
    int position = 0;
    if(val!=prevByte){

        rgba_image[PosInSK++] = 0xc0 | (val>>6);                              
        rgba_image[PosInSK++] = 0xc0 | (val & 0x3f);                          
        rgba_image[PosInSK++] = 0xc0 | ((val & 0xfc)>>2);                     
        rgba_image[PosInSK++] = 0xc0 | ((val & 0x3)<<4) | ((val & 0xf0)>>4);   
        rgba_image[PosInSK++] = 0xc0 | ((val & 0xf)<<2) | 0x3;                
        rgba_image[PosInSK++] = 0xc0 | 0x3f;                                  
        rgba_image[PosInSK++] = 0x83; //s->tool = colour
        position= position+7;
    }

    rgba_image[PosInSK++] = 0x1; //s->tx = +1
    rgba_image[PosInSK++] = 0x40; //s->ty = 0
    position= position+2;

    if(width-1 == p){
        rgba_image[PosInSK++] = 0x80; //s->tool = none
        rgba_image[PosInSK++] = 0x1; //s->tx = +1
        rgba_image[PosInSK++] = 0x81; //s->tool = Line
        rgba_image[PosInSK++] = 0x41; //s->ty = +1
        rgba_image[PosInSK++] = 0xc0; //s->data = 0
        rgba_image[PosInSK++] = 0x84; //s->tool = targetx
        position= position+6;}

    return position;
}



//TESTS
void whichLine(int line, bool x) {
  if (x){
    return;}
  else{  
  printf("The test on line %d fails.\n", line);}
  exit(1);
}

void checkPGMorSK(){
    whichLine(__LINE__, PGMorSK("random.pgm") == PGM);
    whichLine(__LINE__, PGMorSK("random.sk") == SK);
    whichLine(__LINE__, PGMorSK("sk.pgm") == PGM);
    whichLine(__LINE__, PGMorSK("pgm.sk") == SK);
    printf("PGMorSK function all OK\n");
}

void checkToSKname(){
    char *newFile = toSKname("fractal.pgm");
    whichLine(__LINE__, strncmp(newFile, "fractal.sk", 9)==0);
    printf("Newname function all OK\n");
    free(newFile);
}

void test(){
    checkPGMorSK();
    checkToSKname();
    printf("All tests Passed\n");
}
