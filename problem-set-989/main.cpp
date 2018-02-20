#include <iostream>
#include <cmath>

struct Matrix {
  int width;
  int height;
  int **matrix;
};

bool available(Matrix M, int _i, int _j, int n) {
  for (int i = 0; i < M.height; i++)
    if(M.matrix[i][_j] == n )
      return false;

  for (int j = 0; j < M.width; j++)
    if(M.matrix[_i][j] == n)
      return false;

  int b_x, b_y;
  b_x = floor(_j / 3) * 3;
  b_y = floor(_i / 3) * 3;

  for (int i = b_x; i < b_y + 3; i++) {
    for (int j = b_y; j < b_x + 3; j++) {
      if (i != _i && j != _j)
        if(M.matrix[i][j] == n)
          return false;
    }
  }

  return true;
}

// 0 6 0 1 0 4 0 5 0
// 0 0 8 3 0 5 6 0 0
// 2 0 0 0 0 0 0 0 1
// 8 0 0 4 0 7 0 0 6
// 0 0 6 0 0 0 3 0 0
// 7 0 0 9 0 1 0 0 4
// 5 0 0 0 0 0 0 0 2
// 0 0 7 2 0 6 9 0 0
// 0 4 0 5 0 8 0 7 0

bool recursive(Matrix M, int _i, int _j) {

  if (_j == M.width) {
    _j = 0;
    _i++;
  }
  if (_i == M.height) {
    return true;
  }

  while (M.matrix[_i][_j] != 0) {
    _j++;
    if (_j == M.width) {
      _j = 0;
      _i++;
    }
    if (_i == M.height) {
      return true;
    }
  }

  for (int n = 1; n <= 9; n++) {
    if(available(M, _i, _j, n) == true) {
      // printf("Tentando n:%d na posicao M(%d,%d)\n", n, _i, _j);
      M.matrix[_i][_j] = n;

      // for (int i = 0; i < M.height; i++) {
      //   for (int j = 0; j < M.width; j++) {
      //     printf("%d ", M.matrix[i][j]);
      //   }
      //   putchar('\n');
      // }
      // printf("\n\n");
      if(recursive(M, _i, _j+1) == true)
        return true;
    }
  }
  M.matrix[_i][_j] = 0;
  // printf("não foi possível encontrar um numero em M(%d,%d)\n", _i, _j );
  // for (int i = 0; i < M.height; i++) {
  //   for (int j = 0; j < M.width; j++) {
  //     printf("%d ", M.matrix[i][j]);
  //   }
  //   putchar('\n');
  // }
  // printf("\n\n");
  return false;
}

int main(int argc, char const *argv[]) {
  int width;
  int height;
  int n;



  scanf(" %d", &n);

  width = height = n*n;
  // printf("%d %d\n", height, width);
  Matrix M;
  M.height = height;
  M.width = width;
  M.matrix = (int**)malloc(height*sizeof(int*));

  for (int i = 0; i < height; i++)M.matrix[i] = (int*)malloc(width * sizeof(int));

  if(M.matrix == NULL) {
    printf("Malloc deu erro\n");
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      scanf(" %d", &M.matrix[i][j]);
      // M.matrix[i][j] = 5;
    }
  }

  if( recursive(M, 0, 0) ) {
    // putchar('\n');
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        printf("%d ", M.matrix[i][j]);
      }
      putchar('\n');
    }
  } else {
    printf("NO SOLUTION\n");
  }
  free(M.matrix);

  return 0;
}
