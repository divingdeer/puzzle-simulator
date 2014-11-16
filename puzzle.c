#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct piece piece_t;

int generatePuzzle(piece_t* pieces, int length, int height);
piece_t* getPiece(piece_t* pieces, int numberPieces);
int getRand(int min, int max);
int solvePuzzle(piece_t* pieces, int length, int height);
int printPuzzle(piece_t* pieces, int length, int height);
int printPiece(piece_t* pieces, int i);

struct piece {
  int id;
  bool complete;
  int side_n;
  int side_e;
  int side_s;
  int side_w;
  bool complete_n;
  bool complete_e;
  bool complete_s;
  bool complete_w;
};

int main(int argc,char* argv[]) {

  int length = strtol(argv[1], NULL, 10);;
  int height = strtol(argv[2], NULL, 10);;

  piece_t puzzle[length*height];
  piece_t* pointer_puzzle = test;

  generatePuzzle(pointer_puzzle, length, height);
  //printPuzzle(pointer_puzzle, length, height);
  solvePuzzle(pointer_puzzle, length, height);

  return 0;
}

int generatePuzzle(piece_t* pieces, int length, int height) {

  int numberPieces = length*height;

  for(int i=0;i<numberPieces;i++) {
    pieces[i].id = i+1;
    pieces[i].complete = false;

    if(i<length) {
      pieces[i].side_n = 0;
      pieces[i].complete_n = true;
    } else {
      pieces[i].side_n = i+1-length;
      pieces[i].complete_n = false;
    }

    if(i>(numberPieces-length-1)) {
      pieces[i].side_s = 0;
      pieces[i].complete_s = true;
    } else {
      pieces[i].side_s = i+1+length;
      pieces[i].complete_s = false;
    }

    if((i+1)%length==0 && (i!=0)) {
      pieces[i].side_e = 0;
      pieces[i].complete_e = true;
    } else {
      pieces[i].side_e = i+2;
      pieces[i].complete_e = false;
    }

    if(i%length==0) {
      pieces[i].side_w = 0;
      pieces[i].complete_w = true;
    } else {
      pieces[i].side_w = i;
      pieces[i].complete_w = false;
    }
  }
  return 0;
}

piece_t* getPiece(piece_t* pieces, int numberPieces) {

  int randNum = getRand(0, numberPieces-1);
  int randNumTemp = randNum;

  piece_t* piece = &pieces[randNumTemp];

  while(piece->complete == true) {
    randNumTemp++;
    if(randNumTemp==numberPieces) {
      randNumTemp = 0;
    } else if(randNumTemp==randNum) {
      return NULL;
    }
    piece = &pieces[randNumTemp];
  }
  return piece;
}

int getRand(int min, int max) {

  static int Init = 0;
  int rc;
  
  if(Init == 0) {
    srand(time(NULL));
    Init = 1;
  }

  rc = (rand() % (max - min + 1) + min);
  return (rc);
}

int solvePuzzle(piece_t* pieces, int length, int height) {
  
  int numberPieces = length*height;

  piece_t* pieceToSolve = getPiece(pieces, numberPieces);

  int remainingPieces = numberPieces;
  
  printf("\"pieces_remaining\",\"attempts\",\"total_attempts\"\n");
  int total_attempts = 0;

  while(pieceToSolve!=NULL) {

    int attempts = 0;
    printf("%d,",remainingPieces);

    piece_t piecesCopy[numberPieces];
    memcpy(piecesCopy,pieces, sizeof pieces[0] * numberPieces);

    while(pieceToSolve->complete==false) {
      piece_t* pieceTemp = getPiece(piecesCopy, numberPieces);
      piecesCopy[pieceTemp->id-1].complete=true;
      attempts++;
      total_attempts++;

      if(pieceToSolve->side_n==pieceTemp->id && pieceToSolve->complete_n==false) {
        pieceToSolve->complete_n=true;
        pieces[pieceTemp->id-1].complete_s=true;

      } else if(pieceToSolve->side_e==pieceTemp->id && pieceToSolve->complete_e==false) {
        pieceToSolve->complete_e=true;
        pieces[pieceTemp->id-1].complete_w=true;

      } else if(pieceToSolve->side_s==pieceTemp->id && pieceToSolve->complete_s==false) {
        pieceToSolve->complete_s=true;
        pieces[pieceTemp->id-1].complete_n=true;

      } else if(pieceToSolve->side_w==pieceTemp->id && pieceToSolve->complete_w==false) {
        pieceToSolve->complete_w=true;
        pieces[pieceTemp->id-1].complete_e=true;
      }

      if((pieceToSolve->complete_n==true) &&
         (pieceToSolve->complete_e==true) &&
         (pieceToSolve->complete_s==true) &&
         (pieceToSolve->complete_w==true)) {
        pieceToSolve->complete=true;
        printf("%d,%d\n",attempts, total_attempts);
        }
    }

    remainingPieces--;
    pieceToSolve = getPiece(pieces, numberPieces);
  }

  return 0;
}

int printPuzzle(piece_t* pieces, int length, int height) {

  int numberPieces = length*height;

  for(int i=0;i<numberPieces;i++) {
    
    for(int j=0;j<length;j++) {
      printf(" %d ", pieces[j+i].side_n);
    }
    printf("\n");

    for(int j=0;j<length;j++) {
      printf("%d%d%d", pieces[j+i].side_w,pieces[j+i].id,pieces[j+i].side_e);
    }
    printf("\n");

    for(int j=0;j<length;j++) {
      printf(" %d ", pieces[j+i].side_s);
    }
    printf("\n");
    
    i = i-1+length;
  }

  return 0;
}

int printPiece(piece_t* pieces, int i) {

  i--;
  printf(" %d\n ", pieces[i].side_n);
  printf("%d%d%d\n", pieces[i].side_w,pieces[i].id,pieces[i].side_e);
  printf(" %d\n", pieces[i].side_s);

  return 0;
}
