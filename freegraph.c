#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "freegraph.h"

/**
 * List of graph nodes
 */
struct List {
    // node content
    struct A *node;
    // next list item
    struct List *next;
};
struct List *head = NULL;
struct List *current = NULL;

/**
 * Create a new list of nodes
 */
struct List *newList(struct A *node) {
    // allocate space for a list item
    struct List *listItem = (struct List *) malloc(sizeof(struct List));
    if (!listItem) {
        return NULL;
    }

    // point to the given node with no following list items
    listItem->node = node;
    listItem->next = NULL;

    // single item list so set head and current to the item
    head = current = listItem;
    return listItem;
}

/**
 * Add a node to the list
 */
struct List *addToList(struct A *node) {
    // list doesn't exist, create one
    if (!head) {
        return (newList(node));
    }

    // allocate space for a list item
    struct List *listItem = (struct List *) malloc(sizeof(struct List));
    if (!listItem) {
        return NULL;
    }

    // point to the given node with no following list items
    listItem->node = node;
    listItem->next = NULL;

    // set the next item in the list
    current->next = listItem;
    current = listItem;
    return listItem;
}

/**
 * Search for a node in the list
 */
struct List *searchInList(struct A *node, struct List **previous) {
    struct List *listItem = head;
    struct List *temp = NULL;
    bool found = false;

    while (listItem) {
        if (listItem->node == node) {
            found = true;
            break;
        }
        else {
            temp = listItem;
            listItem = listItem->next;
        }
    }

    if (found) {
        if (previous)
            *previous = temp;
        return listItem;
    }
    else {
        return NULL;
    }
}

/**
 * Free all the list items
 */
void freeList() {
    struct List *listItem = head;
    struct List *nextItem;

    while (listItem) {
        nextItem = listItem->next;
        // free the list item
        free(listItem);
        listItem = nextItem;
    }

    head = NULL;
    current = NULL;
}

/**
 * Free all list items and their nodes
 */
void freeListAndNodes() {
    struct List *listItem = head;
    struct List *nextItem;

    while (listItem) {
        nextItem = listItem->next;
        // free the content of the list item
        free(listItem->node);
        // free the list item
        free(listItem);
        listItem = nextItem;
    }

    head = NULL;
    current = NULL;
}

/**
 * Add all connected nodes for a given node to the list
 */
void addConnectedToList(struct A *node) {
    // check if node is in the list
    if (!searchInList(node, NULL)) {
        // add pointer and all sub-pointers to the list
        addToList(node);
        if (node->a) addConnectedToList(node->a);
        if (node->b) addConnectedToList(node->b);
        if (node->c) addConnectedToList(node->c);
    }
}

/**
 * Recursive addition of node values
 */
long sumAHelper(struct A *node) {
    // reset this sum
    long sum = 0;

    // check if the pointer has been visited
    if (!searchInList(node, NULL)) {
        // add the pointer to the list of visited
        addToList(node);

        // sumA of pointers a, b, c + n value
        sum += node->n;
        if (node->a) sum += sumAHelper(node->a);
        if (node->b) sum += sumAHelper(node->b);
        if (node->c) sum += sumAHelper(node->c);
    }
    return sum;
}

/**
 * Sum all elements of a graph from a given node
 */
long sumA(struct A *node) {
    // get the sum of all nodes from this pointer
    long sum = sumAHelper(node);
    // clear the visited pointers list
    freeList();

    return sum;
}

/**
 * Deallocate memory for all nodes connected from a given node
 */
void deallocateA(struct A *node) {
    // add nodes from this pointer to a list
    addConnectedToList(node);
    // free the node and list pointers
    freeListAndNodes();
}