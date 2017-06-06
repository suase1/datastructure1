#include <stdio.h>
#include <stdlib.h>
enum { RED, BLACK, NONE };
typedef struct Node Node;
typedef Node* NodePtr;
struct Node
{
	int key;
	NodePtr parent;
	NodePtr left;
	NodePtr right;
	int color;
};

typedef struct RBT RBT;
typedef RBT* RBTPtr;
struct RBT
{
	NodePtr root;
};

NodePtr Tnull_alloc()
{
	NodePtr Tnull = (NodePtr)malloc(sizeof(Node));
	Tnull->key = NULL;
	Tnull->parent = NULL;
	Tnull->left = NULL;
	Tnull->right = NULL;
	Tnull->color = BLACK;
	return Tnull;
}

NodePtr node_alloc(int k, NodePtr Tnull)
{
	NodePtr self = (NodePtr)malloc(sizeof(Node));
	self->key = k;
	self->parent = Tnull;
	self->left = Tnull;
	self->right = Tnull;
	self->color = NONE;
	return self;
}

RBTPtr rbt_alloc(NodePtr Tnull)
{
	RBTPtr self = (RBTPtr)malloc(sizeof(RBT));
	self->root = Tnull;
	return self;
}

Right_rotate(RBTPtr rbt, NodePtr tree, NodePtr x, NodePtr Tnull)
{
	NodePtr z = (NodePtr)malloc(sizeof(Node));
	z = x->left;
	x->left = z->right;
	if (z->right != Tnull)
		z->right->parent = x;
	z->parent = x->parent;
	if (x->parent == Tnull)
		rbt->root = z;
	else if (x == x->parent->left)
		x->parent->left = z;
	else
		x->parent->right = z;
	z->right = x;
	x->parent = z;
}

Left_rotate(RBTPtr rbt, NodePtr tree, NodePtr x, NodePtr Tnull)
{
	NodePtr z = (NodePtr)malloc(sizeof(Node));
	z = x->right;
	x->right = z->left;
	if (z->left != Tnull)
		z->left->parent = x;
	z->parent = x->parent;
	if (x->parent == Tnull)
		rbt->root = z;
	else if (x == x->parent->left)
		x->parent->left = z;
	else
		x->parent->right = z;
	z->left = x;
	x->parent = z;
}

