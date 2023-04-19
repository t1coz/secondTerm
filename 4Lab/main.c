#include <stdio.h>
#include "binaryTree.h"
#include "menuFunctions.h"
int main(){
    Node* root = NULL;
    Node** answers = malloc(sizeof(Node*));
    menuInterface(root, answers);
    return 0;
}
