#include "9cc.h"
#include "state.h"

State head;
State *cur;


void gen_lval(Node *node) {
  if (node->kind != ND_LVAR)
    error("left value of assignment is not variable");
  printf("  mov rax, rbp\n");
  printf("  sub rax, %d\n", node->offset);
  printf("  push rax\n");
}

void gen(Node *node) {
  switch (node->kind) {
    case ND_NUM:
      printf("  push %d\n", node->val);
      return;
    case ND_LVAR:
      gen_lval(node);
      printf("  pop rax\n");
      printf("  mov rax, [rax]\n");
      printf("  push rax\n");
      return;
    case ND_ASSIGN:
      gen_lval(node->lhs);
      gen(node->rhs);
      //printf("  pop rdi\n");
      //printf("  pop rax\n");
      //printf("  mov [rax], rdi\n");
      //printf("  push rdi\n");
      cur = new_state(ST_ASSIGN, cur, "test", "test");
      return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind) {
    case ND_ADD:
      printf("  add rax, rdi\n");
      break;
    case ND_SUB:
      printf("  sub rax, rdi\n");
      break;
    case ND_MUL:
      printf("  imul rax, rdi\n");
      break;
    case ND_DIV:
      printf("  cqo\n");
      printf("  idiv rdi\n");
      break;
    case ND_EQ:
      printf("  cmp rax, rdi\n");
      printf("  sete al\n");
      printf("  movzb rax, al\n");
      break;
    case ND_NE:
      printf("  cmp rax, rdi\n");
      printf("  setne al\n");
      printf("  movzb rax, al\n");
      break;
  	case ND_LT:
    	printf("  cmp rax, rdi\n");
    	printf("  setl al\n");
    	printf("  movzb rax, al\n");
    	break;
  	case ND_LE:
  	  printf("  cmp rax, rdi\n");
    	printf("  setle al\n");
    	printf("  movzb rax, al\n");
    	break;
  }

  printf("  push rax\n");
}

void generate_module() {
  printf("module minihls (\n");
  printf("  input wire clk,\n");
  printf("  input wire rst,\n");
  printf("  input wire minihls_ready,\n");
  printf("  input wire minihls_accept,\n");
  printf("  output reg minihls_valid,\n");
  printf("  output reg signed [31:0] minihls_out\n");
  printf("  );\n");
}

void generate_params() {
  printf("  reg minihls_state;\n");
}

void generate_always() {
  printf("  always @(posedge clk) begin\n");
  printf("    if (rst) begin\n");
  printf("      minihls_out <= 0;\n");
  printf("      minihls_state <= ;\n");
}

void print_state() {
  State *p;
  p = &head;
  p = p->next;
  while (p != NULL) {
    printf("id = %d, src = %s, dest = %s\n", p->id, p->src, p->dest);
    p = p->next;
  }
}

void codegen_main() {

  head.next = NULL;
  cur = &head;

  generate_module();

  for (int i = 0; code[i]; i++) {
    gen(code[i]);
    //printf("  pop rax\n");
    printf("-------\n");
  }

  print_state();
}