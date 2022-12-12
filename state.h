typedef enum {
  ST_ASSIGN,
} StateKind;

typedef struct State State;

struct State {
  StateKind kind;
  State *next;
  int id;
  char *src;
  char *dest;

};

State *new_state(StateKind kind, State *cur, char *src, char *dest);