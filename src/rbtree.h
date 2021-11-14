#if !defined(RBTREE_H)
#define RBTREE_H

enum rb_color {
	RB_RED,
	RB_BLACK
};

struct rb_node {
	unsigned long color;
	struct rb_node *left;
	struct rb_node *right;
	struct rb_node *parent;
};

struct rb_root {
	struct rb_node *node;
};

#endif /* !defined(RBTREE_H) */
