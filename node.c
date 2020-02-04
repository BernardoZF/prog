/**
* @file node.c
* @author Bernardo zambrano && Alvaro Platon
* @date 4 February 2020
* @version 1.0
* @brief TAD Node
**
@details
**
@see
*/

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 struct _Node{
    char name [NAME_L]; /*!<Node name */
    long id;            /*!<Node id*/
    int nConnect;       /*!<Node number of connections*/
    Label label;        /*!<Node state*/
};


Node * node_init()
{

    Node *n=NULL;

    n=(Node *)malloc(sizeof(Node));
    if(!n){
        return NULL;
    }


    strcpy(n->name, "");
    n->id=-1;
    n->nConnect=0;
    n->label=WHITE;

    return n;
}

void node_free(void *n)
{
    if(!n)
        return;

    free(n);

return;
}

long node_getId(const Node * n)
{
    if(!n)
    return -1;

    return n->id;
}

const char* node_getName(Node *n)
{

    if(!n)
        return NULL;

    return n->name;
}

int node_getConnect(const Node *n)
{

    if(!n)
        return -1;
    
    return n->nConnect;
}

Label node_getLabel(const Node * n)
{

    if(!n)
        return ERROR_NODE;

    return n->label;
}

Status node_setLabel(Node *n, Label l)
{

    if(!n || l == ERROR_NODE)
        return ERROR;

    n->label=l;

    return OK;
}

Status node_setId(Node * n, const long id)
{

    if(!n || id < 0)
        return ERROR;
    
    n->id=id;
    return OK;
}

Status node_setName (Node * n, const char * name)
{

    if(!n || !name)
        return ERROR;
    
    strcpy(n->name,name);
    return OK;
}

Status node_setNConnect(Node * n, const int cn)
{

    if(!n || cn < 0 )
        return ERROR;

    n->nConnect=cn;
    return OK;
}

int node_cmp(const void * n1, const void * n2)
{
    int cmp=0;
    Node *node1, *node2;


    if(!n1 || !n2){
        printf("ERROR in the arguments");
        return -2;
    }

    node1=(Node *)n1;
    node2=(Node *)n2;

    if(node_getId(node1) == node_getId(node2)){
        cmp=0;
        return cmp;
    }

    cmp=strcmp(node_getName(node1),node_getName(node2));

    if(cmp<0)
        return -1;
    else if(cmp == 0)
        return 0;
    else
        return 1;

    return -2;
}

void *node_copy (const void *src)
{
    Node *cpy, *source;

    
    if(!src)
        return NULL;

    cpy=node_init();
    source =(Node *)src;

    node_setId(cpy, node_getId(source));
    node_setName(cpy,node_getName(source));
    node_setNConnect(cpy, node_getConnect(source));
    node_setLabel(cpy, node_getLabel(source));
    
    return cpy;
}

int node_print(FILE *pf, const void *n)
{
    Node *n1=NULL;
    int chars=-1;

    if(!pf || !n){
        fprintf(stdout, "Error while printing the node");
        return -1;
    }

    n1=(Node *)n;

    chars=fprintf(pf, "[%ld, %s, %d, %d]", n1->id, n1->name, n1->label, n1->nConnect);

    return chars;
}