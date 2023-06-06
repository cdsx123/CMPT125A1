#include <stdio.h>
#include <stdlib.h>


void FillZero( int ** my2DArray, int M, int N);
void CopyArray(int ** my2DArray, int**myNextGenArray, int M, int N);
void NextGen(int ** board, int M, int N);

int main(void) {
  int err;
  FILE *outStream = NULL;
  FILE *inStream = NULL;
  char outFile[100];
  char inFile[100];
  int numRows;
  int numCols;
  int numGens;
  int genInc;
  int curGen = 0;
  int ** board = NULL;

  printf("Enter the name of the output file: ");
  scanf("%s", outFile);
  printf("Enter the name of the input file: ");
  scanf("%s", inFile);

  outStream = fopen(outFile, "w");
  if (outStream == NULL) {
    printf("ERROR: Output file not opened correctly.\n");
    exit(1);
  };
  inStream = fopen(inFile, "r");
  if (inStream == NULL) {
    printf("ERROR: Input file not opened correctly.\n");
    fclose(outStream);
    exit(2);
  };


  do {
    if (!numRows) {
      printf("Enter the number of rows in the board (2<number<40) ");
    }
    err = scanf("%d", &numRows);

    if (err != 1) {
      printf("ERROR: The value of numRows is not an integer\n");
      fclose(inStream);
      fclose(outStream);
      exit(3);
    };
    if (numRows <= 2 || numRows >= 40) {
      printf("ERROR: Read an illegal number of rows for board\n");
      printf("TRY AGAIN, 2 < number of rows < 40 ");
    };
  } while (numRows <= 2 || numRows >= 40);


  do {
    if (!numCols) {
      printf("Enter the number of cols in the board (4<number<80) ");
    }
    err = scanf("%d", &numCols);

    if (err != 1) {
      printf("ERROR: The value of numCols is not an integer\n");
      fclose(inStream);
      fclose(outStream);
      exit(4);
    };
    if (numCols <= 4 || numCols >= 80) {
      printf("ERROR: Read an illegal number of columns for board\n");
      printf("TRY AGAIN, 4 < number of columns < 80 ");
    };
  } while (numCols <= 4 || numCols >= 80);




  err = fscanf(inStream, "%d", &numGens);
  if (err == -1) {
    printf("ERROR: Could not read the number of generations\n");
    fclose(inStream);
    fclose(outStream);
    exit(5);
  } else if (err != 1) {
    printf("ERROR: number of generations is not an integer\n");
    fclose(inStream);
    fclose(outStream);
    exit(6);
  } else if (numGens < 0) {
    printf("ERROR: Read an illegal number of generations\n");
    fclose(inStream);
    fclose(outStream);
    exit(7);
  }

  

  err = fscanf(inStream, "%d", &genInc);

  if (err == -1) {
    printf("ERROR: Could not read the generation increment\n");
    fclose(inStream);
    fclose(outStream);
    exit(8);
  } else if (err != 1) {
    printf("ERROR: generation increment is not an integer\n");
    fclose(inStream);
    fclose(outStream);
    exit(9);
  } else if (genInc < 0 || genInc > numGens) {
    printf("ERROR: Read an illegal generation increment\n");
    fclose(inStream);
    fclose(outStream);
    exit(10);
  }

  
  board = (int**)malloc(numRows * sizeof(int*));
  board[0] = (int*)malloc(numRows*numCols*sizeof(int));
  for (int i = 1; i < numRows; i++) {
    board[i] = board[0] + i*numCols;
  }
  FillZero(board, numRows, numCols);

  board[1][3] = 1;


  NextGen(board, numRows, numCols);

  for (curGen = 1; curGen < numGens; curGen += genInc) {
    if (curGen != 1) {
      for (int P = curGen - genInc; P < curGen; P++) {
        NextGen(board, numRows, numCols);
      }
    }
    
  
    
    printf("Sierpinski gameboard: generation %d\n", curGen);
    fprintf(outStream, "Sierpinski gameboard: generation %d\n", curGen);

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        if (board[i][j] == 0) {
          printf(" ");
          fprintf(outStream, " ");
        } else {
          printf("%d", board[i][j]);
          fprintf(outStream, "%d", board[i][j]);
        }
        
      }
      printf("\n");
      fprintf(outStream, "\n");
    }
    printf("\n");
    fprintf(outStream, "\n");
  }

  if (curGen >= numGens) {
    for (int P = curGen - genInc; P < numGens; P++) {
      NextGen(board, numRows, numCols);
    }
    printf("Sierpinski gameboard: generation %d\n", numGens);
    fprintf(outStream, "Sierpinski gameboard: generation %d\n", numGens);

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        if (board[i][j] == 0) {
          printf(" ");
          fprintf(outStream, " ");
        } else {
          printf("%d", board[i][j]);
          fprintf(outStream, "%d", board[i][j]);
        }
      }
      printf("\n");
      fprintf(outStream, "\n");
    }
    printf("\n");
    fprintf(outStream, "\n");
  }

  free(board[0]);
  free(board);

  fclose(inStream);

  fclose(outStream);
  return 0;
}

void FillZero(int** my2DArray, int M, int N) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        my2DArray[i][j] = 0;
      };
    };
  };

void CopyArray(int ** my2DArray, int**myNextGenArray, int M, int N) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      my2DArray[i][j] = myNextGenArray[i][j];
    };
  };
};

void NextGen(int ** board, int M, int N) {
  int ** nextGenBoard = (int**)malloc(M*sizeof(int*));
  *nextGenBoard = (int*)malloc(M*N*sizeof(int));
  for (int i = 0; i < M; i++) {
    *(nextGenBoard + i) = *nextGenBoard + i*N;
  };
  FillZero(nextGenBoard, M, N);
  for (int k = 0; k < M; k++) {
    for (int j = 0; j < N; j++) {
      if (k == 0 || j == 0) {
        *(*(nextGenBoard+k)+j) = 0;
      } else {
        *(*(nextGenBoard+k)+j) = ( *(*(board+k)+j) + *(*(board+k-1)+j) + *(*(board+k)+j-1) ) % 2;
      };
    };
  };
  CopyArray(board, nextGenBoard, M, N);

  free(nextGenBoard[0]);
  free(nextGenBoard);
};