void rbt_insert_fixup(RBTPtr rbt, NodePtr tree, NodePtr n, NodePtr Tnull)
{
	NodePtr y = (NodePtr)malloc(sizeof(Node));
	while (n->parent->color == RED)
	{
		if (n->parent == n->parent->parent->left)
		{
			y = n->parent->parent->right;
			if (y->color == RED)
			{
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			else if (n == n->parent->left)
			{
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				Right_rotate(rbt, rbt->root, n->parent->parent, Tnull);
			}
			else if (n == n->parent->right)
			{
				n = n->parent;
				Left_rotate(rbt, rbt->root, n, Tnull);
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				Right_rotate(rbt, rbt->root, n->parent->parent, Tnull);
			}
		}
		else
		{
			y = n->parent->parent->left;
			if (y->color == RED)
			{
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			else if (n == n->parent->right)
			{
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				Left_rotate(rbt, rbt->root, n->parent->parent, Tnull);
			}
			else if (n == n->parent->left)
			{
				n = n->parent;
				Right_rotate(rbt, rbt->root, n, Tnull);
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				Left_rotate(rbt, rbt->root, n->parent->parent, Tnull);
			}
		}
	}
	rbt->root->color = BLACK;
}

void rbt_insert(RBTPtr rbt, NodePtr tree, NodePtr n, NodePtr Tnull)
{
	NodePtr z = Tnull;
	NodePtr x = (NodePtr)malloc(sizeof(Node));
	x = rbt->root;
	while (x != Tnull)
	{
		z = x;
		if (n->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	n->parent = z;
	if (z == Tnull)
		rbt->root = n;
	else if (n->key < z->key)
		z->left = n;
	else
		z->right = n;
	n->right = Tnull;
	n->left = Tnull;
	n->color = RED;
	rbt_insert_fixup(rbt, tree, n, Tnull);
}

void rbt_print(RBTPtr rbt, NodePtr tree, NodePtr Tnull, int level)
{
	if (tree->right != Tnull)
		rbt_print(rbt, tree->right, Tnull, level + 1);
	for (int i = 0; i < level; i++)
	{
		printf("	");
	}
	if (tree->color == RED)
		printf("%d(red)\n", tree->key);
	else
		printf("%d(black)\n", tree->key);
	if (tree->left != Tnull)
		rbt_print(rbt, tree->left, Tnull, level + 1);

	printf("\n");
}

void rb_transplant(RBTPtr rbt, NodePtr tree, NodePtr u, NodePtr v, NodePtr Tnull)
{
	if (u->parent == Tnull)
		rbt->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

NodePtr rb_search(RBTPtr rbt, NodePtr tree, int k, NodePtr Tnull)
{
	NodePtr x = tree;
	while (x->key != k && x != Tnull)
	{
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

NodePtr rb_minimum(NodePtr z, NodePtr Tnull)
{
	NodePtr x = z;
	while (x->left != Tnull)
		x = x->left;
	return x;
}

void rb_delete_fixup(RBTPtr rbt, NodePtr tree, NodePtr x, NodePtr Tnull)
{
	NodePtr w;
	while (x != rbt->root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				Left_rotate(rbt, tree, x->parent, Tnull);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->left->color == BLACK)
			{
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				Left_rotate(rbt, tree, x->parent, Tnull);
				x = rbt->root;
			}
			else
			{

				w->left->color = BLACK;
				w->color = RED;
				Right_rotate(rbt, tree, w, Tnull);
				w = x->parent->right;
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				Left_rotate(rbt, tree, x->parent, Tnull);
				x = rbt->root;
			}
		}
		else
		{
			w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				Right_rotate(rbt, tree, x->parent, Tnull);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->right->color == BLACK)
			{
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				Right_rotate(rbt, tree, x->parent, Tnull);
				x = rbt->root;
			}
			else
			{

				w->right->color = BLACK;
				w->color = RED;
				Left_rotate(rbt, tree, w, Tnull);
				w = x->parent->left;
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				Right_rotate(rbt, tree, x->parent, Tnull);
				x = rbt->root;
			}
		}
	}
	x->color = BLACK;
}


void rb_delete(RBTPtr rbt, NodePtr tree, int k, NodePtr Tnull)
{
	NodePtr z = rb_search(rbt, tree, k, Tnull);
	NodePtr y;
	y = z;
	int y_original_color = y->color;
	NodePtr x;
	if (z->left == Tnull)
	{
		x = z->right;
		rb_transplant(rbt, tree, z, z->right, Tnull);
	}
	else if (z->right == Tnull)
	{
		x = z->left;
		rb_transplant(rbt, tree, z, z->left, Tnull);
	}
	else
	{
		y = rb_minimum(z->right, Tnull);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else
		{
			rb_transplant(rbt, tree, y, y->right, Tnull);
			y->right = z->right;
			y->right->parent = y;
		}
		rb_transplant(rbt, tree, z, y, Tnull);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == BLACK)
		rb_delete_fixup(rbt, tree, x, Tnull);
}


void rb_inorder_traversal(RBTPtr rbt, NodePtr tree, NodePtr Tnull)
{
	NodePtr x = tree;
	if (x == Tnull)
	{
		return 0;
	}
	else
	{
		rb_inorder_traversal(rbt, x->left, Tnull);
		printf("  %d  \n", x->key);
		rb_inorder_traversal(rbt, x->right, Tnull);
	}
}



void push(NodePtr *stk, int *top, NodePtr x)
{
	*top = *top + 1;
	stk[*top] = x;
}
NodePtr pop(NodePtr *skt, int *top)
{
	NodePtr k;
	*top = *top - 1;
	k = skt[*top + 1];
	return k;
}
int empty(int *top)
{
	if (*top == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
#define STKSZ 100
NodePtr nb_count(RBTPtr rbt, NodePtr tree, NodePtr Tnull)
{
	int nb = 0;
	NodePtr x = tree;
	if (x == Tnull)
		return 0;
	NodePtr STK[STKSZ];
	int top = 0;
	while (1)
	{
		if (x != Tnull)
		{
			push(STK, &top, x);
			x = x->left;
		}
		else
		{
			if (empty(&top) == 1)
			{
				break;
			}
			x = pop(STK, &top);
			if (x->color == BLACK)
			{
				nb++;
			}
			x = x->right;
		}
	}
	return nb;
}

void Discriminate(RBTPtr rbt, NodePtr tree, int *count, int *nothing, int *nb, int *bh, int k, NodePtr Tnull)
{
	NodePtr x;
	x = tree;
	if (k > 0)
	{
		rbt_insert(rbt, tree, node_alloc(k, Tnull), Tnull);
		*count = *count + 1;
	}
	else if (k < 0)
	{
		k = -k;
		if (rb_search(rbt, tree, k, Tnull) != Tnull)
		{
			rb_delete(rbt, tree, k, Tnull);
			*count = *count - 1;
		}
		else
		{
			*nothing = *nothing + 1;
		}
	}
	else
	{
		printf(" total = %d\n", *count);
		printf(" nb = %d\n", nb_count(rbt, tree, Tnull));
		while (x != Tnull)
		{
			x = x->left;
			if (x->color == BLACK)
			{
				*bh = *bh + 1;
			}
		}
		printf(" bh = %d\n", *bh - 1);
		rb_inorder_traversal(rbt, tree, Tnull);



	}
}




void main() 
{
	FILE *fp;
	int data;

	NodePtr Tnull = Tnull_alloc();
	RBTPtr rbt = rbt_alloc(Tnull);
	int count = 0;
	int nothing = 0;
	int nb = 0;
	int bh = 1;

	fp = fopen("C:\\Users\\user\\Desktop\\input.txt", "r");

	while (fscanf_s(fp, "%d", &data) != EOF) 
	{
		Discriminate(rbt, rbt->root, &count, &nothing, &nb, &bh, data, Tnull);
	}
	//rbt_print(rbt, rbt->root, Tnull, 0);
	printf("\n##############################\n");
	fclose(fp);
	return 0;
}