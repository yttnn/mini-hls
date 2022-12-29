typedef enum {
  STACK_NUMBER,
  STACK_VARIABLE,
} StackKind;

typedef struct Stack Stack;

struct Stack {
  StackKind kind;
  int value;

};

void push(StackKind kind, int value);
Stack pop();

void printstack();