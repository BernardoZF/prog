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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#define NAME_L 64

 struct _Node{
    char name [NAME_L]; /*!<Node name */
    long id;            /*!<Node id*/
    int nConnect;       /*!<Node number of connections*/
    Label label;        /*!<Node state*/
    long predecessorid; /*!<Node predecessor Id */
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
    n->predecessorid = -1;

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

const char* node_getName(const Node *n)
{

    if(!n)
        return NULL;

    return n->name;
}

int node_getNConnect(const Node *n)
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


long node_getPredecessorId (const Node * n)
{
  if(!n) return -1;

  return n->predecessorid;
}


Status node_setPredecessorId (Node * n, long predid)
{
  if(!n || predid == -1){
    return ERROR;
  }

    n->predecessorid = predid;
    return OK;
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

/*Esta funcion no la hemos corregido ya que hemos considerado
que el identificador unico del nodo es el id*/
/**
* Funcion cambiada para que coincida con la ejecucion necesaria para p4_e3_a
*/
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
    /**
    cmp=strcmp(node_getName(node1),node_getName(node2));

    if(cmp<0)
        return -1;
    else if (cmp>0)
        return 1;
*/

  if(node_getId(node1) < node_getId(node2)){
    return -1;
    }
  else if (node_getId(node1) > node_getId(node2)){
    return 1;
  }
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
    node_setNConnect(cpy, node_getNConnect(source));
    node_setLabel(cpy, node_getLabel(source));
    node_setPredecessorId(cpy, node_getPredecessorId(source));

    return cpy;
}

int node_print(FILE *pf, const void *n)
{
    Node *n1=NULL;
    int chars=-1;

    if(!pf || !n){
        fprintf(stdout, "Error while printing the node\n");
        return -1;
    }

    n1=(Node *)n;

    chars=fprintf(pf, "[%ld, %s, %d, %d, %ld] ", n1->id, n1->name, n1->label, n1->nConnect, n1->predecessorid);

    return chars;
}
