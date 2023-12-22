
typedef enum {
 SPAWN, RESHAPE, MOVE, CLOSE, KILL, ICONIFY, LOGOUT
} what_n;

typedef struct {
 struct list_head node;
 what_n what;
 char *name;
 char *run;
} menu_entry_t;

extern menu_entry_t *menu_list;
void add_entry(what_n what, char *name, char *run);
void do_menu_item(menu_entry_t *a, XButtonEvent *e);
