#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graph.h"


int main(int argc, char const *argv[])
{
  FILE *pf=NULL;
  Graph *g=NULL;
  int flag = 0;

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

  flag=graph_print(stdout,g);
  if(flag==-1){
  fprintf(stderr, "Error al imprimir el archivo\n");
  fclose(pf);
  graph_free(g);
  return -1;
  }
  
  fclose(pf);
  graph_free(g);

  return 0;
}