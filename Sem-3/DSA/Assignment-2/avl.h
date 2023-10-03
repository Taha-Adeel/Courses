#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _avl_node{
	char key[100];
	struct _avl_node* parent;
	struct _avl_node* left;
	struct _avl_node* right;
	int height;
} avl_node;

avl_node* newAvlNode(char key[100]){
	avl_node* temp = (avl_node*)malloc(sizeof(avl_node));
    strcpy(temp->key, key);
	temp->parent = NULL;
    temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;

    return temp;
}

int heightOf(avl_node* node){
	if(node == NULL)
		return 0;
	else
		return node->height;
}

typedef struct avl{
	avl_node* root;
} avl_tree;

void init_avl_tree(avl_tree* tree){
	tree->root = NULL;
}

int updateHeight(avl_node* node){
	node->height = (heightOf(node->left) > heightOf(node->right)) ? heightOf(node->left) + 1 : heightOf(node->right) + 1;
	return node->height;
}

int getBalance(avl_node* node){
	if(node == NULL)
		return 0;

	return heightOf(node->left) - heightOf(node->right);
}

avl_node* minValue(avl_node* node){
	if(node == NULL)
		return NULL;
		
	while(node->left != NULL)
		node = node->left;

	return node;
}

avl_node* successor(avl_node* node){
	if(node->right != NULL){
		return minValue(node->right);
	}
	else{
		avl_node* _successor = node->parent;
		while(_successor != NULL && node == _successor->right){
			node = _successor;
			_successor = _successor->parent;
		}
		return _successor;
	}
}

avl_node* rightRotate(avl_node* root){
	avl_node* left_child = root->left;
	avl_node* right_subtree_of_left_child = left_child->right;

	// Perform rotation
	if(root->parent != NULL){
		root->parent->right = left_child;
		left_child->parent = root->parent;
	}
	else
		left_child->parent = NULL;
	left_child->right = root;
	root->parent = left_child;
	root->left = right_subtree_of_left_child;
	right_subtree_of_left_child->parent = root;

	// Update heights
	updateHeight(root);
	updateHeight(left_child);
	if(left_child->parent != NULL)
		updateHeight(left_child->parent);

	// Return new root
	return left_child;
}

avl_node* leftRotate(avl_node* root){
	avl_node* right_child = root->right;
	avl_node* left_subtree_of_right_child = right_child->left;

	// Perform rotation
	if(root->parent != NULL){
		root->parent->left = right_child;
		right_child->parent = root->parent;
	}
	else
		right_child->parent = NULL;
	right_child->left = root;
	root->parent = right_child;
	root->right = left_subtree_of_right_child;
	left_subtree_of_right_child->parent = root;

	// Update heights
	updateHeight(root);
	updateHeight(right_child);
	if(right_child->parent != NULL)
		updateHeight(right_child->parent);

	// Return new root
	return right_child;
}

avl_node* balance(avl_node* root){
	int balance_factor = getBalance(root);

	//Left-Left Case
	if(balance_factor > 1 && getBalance(root->left)>=0)
		return rightRotate(root);
	//Right-Right Case
	else if(balance_factor < -1 && getBalance(root->right)<=0)
		return leftRotate(root);
	//Left-Right Case
	else if(balance_factor > 1 && getBalance(root->left)<0){
		leftRotate(root->left);
		return rightRotate(root);
	}
	//Right-Left Case
	else if(balance_factor < -1 && getBalance(root->right)>0){
		rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

avl_node* search_avl_tree(avl_node* root, char name[100]){
	if(root == NULL)
		return NULL;

	else if(strcmp(name, root->key) == 0)
		return root;
	
	else if(strcmp(name, root->key) < 0)
		return search_avl_tree(root->left, name);

	else if(strcmp(name, root->key) > 0)
		return search_avl_tree(root->right, name);	
}

avl_node* insert_avl_tree(avl_node* root, char name[100]){
	if(root == NULL)
		return newAvlNode(name);

	else if(strcmp(name, root->key) < 0){
		root->left = insert_avl_tree(root->left, name);
		root->left->parent = root;
	}
	else if(strcmp(name, root->key) > 0){
		root->right = insert_avl_tree(root->right, name);
		root->right->parent = root;
	}
	else if(strcmp(name, root->key) == 0)
		return root;

	updateHeight(root);
	
	avl_node* balanced_node = balance(root);
	return balanced_node;
}

avl_node* delete_avl_node(avl_node* del_node){
	if(del_node->parent != NULL){
		avl_node* parent = del_node->parent;
		if(del_node->left == NULL && del_node->right == NULL){
			if(parent->left == del_node)
				parent->left = NULL;
			else
				parent->right = NULL;

			free(del_node);
			return parent;
		}
		else if(del_node->left == NULL && del_node->right != NULL){
			if(parent->left == del_node){
				parent->left = del_node->right;
				parent->left->parent = parent;
			}
			else{
				parent->right = del_node->right;
				parent->right->parent = parent;
			}
			free(del_node);
			return parent;
		}
		else if(del_node->left != NULL && del_node->right == NULL){
			if(parent->left == del_node){
				parent->left = del_node->left;
				parent->left->parent = parent;
			}
			else{
				parent->right = del_node->left;
				parent->right->parent = parent;
			}
			free(del_node);
			return parent;
		}
		else{
			avl_node* successor = del_node->right;

			while(successor->left != NULL)
				successor = successor->left;
			
			strcpy(del_node->key, successor->key);

			return delete_avl_node(successor);
		}

	}
	else{
		free(del_node);
		del_node = NULL;
		return NULL;
	}
}

void delete_from_avl_tree(avl_tree* tree, char name[100]){
	avl_node* del_node = search_avl_tree(tree->root, name);
	if(del_node != NULL){
		if(del_node != tree->root){
			avl_node* unbalanced_node = delete_avl_node(del_node);
			for(avl_node* current_node = unbalanced_node; current_node != NULL; current_node = current_node->parent){
				updateHeight(current_node);
				balance(current_node);
			}
		}
		else{
			free(del_node);
			tree->root = NULL;
		}
	}
}

#endif