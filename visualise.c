#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

int convert( const char numberS[]);
int sign (int decimal);
int IntorFloat(double pointedNum);
int toBinary(long decimal, int bitlength, int sign);
int fTObin (long double floatingNumber);

void whichLine(int line, bool x);
void checkConvert();
void checkSign();
void checkMaxMin();
void checkIntorFloat();
void test();


int main( int n, char *args[]){   

  if (n==1){
    test();}

  else if (n == 3){
    int bitlength = 0;
    if (strcmp(args[1], "char") == 0) {bitlength = (sizeof(char)*8);}
    else if (strcmp(args[1], "int") == 0) {bitlength = (sizeof(int)*8);}
    else if (strcmp(args[1], "long") == 0) {bitlength = (sizeof(long)*8);}
    else {printf("Invalid type. Use char, int, long");}
    
    char *a = args[2];
    double x = atof(a);
    int IorF = IntorFloat(x);
    int b = sign(x);
    printf("Sign bit: %d \n",b );
    printf("Binary: ");
    if (IorF == 1){
      toBinary (x, bitlength, b);
    }else{
      fTObin (x);}}
    
  else{
    printf(" Use e.g. ./visualise char 7\n");
    exit(1);}
  
  printf("\n");

  return 0;
}


//FUNCTIONS -----------------------------------------------------------------------

int convert( const char numberS[]){
  if(isalpha(numberS[0])){
    printf("-------------------------------\nInvalid input, please try again\n-------------------------------"); printf("\n");
    return -1;
  }else{if(numberS[0] =='-'){
      if(numberS[1] == '0'){
        const char *NumberS = numberS;
        char *str;
        long a = (int) strtol(NumberS, &str, 16);
        return a;}
      else{long a = atoi(numberS);
      return a;}}
    else if(numberS[0] =='0'){
      const char *NumberS = numberS;
      char *str;
      long a = (int) strtol(NumberS, &str, 16);
      return a;}
    else {long a = atoi(numberS);
      return a;}}
  return 0;}


int sign (int decimal){
  int result = 0; 
  if (decimal >= 0){
    result = 0;}
  else {
    result = 1;}
  return result;
}

int IntorFloat(double pointedNum){
  int whole = (int)pointedNum;
  if(pointedNum == whole){
    int x = 1; //int
    return x;}
  else{ int x = 2; //float
  return x;
  }return 0;
}


int toBinary(long decimal, int bitlength, int sign){
  if (((decimal > INT_MAX) || (decimal < INT_MIN))){
    return -1;}
  int binaryarr[bitlength+1];
  int revBinaryarr[bitlength+1];
  int bit = 0;
  for ( int i =(bitlength-1); i >=0; i--){  //repeats for each bit
    bit = decimal >> i; //shifts bit i spaces to right. if char, i=7
    if(bit & 1) { binaryarr[i] = 1;} //saving into array
    else {binaryarr[i]= 0;}} 
   
  int m = bitlength-1; //reversing array
  for (int p = 0; p < bitlength; p++){
      revBinaryarr[m] = binaryarr[p];
      m--;}

  for (int n = 0; n < bitlength; n++){ //printing reversed array
     printf("%d ", revBinaryarr[n]);}
  return 0;}


int fTObin (long double floatingNumber){
  int copyInt = floatingNumber;
  float floatpart = floatingNumber - copyInt;
  int binaryInt[100], i = 0, n = 0;
  while(copyInt != 0){
    binaryInt[i] = copyInt%2;    //remainder from dividing by 2
    copyInt = copyInt/2;
    i++;}
  for (int m = (i-1); m >=0; m--){ 
     printf("%d", binaryInt[m]);}
  printf(".");
  int p = 0;
  while( floatpart != 0){
    floatpart = floatpart*2;
    n = floatpart; //just int part. e.g. 1.5 -> 1
    floatpart = floatpart - 1;
    printf("%d",n);
    p++;}
  return 0;}


// Tests -------------------------------------------------------------------

void whichLine(int line, bool x) {
  if (x){
    return;}
  else{  
  printf("The test on line %d fails.\n", line);}
  exit(1);
}

void checkConvert(){
  whichLine(__LINE__, convert("7") == 7);
  whichLine(__LINE__, convert("-7") == -7);
  whichLine(__LINE__, convert("-10") == -10);
  whichLine(__LINE__, convert("0x7") == 7);
  whichLine(__LINE__, convert("-0x7") == -7);
  whichLine(__LINE__, convert("a") == -1);
}

void checkSign(){
  whichLine (__LINE__, sign(-1) == 1);
  whichLine (__LINE__, sign(1) == 0);
}

void checkMaxMin(){
  whichLine(__LINE__, toBinary(2147483648, 8, 0) == -1);
  whichLine(__LINE__, toBinary(-2147483649, 8, 0) == -1);
}

void checkIntorFloat(){
  whichLine(__LINE__, IntorFloat(2) == 1);
  whichLine(__LINE__, IntorFloat(2.5) == 2);
}



void test(){
  checkConvert();
  checkSign();
  checkMaxMin();
  checkIntorFloat();
  printf("All tests passed \n");
}



