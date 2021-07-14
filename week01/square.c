#include <stdio.h>

int square(int x){
  return x * x;
}

int main(){
  int num;
  printf("Please enter a number: \n");
  scanf("%d", &num);

  printf("Square of %d is %d\n", num, square(num));
  return 0;

}