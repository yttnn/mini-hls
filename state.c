#include "state.h"
#include <stdio.h>
#include <stdlib.h>

int state_id = 0;

State *new_state(StateKind kind, State *cur, int src, int dest) {
  State *state = calloc(1, sizeof(State));
  state->kind = kind;
  state->id = state_id;
  state->src = src;
  state->dest = dest;
  state->next = NULL;
  cur->next = state;
  state_id++;
  return state;
}

int get_length() {
  return state_id;
}