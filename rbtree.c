#include<stdio.h>
#include<stdlib.h>
typedef enum { false, true } bool;

// Implementation of Data Structure based directly on Introduction to Algorithms, Cormen, psuedo-code copied directly from there

struct rbtreenode {
	struct rbtreenode *left;		// Pointer to the left child of the node
	struct rbtreenode *right;		// Pointer to the right child	of the node
	struct rbtreenode *parent;				// Pointer to the parent of the node
	uintptr_t key;										// Containing the key of
	bool color;									// This field contains the color of the node, True - Red, False - Red
};


struct rbtreenode *create(struct rbtreenode *left,
													struct rbtreenode *right,
													struct rbtreenode *parent, uintptr_t key, bool color)
{
  struct rbtreenode *new_node = malloc(sizeof(*new_node));
  if(new_node == NULL)
  {
    printf("ERROR! Unsucessful emory Allocation attempt!\n");
    exit(0);
  }
  new_node->left  = left;
  new_node->right = right;
	new_node->parent = parent;
  new_node->key = key;
	new_node->color = false;
  return new_node;
}

void show(struct rbtreenode **root)
{
  if(*root != NULL)
  {
    show(&(*root)->left);
		if((*root)->color == 1) { printf("%lu red , ", (*root)->key); }
		if((*root)->color == 0) { printf("%lu black , ", (*root)->key); }
  	show(&(*root)->right);
  }
  else
  {
    return;
  }
}

void left_rotate(struct rbtreenode *root, struct rbtreenode *x, struct rbtreenode *nilT) // Implemented Directly as mentioned by Cormen
{
	struct rbtreenode *y = x->right;
	x->right = y->left;
	if(y->left != nilT)	// check
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == nilT)
	{
		root = y;
	}
	else if(x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void right_rotate(struct rbtreenode *root, struct rbtreenode *x, struct rbtreenode *nilT) // Implemented Directly as mentioned by Cormen
{
	struct rbtreenode *y = x->left;
	x->left = y->right;
	if(y->right != nilT)	// check
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == nilT)
	{
		root = y;
	}
	else if(x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}
// void rb_insert_fixup(struct rbtreenode *root, struct rbtreenode *z, struct rbtreenode *nilT)
// {
// }


void rb_insert_fixup(struct rbtreenode *root, struct rbtreenode *z, struct rbtreenode *nilT)
{
	while(z->parent->color == true)
	{
		if(z->parent == z->parent->parent->left)		// L1
		{
			struct rbtreenode *y = z->parent->parent->right;
			if(y->color == true)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else if(z == z->parent->right)
			{
				z = z->parent;
				left_rotate(root, z, nilT);
			}
			z->parent->color = false;
			z->parent->parent->color= true;
			right_rotate(root, z->parent->parent, nilT);
		}
		else // same as L1, just with right and left exchanged
		{
			struct rbtreenode *y = z->parent->parent->left;
			if(y->color == true)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else if(z == z->parent->left)
			{
				z = z->parent;
				left_rotate(root, z, nilT);
			}
			z->parent->color = false;
			z->parent->parent->color= true;
			right_rotate(root, z->parent->parent, nilT);
		}
	}
	root->color = false;
}

void rb_insert(struct rbtreenode *root, struct rbtreenode *z, struct rbtreenode *nilT)
{
	struct rbtreenode *y = nilT;
	struct rbtreenode *x = root;
	while(x != nilT)
	{
		y = x;
		if(z->key < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	z->parent = y;
	if(y == nilT)
	{
		root = z;
	}
	else if(z->key < y->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = nilT;
	z->right = nilT;
	z->color = true;
	rb_insert_fixup(root, z, nilT);
}


void rb_delete_fixup(struct rbtreenode *root, struct rbtreenode *x, struct rbtreenode *nilT)
{
	while(x != root && x->color == false)
	{
			if(x == x->parent->left) //L1
			{
				struct rbtreenode *w = x->parent->right;
				if(w->color == true)
				{
					w->color = false;
					x->parent->color = true;
					left_rotate(root, x->parent, nilT);
					w = x->parent->right;
				}
				if(w->left->color == false && w->right->color)
				{
					w->color = true;
					x = x->parent;
				}
				else if(w->right->color == false)
				{
					w->left->color = false;
					w->color = true;
					right_rotate(root, w, nilT);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = false;
				w->right->color = false;
				left_rotate(root, x->parent, nilT);
				x = root;
			}
			else // same as L2, just with right and left exchanged
			{
				if(x == x->parent->right) //L1
				{
					struct rbtreenode *w = x->parent->left;
					if(w->color == true)
					{
						w->color = false;
						x->parent->color = true;
						left_rotate(root, x->parent, nilT);
						w = x->parent->left;
					}
					if(w->right->color == false && w->left->color)
					{
						w->color = true;
						x = x->parent;
					}
					else if(w->left->color == false)
					{
						w->right->color = false;
						w->color = true;
						right_rotate(root, w, nilT);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = false;
					w->left->color = false;
					left_rotate(root, x->parent, nilT);
			}
		}
	}
	x = root;
}

struct rbtreenode *tree_minimum(struct rbtreenode *x, struct rbtreenode *nilT)
{
	while(x->left != nilT)
	{
		x = x->left;
	}
	return x;
}

struct rbtreenode *tree_successor(struct rbtreenode *x, struct rbtreenode *nilT)
{
	if(x->right != nilT)
	{
		return tree_minimum(x->right, nilT);
	}
	struct rbtreenode *y = x->parent;
	while(y != nilT && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

struct rbtreenode *rb_delete(struct rbtreenode *root, struct rbtreenode *z, struct rbtreenode *nilT)
{
	struct rbtreenode *x = NULL;
	struct rbtreenode *y = NULL;
	if(z->left == nilT || z->right == nilT)
	{
		y = z;
	}
	else
	{
		y = tree_successor(z, nilT);
	}
	if(y->left != nilT)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	x->parent = y->parent;
	if(y->parent == nilT)
	{
		root = x;
	}
	else if(y == y->parent->left)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}
	if(y != z)
	{
		z->key = y->key;
	}
	if(y->color == false)
	{
		rb_delete_fixup(root, x, nilT);
	}
	return y;
}


int main(int argc, char **argv)
{

	char *cz1, *cz2, *cz3;
	printf("\nz1:%lu\n", (uintptr_t)(&cz1));
	printf("\nz2:%lu\n", (uintptr_t)(&cz2));
	printf("\nz3:%lu\n", (uintptr_t)(&cz3));
	struct rbtreenode *nilT = create(NULL, NULL, NULL, 0, false);

	struct rbtreenode *root = create(nilT, nilT, nilT, (uintptr_t)(&cz1), false);

	struct rbtreenode *z1  = create(NULL, NULL, NULL, (uintptr_t)(&cz2), false);
	struct rbtreenode *z2  = create(NULL, NULL, NULL, (uintptr_t)(&cz3), false);
	printf("\n");
	show(&root);
	rb_insert(root,z1, nilT);
	printf("\n");
	show(&root);
	rb_insert(root,z2, nilT);
	printf("\n");
	show(&root);
	printf("\n");
	struct rbtreenode *y = rb_delete(root, z1, nilT);
	show(&root);
	printf("\n");

	//root->left->left = create(NULL, NULL, root->left->left, 2, false);
	//printf("\nHello %p\n", z->parent->parent->parent->parent->parent->parent);
}
