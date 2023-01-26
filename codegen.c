#include "9cc.h"
#include "state.h"
#include "stack.h"

State head;
State *cur;
Stack rdi;
Stack rax;

typedef struct Variable Variable;
struct Variable {
  int value;
  char *name;
};
Variable variable_list[20];
int var_index = 0;

void gen_lval(Node *node) {
  if (node->kind != ND_LVAR)
    error("left value of assignment is not variable");
  //printf("  mov rax, rbp\n");
  //printf("  sub rax, %d\n", node->offset);
  //printf("  push rax\n");
  push(STACK_VARIABLE, node->offset);
}

void gen(Node *node) {
  switch (node->kind) {
    case ND_NUM:
      //printf("  push %d\n", node->val);
      push(STACK_NUMBER, node->val);
      return;
    case ND_LVAR:
      gen_lval(node);
      //printf("  pop rax\n");
      //printf("  mov rax, [rax]\n");
      //printf("  push rax\n");
      rax = pop();
      int value = variable_list[rax.value].value;
      push(STACK_VARIABLE, value);
      return;
    case ND_ASSIGN:
      gen_lval(node->lhs);
      gen(node->rhs);
      //printf("  pop rdi\n");
      //printf("  pop rax\n");
      //printf("  mov [rax], rdi\n");
      //printf("  push rdi\n");
      //printstack();
      rdi = pop();
      rax = pop();
      if (var_index <= rax.value) {
        var_index++;
      }
      variable_list[rax.value].value = rdi.value;
      variable_list[rax.value].name = "test";
      cur = new_state(ST_ASSIGN, cur, rax.value, rdi.value);
      push(STACK_VARIABLE, rdi.value);
      return;
  }

  gen(node->lhs);
  gen(node->rhs);

  //printstack();
  //printf("  pop rdi\n");
  //printf("  pop rax\n");
  rdi = pop();
  rax = pop();

  switch (node->kind) {
    case ND_ADD:
      //printf("  add rax, rdi\n");
      rax.value = rax.value + rdi.value;
      break;
    case ND_SUB:
      //printf("  sub rax, rdi\n");
      rax.value = rax.value - rdi.value;
      break;
    case ND_MUL:
      //printf("  imul rax, rdi\n");
      rax.value = rax.value * rdi.value;
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

  //printf("  push rax\n");
  push(STACK_VARIABLE, rax.value);
}

void generate_params() {
  printf("  localparam state_INIT = 0\n");
  for (int i = 1; i <= get_length(); i++) {
    printf("  localparam state_%d = %d\n", i, i);
  }
  printf("  reg [31:0] state;\n");
  for (int i = 0; i < var_index; i++) {
    printf("  wire signed [31:0] a%d;\n", i);
  }
}

void generate_always() {
  printf("  always @(posedge clk) begin\n");
  printf("    if (rst) begin\n");
  printf("      out = 0;\n");
  printf("      state <= state_INIT;\n");

  printf("    end else begin\n");
  printf("      case(state)\n");
  printf("      state_INIT: begin\n");
  printf("        valid <= 0;\n");
  printf("        if (ready == 1) begin\n");
  printf("          state <= state_0\n");
  printf("        end\n");
  printf("      end\n");

  State *p;
  p = &head;
  p = p->next;

  int i = 0;
  int outvalue_number = 0;
  for (i = 0; i < get_length(); i++) {
    printf("      state_%d: begin\n", i);
    if (i == 0) {
      printf("        if (accept == 1) begin\n");
      printf("          state <= state_INIT;\n");
      printf("        end\n");
    }
    printf("        a%d <= %d;\n", p->src, p->dest);
    printf("        state <= state_%d;\n", i + 1);
    printf("      end\n");
    outvalue_number = p->src;
    p = p->next;
  }

  printf("      state_%d: begin\n", i);
  printf("        valid <= 1;\n");
  printf("        if (accept == 1) begin\n");
  printf("          state <= state_INIT;\n");
  printf("        end\n");
  printf("        out <= a%d;\n", outvalue_number);
  printf("      end\n");

  printf("      endcase\n");
  printf("    end\n");
  printf("  end\n");
}

void print_state() {
  State *p;
  p = &head;
  p = p->next;
  while (p != NULL) {
    printf("id = %d, src = %d, dest = %d\n", p->id, p->src, p->dest);
    p = p->next;
  }
}

void generate_module() {
  printf("module minihls (\n");
  printf("  input wire clk,\n");
  printf("  input wire rst,\n");
  printf("  input wire ready,\n");
  printf("  input wire accept\n");
  printf("  output reg valid,\n");
  printf("  output reg out\n");
  printf("  );\n");

  generate_params();
  generate_always();

  printf("endmodule\n");
}

void codegen_main() {

  head.next = NULL;
  cur = &head;

  for (int i = 0; code[i]; i++) {
    gen(code[i]);
    //printf("  pop rax\n");
    rax = pop();
    //printf("-------\n");
  }

  generate_module();
  //printstack();
  //print_state();
}