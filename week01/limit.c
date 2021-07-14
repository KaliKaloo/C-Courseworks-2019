/* Find the limits of the int type */
#include <stdio.h>

//use long instead of int beucase the number we are storing inside high is bigger than the int variable can store
int largestInt(int low, long high){   

  long mid = low + (high -low)/2;
  int test = mid;
  if (test == mid) 
    low = mid;
  else high = mid;
  
  if(high - low < 2)  
    return test;
  
  return largestInt(low, high);
}

int main() {
  int n = largestInt(0,2500000000);
  printf("%d\n", n);
  return 0;
}