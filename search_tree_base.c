/*
 * Program skeleton for the course "Programming embedded systems"
 */

#include <stdio.h>
#include <limits.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "stm32f10x_conf.h"
#include "task.h"
#include "setup.h"
#include "assert.h"


/*
 * Program skeleton for the course "Programming embedded systems"
 */

/*-----------------------------------------------------------*/

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node nodes[64];

Node *root = NULL;

int insertNode(Node *n) {
    Node *currentNode;
    Node **currentPtr;
    
    assert(!n->left && !n->right);
    
    currentPtr = &root;
    
    while (*currentPtr) {
        currentNode = *currentPtr;
        if (n->data < currentNode->data) {
            currentPtr = &currentNode->left;
        } else if (n->data > currentNode->data) {
            currentPtr = &currentNode->right;
        } else {
            // already present
            return 0;
        }
    }
    
    *currentPtr = n;
    return 1;
}



int isBSTHelper(Node *node, int min, int max);
int isBST(Node *n);

int treeIsWellformed(void)
{
    /* checks whether the tree is well-formed */
    Node *currentNode;
    
    currentNode = root;
    
    return isBSTHelper(currentNode, INT_MIN, INT_MAX);
}


/* returns 1 if each node has data >= min and <= max
 */
int isBSTHelper(Node *node, int min, int max)
{
    /* base case 1: an empty tree is a well-formed BST */
    if (node == NULL)
        return 1;
    
    /* base case 2: tree is not well formed */
    if (node->data < min || node->data > max) {
        return 0;
    }
    
    /* recursively check all the nodes, left and right */
    return
        isBSTHelper(node->left, min, node->data - 1) &&
        isBSTHelper(node->right, node->data+1, max);
}

/* checks whether the search tree currently contains the datum d */
int contains(int d)
{
    //Node **nodePtr;
    Node *currentNode;
    
    /* start from the root of the tree */
    currentNode = root;
    
    while(currentNode != NULL) {
        if (currentNode->data == d)
            return 1;
        else if (d < currentNode->data) {
            currentNode = currentNode->left;
        }
        else if (d > currentNode->data) {
            currentNode = currentNode->right;
        }
    }
    /* end; d not found */
    return 0;
}

void deleteTree(Node *n)
{
    if (n == NULL) return;
    
    deleteTree(n->left);
    deleteTree(n->right);
    
    printf("Deleting node: %i\n", n->data);
    n->data = NULL;
    
}

int testCase(void)
{
    /* 1: initializing the search tree with data */
    int testCase0, testCase1, testCase2, testCase3, testResult;
    
    nodes[1].data = 1;
    nodes[1].left = NULL;
    nodes[1].right = NULL;
    insertNode(nodes+1);
    
    nodes[2].data = 2;
    nodes[2].left = NULL;
    nodes[3].right = NULL;
    insertNode(nodes+2);
    
    nodes[3].data = 3;
    nodes[3].left = NULL;
    nodes[3].right = NULL;
    insertNode(nodes+3);
    
    /* confirm initital tree is well-formed */
    if (treeIsWellformed())
        testCase0 = 1;
    else
        testCase0 = 0;
    
    /* 2: >=1 invocation of insertNode */
    nodes[4].data = 4;
    nodes[4].left = NULL;
    nodes[4].right = NULL;
    nodes[5].data = -5;
    nodes[5].left = NULL;
    nodes[5].right = NULL;
    insertNode(nodes+4);
    insertNode(nodes+5);
    
    /*check if tree is well-formed */
    if (treeIsWellformed()) {
        printf("Tree is well formed \n");
        testCase1 = 1;
    }
    
    else {
        printf("Tree is not well formed\n");
        testCase1 = 0;
    }
    
    /* 3: Result of 2 is checked */
    if (contains(nodes[4].data)) {
        printf("Node present, data: %i\n", nodes[4].data);
        testCase2 = 1;
    }
    else {
        printf("Node 4 absent\n");
        testCase2 = 0;
    }
    if (contains(nodes[5].data)) {
        printf("Node present, data: %i\n", nodes[5].data);
        testCase3 = 1;
    }
    else {
        printf("Node 5 not found\n");
        testCase3 = 0;
    }
    
    /* 4: Reset the tree by removing all nodes from it */
    deleteTree(root);
    root = NULL;
    
    testResult = testCase0 && testCase1 && testCase2 && testCase3;
    
    return testResult;
}

/**************************************************************/
/*
 * Entry point of program execution
 */
int main( void )
{
    
    printf("test result: %d\n", testCase());
    
    //assert(0);
    return 0;                 // not reachable
}
/*-----------------------------------------------------------*/