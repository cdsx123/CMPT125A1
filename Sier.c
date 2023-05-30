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
  printf("\nEnter the name of the input file: ");
  scanf("%s", inFile);

  outStream = fopen(outFile, "w");
  if (outStream == NULL) {
    printf("ERROR: Output file not opened correctly.");
    exit(1);
  };
  inStream = fopen(inFile, "r");
  if (inStream == NULL) {
    printf("ERROR: Input file not opened correctly.");
    fclose(outStream);
    exit(1);
  };


  do {
    if (!numRows) {
      printf("Enter the number of rows in the board (0<number<40) ");
    }
    err = scanf("%d", &numRows);

    if (err == 0) {
      printf("\nERROR: The value of numRows is not an integer");
      fclose(inStream);
      fclose(outStream);
      exit(1);
    };
    if (numRows < 0 || numRows > 40) {
      printf("\nERROR: Read an illegal number of rows for board\n");
      printf("TRY AGAIN, 0 < number of rows < 40 ");
    };
  } while (numRows < 0 || numRows > 40);


  do {
    if (!numCols) {
      printf("Enter the number of cols in the board (0<number<80) ");
    }
    err = scanf("%d", &numCols);

    if (err == 0) {
      printf("\nERROR: The value of numCols is not an integer");
      fclose(inStream);
      fclose(outStream);
      exit(1);
    };
    if (numCols < 0 || numCols > 80) {
      printf("ERROR: Read an illegal number of columns for board\n");
      printf("TRY AGAIN, 0 < number of columns < 80");
    };
  } while (numCols < 0 || numCols > 80);


  err = fscanf(inStream, "%d", &numGens);
  if (!numGens) {
    printf("ERROR: Could not read the number of generations");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  } else if (err == 0) {
    printf("ERROR: number of generations is not an integer");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  } else if (numGens < 0 || numGens > 40) {
    printf("ERROR: Read an illegal number of generations");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  }

  err = fscanf(inStream, "%d", &genInc);
  if (!genInc) {
    printf("ERROR: Could not read the generation increment");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  } else if (err == 0) {
    printf("ERROR: generation increment is not an integer");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  } else if (genInc < 0 || genInc > 40) {
    printf("ERROR: Read an illegal generation incremen");
    fclose(inStream);
    fclose(outStream);
    exit(1);
  }

  printf("hello");
  board = (int**)malloc((numRows+1) * sizeof(int));
  board[0] = (int*)malloc(numRows*numCols*sizeof(int));
  for (int i = 1; i < numRows; i++) {
    board[i] = board[0] + i*numCols;
  };
  board[1][3] = 1;

  FillZero(board, numRows, numCols);

  for (curGen = 0; curGen < numGens; curGen++) {
    NextGen(board, numRows, numCols);
    printf("\nSierpinski gameboard: generation %d\n", curGen);

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        printf("%d", board[i][j]);
        // fprintf(outFile, "%d", board[i][j]);
      }
      printf("\n");
      // fprintf(outFile, "\n");
    }
  }

  free(board);
  fclose(inStream);
  fclose(outStream);
  return 0;
}

void FillZero(int ** my2DArray, int M, int N) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        printf("hello");
        printf("%d", my2DArray[i][j]);
        my2DArray[i][j] = 0;
        printf("%d", my2DArray[i][j]);
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
  int ** nextGenBoard = (int**)malloc(M*sizeof(int));
  nextGenBoard[0] = (int*)malloc(M*N*sizeof(int));
  for (int i = 0; i < M; i++) {
    nextGenBoard[i] = nextGenBoard[0] + i*N;
  };
  FillZero(nextGenBoard, M, N);
  for (int k = 0; k < M; k++) {
    for (int j = 0; j < N; j++) {
      if (k == 0 || j == 0) {
        nextGenBoard[k][j] = 0;
      } else {
        nextGenBoard[k][j] = ( board[k][j] + board[k-1][j] + board[k][j-1] ) % 2;
      };
    };
  };
  CopyArray(board, nextGenBoard, M, N);

  free(nextGenBoard);
};