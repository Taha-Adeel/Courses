#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bst_node {
	char key[100];
	struct bst_node* parent;
	struct bst_node* left;
	struct bst_node* right;
} bst_node;

bst_node* newNode(char key[100]){
	bst_node* temp = (bst_node*)malloc(sizeof(bst_node));
    strcpy(temp->key, key);
	temp->parent = NULL;
    temp->left = NULL;
	temp->right = NULL;

    return temp;
}

typedef struct _bst{
	bst_node *root;
	int size;
} bst;

void init_bst(bst *tree){
	tree->root = NULL;
	tree->size = 0;
}

bst_node* search_bst(bst *tree, char name[100]){
	bst_node* current_node = tree->root;

	while(current_node != NULL){
		if(strcmp(name, current_node->key) < 0)
			current_node = current_node->left;

		else if(strcmp(name, current_node->key) > 0)
			current_node = current_node->right;

		else if(strcmp(name, current_node->key) == 0)
			return current_node;
	}

	return NULL;
}

void insert_bst(bst *tree, char name[100]){
    if(tree->root == NULL){
        tree->root = newNode(name);
		tree->size++;
		return;
	}

	bst_node* current_node = tree->root;

	while(true){
		if(strcmp(name, current_node->key) < 0){
			if(current_node->left == NULL){
				current_node->left = newNode(name);
				current_node->left->parent = current_node;
				tree->size++;
				return;
			}
			else
				current_node == current_node->left;
		}
		else if(strcmp(name, current_node->key) > 0){
			if(current_node->right == NULL){
				current_node->right = newNode(name);
				current_node->right->parent = current_node;
				tree->size++;
				return;
			}
			else
				current_node = current_node->right;
		}
		else if(strcmp(name, current_node->key) == 0)
			return;
	}
}

void delete_node(bst_node* del_node){
	bst_node* parent = del_node->parent;
	if(del_node->left == NULL && del_node->right == NULL){
		if(parent->left == del_node)
			parent->left = NULL;
		else
			parent->right = NULL;

		free(del_node);
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
	}
	else{
		bst_node* successor = del_node->right;

		while(successor->left != NULL)
			successor = successor->left;
		
		strcpy(del_node->key, successor->key);

		delete_node(successor);
	}

	return;
}

void delete_from_bst(bst *tree, char name[100]){
	bst_node* del_node = search_bst(tree, name);
	if(del_node != NULL){
		if(del_node->parent != NULL){
			delete_node(del_node);
		}
		else{
			free(del_node);
			tree->root = NULL;
		}
		tree->size--;
	}

	return;
}

void construct_bst_from_preorder(bst* tree, char array[][100], int size){
	for(int i=0; i<size; ++i){
		insert_bst(tree, array[i]);
	}
}

#endif