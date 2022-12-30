typedef enum {
  ST_ASSIGN,
} StateKind;

typedef struct State State;

struct State {
  StateKind kind;
  State *next;
  int id;
  int src;
  int dest;

};

State *new_state(StateKind kind, State *cur, int src, int dest);

int get_length();