typedef enum {
  ST_ASSIGN,
} StateKind;

typedef struct State State;

struct State {
  StateKind kind;
  State *next;
  int id;
  char *src;
  int dest;

};

State *new_state(StateKind kind, State *cur, char *src, int dest);