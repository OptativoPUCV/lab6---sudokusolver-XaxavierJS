#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int row[9][10] = {0};
  int col[9][10] = {0};
  int box[9][10] = {0};
  int i, j;

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      int num = n->sudo[i][j];
      if (num != 0) {
        if (row[i][num] || col[j][num] || box[(i / 3) * 3 + j / 3][num]) {
          return 0;
        }
        row[i][num] = 1;
        col[j][num] = 1;
        box[(i / 3) * 3 + j / 3][num] = 1;
      }
    }
  }
  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int i, j, k;

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        for (k = 1; k <= 9; k++) {
          Node *new_node = copy(n);
          new_node->sudo[i][j] = k;

          if (is_valid(new_node)) {
            pushBack(list, new_node);
          } else {
            free(new_node);
          }
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0) {
        return 0;
      }
      
    }
    
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) { 
  Stack *S = createStack();
  push(S, initial);
  while (!is_empty(S)){
    Node *n = top(S);
    pop(S);
    if (is_final(n)){
      return n;
    }
    List *list = get_adj_nodes(n);
    Node *aux = first(list);
    while (aux){
      push(S, aux);
      aux = next(list);
    }
    free(n);
    
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