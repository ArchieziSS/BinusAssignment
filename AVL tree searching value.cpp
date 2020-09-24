//Steven Santoso Suntiarko
//2301856812

#include<stdio.h>
#include<stdlib.h>

void cls(){
	for (int i = 0; i < 50; i++){
		printf("\n");
	}
}
struct data{
	int value;
	int height; //buat AVL
	struct data *left, *right;
}*root = NULL;

struct data *createNewNode(int num){
	struct data *newNode = (struct data *) malloc (sizeof(struct data));
	newNode->value = num;
	newNode->height = 1; //buat AVL
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int getMax(int a, int b){
	if(a < b) return b;
	else return a;
}

int getHeight(struct data *node){
	if(node==NULL) return 0;
	return node->height;
}

int getBF(struct data *node){
	if(node == NULL) return 0;
	return getHeight(node->left) - getHeight(node->right);
}

struct data *rotateKeKanan(struct data *nodeX){
	struct data *nodeY = nodeX->left;
	struct data *nodeB = nodeY->right;
	
	//rotate
	nodeY->right = nodeX;
	nodeX->left = nodeB;
	
	//update height
	nodeX->height = 1+getMax(getHeight(nodeX->left), getHeight(nodeX->right));
	nodeY->height = 1+getMax(getHeight(nodeY->left), getHeight(nodeY->right));
	
	return nodeY;
}

struct data *rotateKeKiri(struct data *nodeX){
	struct data *nodeY = nodeX->right;
	struct data *nodeB = nodeY->left;
	
	//rotate
	nodeY->left = nodeX;
	nodeX->right = nodeB;
	
	//update height
	nodeX->height = 1+getMax(getHeight(nodeX->left), getHeight(nodeX->right));
	nodeY->height = 1+getMax(getHeight(nodeY->left), getHeight(nodeY->right));
	
	return nodeY;
}

struct data *insertNode(struct data *node, int num){
	if(node == NULL){ //kosong
		return createNewNode(num);
	}else if(num < node->value){ //ke kiri
		node->left = insertNode(node->left, num);
	}else if(num > node->value){ //ke kanan
		node->right = insertNode(node->right, num);
	}else{ //sama ga boleh dimasukin
		printf("TIDAK BISA INPUT VALUE YANG SAMA!\n");
	}
	
	//buat AVL
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	int BF = getBF(node);
	
	//case 1
	if(BF > 1 && num < node->left->value){
		//rotate ke kanan
		return rotateKeKanan(node);
	}
	//case 2
	if(BF < -1 && num > node->right->value){
		//rotate ke kiri
		return rotateKeKiri(node);
	}
	//case 3
	if(BF > 1 && num > node->left->value){
		//1. rotate ke kiri
		node->left = rotateKeKiri(node->left);
		//2. rotate ke kanan
		return rotateKeKanan(node);
	}
	//case 4
	if(BF < -1 && num < node->right->value){
		//1. rotate ke kanan
		node->right = rotateKeKanan(node->right);
		//2. rotate ke kiri
		return rotateKeKiri(node);
	}
	
	return node;
}

void prefix(struct data *node){
	if(node == NULL) return;
	
	printf(" %d -", node->value);
	prefix(node->left);
	prefix(node->right);
}

struct data *deleteNode(struct data *node, int num){
	if(node == NULL) return NULL;
	
	if(num < node->value){
		node->left = deleteNode(node->left, num);
	}else if(num > node->value){
		node->right = deleteNode(node->right, num);
	}else if(num == node->value){
		struct data *temp;//utk tampung sementara
		
		//case 1 = ga punya sama sekali
		if(node->left == NULL && node->right == NULL){
			free(node);
			node = NULL;
		}
		//case 2 = punya 1 anak
		else if(node->left == NULL || node->right == NULL){
			if(node->left != NULL) temp = node->left;
			else temp = node->right;
			
			*node = *temp;
			free(temp);
		}
		//case 3 = punya 2 anak
		else{
			temp = node->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			node->value = temp->value;
			node->left = deleteNode(node->left, temp->value);
		}
	}
	
	if(node == NULL) return node;
	
	node->height = 1+getMax(getHeight(node->left), getHeight(node->right));
	int BF = getBF(node);
	
	//case 1
	if(BF > 1 && getBF(node->left) >= 0){
		return rotateKeKanan(node);
	}
	//case 2
	if(BF < -1 && getBF(node->right) <= 0){
		return rotateKeKiri(node);
	}
	//case 3
	if(BF > 1 && getBF(node->left) < 0){
		node->left = rotateKeKiri(node->left);
		return rotateKeKanan(node);
	}
	//case 4
	if(BF < -1 && getBF(node->right) > 0){
		node->right = rotateKeKanan(node->right);
		return rotateKeKiri(node);
	}
	
	return node;
}

struct data *searchNode(struct data *node, int num){
	if(node == NULL) {
		printf("%d WAS NOT FOUND\n\n", num);
		return NULL;
	}
	
	if(num < node->value){
		node->left = searchNode(node->left, num);
	}else if(num > node->value){
		node->right = searchNode(node->right, num);
	}else if(num == node->value){
		printf("%d WAS FOUND!\n\n", node->value);
	}else{
		printf("%d WAS NOT FOUND!\n\n", num);
	}
	return node;
}

int main()
{
	//inserting nodes into AVL tree
	root = insertNode(root, 10);
	root = insertNode(root, 30);
	root = insertNode(root, 50);
	root = insertNode(root, 100);
	root = insertNode(root, 120);
	
	//show all nodes using prefix
	prefix(root);
	
	//searching certain node
	int input;
	do{
		printf ("\nInput number to search [0 to close the program]: ");
		scanf ("%d", &input);
		if (input != 0){
			root - searchNode (root, input);
		}
	}while (input != 0);
	
	
	
	return 0;
}
