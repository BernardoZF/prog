/**
* @file p4_e3_a.c
* @author Bernardo zambrano && Alvaro Platon
* @date 8 May 2020
* @version 1.0
* @brief ej3
**
@details
**
@see
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tree.h"
#include "graph_list.h"
#include "node.h"
#include "types.h"

void clean_up(FILE *pf, Graph *g, BSTree *t);

int main(int argc, char* argv[]){
    Node *n=NULL;
    Graph *g=NULL;
    BSTree *t=NULL;
    FILE *pf=NULL;
    int i;
    int flag;
    long * ids;

    if(argc != 2){
        fprintf(stderr, "ERROR EN EL FORMATO DE EJECUCION");
        return -1;
    }

    pf=fopen(argv[1], "r");
    if(!pf) {
        fprintf(stderr, "Error abriendo el archivo\n ");
        return -1;
    }

    g=graph_init();
    if(!g){
        fprintf(stderr, "Error al iniciaizar el grafo\n");
        fclose(pf);
        return -1;
    }

    flag=graph_readFromFile(pf, g);
    if(flag==ERROR){
        fprintf(stderr, "Error al crear el grafo\n");
        fclose(pf);
        graph_free(g);
        return -1;
    }

    fprintf(stdout, "Printing Graph ... \n");
    graph_print(stdout, g);
      fprintf(stdout, "\n\n");


    t=tree_init(node_free, node_copy, node_print, node_cmp);
    if(!t){
      fclose(pf);
      graph_free(g);
      return -1;
    }

    ids=graph_getNodesId(g);
    if(ids==NULL){
      clean_up(pf, g, t);
      return -1;
    }

    for(i=0;i<graph_getNumberOfNodes(g) && flag == OK; i++){
      n=graph_getNode(g,ids[i]);
      if(!n){
        clean_up(pf, g, t);
        return -1;
      }
      flag = tree_insert(t, n);
      node_free(n);
    }
    free(ids);
    if(flag != OK){
      clean_up(pf, g, t);
      return -1;
    }
    
    fprintf(stdout, "Tree postOrder Traversal ...\n" );
    tree_postOrder(stdout, t);
    fprintf(stdout, "\n\n");


    fprintf(stdout, "Tree preOrder Traversal ...\n" );
    tree_preOrder(stdout, t);
    fprintf(stdout, "\n\n");


    fprintf(stdout, "Tree inOrder Traversal ...\n" );
    tree_inOrder(stdout, t);
    fprintf(stdout, "\n\n");

    clean_up(pf, g, t);

    return 0;
  }


void clean_up(FILE *pf, Graph *g, BSTree *t)
{
  if(!pf || !g || !t) return;

  fclose(pf);
  graph_free(g);
  tree_destroy(t);

}
