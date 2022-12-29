#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stack[100];
int last_index = 0;

void push(StackKind kind, int value) {
  stack[last_index].kind = kind;
  stack[last_index].value = value;
  last_index++;
}

Stack pop() {
  if (last_index == 0) {
    printf("stack underflow!!\n");
    exit(1);
  }
  Stack s = stack[last_index-1];
  last_index--;
  return s;
}

void printstack() {
  printf("printstack: ");
  for(int i = 0; i < last_index; i++) {
    printf("[%d, %d]", stack[i].kind, stack[i].value);
  }
  printf("\n");
}