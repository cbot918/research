#include<stdio.h>

#define TEMP 30

void trans(){
  
}

void yitos(int input, char* buf){
	int res = sprintf(buf, "%d",input);
}

int main(){
  
  int a = 3;
  
  char temp[TEMP];
  yitos(a, temp);
  
  printf("%s", temp);
  

}