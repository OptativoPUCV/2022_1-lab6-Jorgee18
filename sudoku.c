#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  int a, s;
  int *ptr = (int*) calloc(10, sizeof(int));
  
  for(a = 0; a < 9; a++)
  {
    if(n->sudo[a][0] != 0)
    {
      ptr[a] = ptr[a] + 1;
      if(ptr[a] > 1) 
      {
        free(ptr);
        return 0;
      }
    }
  }
  
  ptr = (int*) calloc(10, sizeof(int));
  for(s = 0; s < 9; s++)
  {
    if(n->sudo[0][s] != 0)
    {
      ptr[s] = ptr[s] + 1;
      if(ptr[s] > 1)
      { 
        free(ptr);
        return 0;
      }
    }
  }
  
  int h,k,p;
  for(h = 0; h < 9; h++)
  {
    k = h;
    ptr = (int*) calloc(10, sizeof(int));
    for(p = 0; p < 9; p++)
      {
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        if(n->sudo[i][j] != 0)
        {
          ptr[p] = ptr[p] + 1;
          if(ptr[p] > 1)
          { 
            free(ptr);
            return 0;
          } 
        }
      }
    free(ptr);
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i, j, k;
  for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
        {
          if(n->sudo[i][j] == 0)
          {
            for(k = 1; k < 10; k++)
            {
              n->sudo[i][j] = k;
              if(is_valid(n))
              {
                Node* adj = copy(n);
                pushBack(list,adj);
              }
            }
            n->sudo[i][j] = 0;
            return list;
          }
        }
    }
  return list;
}


int is_final(Node* n)
{
  int h,k,p;
  for(h = 0; h < 9; h++)
  {
    k = h;
    for(p = 0; p < 9; p++)
      {
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        
        if(n->sudo[i][j] == 0)
        {
          return 0;
        }
      }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack *pila = createStack();
  Node *aux = createNode();
  push(pila, initial);

  while(pila != NULL)
  {
    aux = first(pila);
    pop(pila);
    
    if(is_final(aux) == 1)return aux;
    List *adj = get_adj_nodes(aux);
    Node *ptrAux = first(adj);
    
    while(ptrAux)
      {
        push(pila, ptrAux);
        ptrAux = next(adj);
      }
    free(ptrAux);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/