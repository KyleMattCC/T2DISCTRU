#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[30];

struct setTag{
   int x, y;
   struct setTag *pNext;
};

struct setTag *NextMove(int x, int y, struct setTag free[], int *turn, struct setTag *posn, int Table[][4], int *ctr)
{
   int i, found = 0;
   struct setTag *pTemp;
   struct setTag *pCurrent;

   pTemp = NULL;
   pCurrent = NULL;

/*Checks if coordinates is an element of free*/
   for(i=0; i<16; i++){
	if(x == free[i].x && y == free[i].y){
		free[i].x = -1;
		free[i].y = -1;
		found = 1;
		break;
	}
   }
  
   if(found == 1){
	printf("\nSuccessful! %d inserted in row %d col %d.\n", *turn, x, y);
	Table[x-1][y-1] = *turn;
	pTemp = malloc(sizeof(struct setTag));
	pTemp->x = x;
	pTemp->y = y;
	pTemp->pNext = NULL;
    if(posn == NULL) 
		posn = pTemp;
    else{
		pCurrent = posn;
		while(pCurrent->pNext != NULL)
			pCurrent = pCurrent->pNext;
		pCurrent->pNext = pTemp;
	}
	*turn = *turn + 1;
	if(*turn == 5)
		*turn = 1;
	*ctr = *ctr + 1;
   }

   else
	printf("\nUnsuccessful, slot is occupied or does not exist.\n");

   return posn;
}

int Match(struct setTag *posns, struct setTag patn[])
{
   int matchnum = 0;
   int i;
   struct setTag *pTemp;
 
   pTemp = posns;
   while(pTemp != NULL){
	for(i = 0; i < 4; i++){
		if(patn[i].x == pTemp->x && patn[i].y == pTemp->y)
			matchnum++;
	}
	pTemp = pTemp->pNext;
   }

   return matchnum;
}

int Check(struct setTag *posns, struct setTag A[], struct setTag B[], struct setTag C[], struct setTag D[])
{
   int i, j, k;
   int MatchHor, MatchVer;
   struct setTag Horizontal[4];
   struct setTag Vertical[4];

/*Checks horizontally*/
   for(i=1;i<5;i++){
	k = 0;
	for(j=1;j<5;j++){
		Horizontal[k].x = i;
		Horizontal[k].y = j;
		k++;
    }

    MatchHor = Match(posns, Horizontal);
    if(MatchHor != 1)
		break;
   }

/*Checks vertically*/
   for(i=1;i<5;i++){
	k = 0;
	for(j=1;j<5;j++){
		Vertical[k].x = j;
		Vertical[k].y = i;
		k++;
    }

    MatchVer = Match(posns, Vertical);
    if(MatchVer != 1)
		break;
   }

   if(Match(posns, A) == 1 && Match(posns, B) == 1 && Match(posns, C) == 1 && Match(posns, D) == 1 && MatchHor == 1 && MatchVer == 1)
	return 1;

   else
	return 0;
}

void EndGame(int over, struct setTag *uno, struct setTag *dos, struct setTag *tres, struct setTag *quatro, string result, struct setTag A[], struct setTag B[], struct setTag C[], struct setTag D[])
{
   if(Check(uno, A, B, C, D) == 1 && Check(dos, A, B, C, D) == 1 && Check(tres, A, B, C, D) == 1 && Check(quatro, A, B, C, D) == 1)
	strcpy(result, "good");

   if(over && !(strcmp(result, "\0")))
	strcpy(result, "bad");

   printf("Result is %s\n", result);
}

void PrintTable(int Table[][4])
{
   int a, b;
		
   printf("\n");
   for(a=0;a<4;a++){
	if(a == 2)
		printf("==============\n");
	for(b=0;b<4;b++){
		if(b==2)
			printf("||");
		printf(" %d ", Table[a][b]);
	}
	printf("\n");
   }

   printf("\n");
}

int main()
{
   int Table[4][4] = {{0,0,0,0},
		  {0,0,0,0},
		  {0,0,0,0},
		  {0,0,0,0}};
   struct setTag empty[16];
   struct setTag A[4];
   struct setTag B[4];
   struct setTag C[4];
   struct setTag D[4];
   struct setTag *uno, *dos, *tres, *quatro;
   string result = "\0";
   int turn = 1;
   int over = 0;
   int i, j, k;
   int x, y;

/*Print table*/
   PrintTable(Table);
   
   uno = NULL;
   dos = NULL;
   tres = NULL;
   quatro = NULL;

/*Initializing free*/
   k = 0;   
   for(i=1; i<5; i++){
	for(j=1; j<5; j++){
		empty[k].x = i;
		empty[k].y = j;
		k++;
	}
   }

/*Initializing A*/
   k = 0;
   for(i=1; i<3; i++){
	for(j=1; j<3; j++){
		A[k].x = i;
		A[k].y = j;
		k++;
	}
   }

/*Initializing B*/
   k = 0;
   for(i=1; i<3; i++){
	for(j=3; j<5; j++){
		B[k].x = i;
		B[k].y = j;
		k++;
	}
   }

/*Initializing C*/
   k = 0;
   for(i=3; i<5; i++){
	for(j=1; j<3; j++){
		C[k].x = i;
		C[k].y = j;
		k++;
	}
   }

/*Initializing D*/
   k = 0;
   for(i=3; i<5; i++){
	for(j=3; j<5; j++){
		D[k].x = i;
		D[k].y = j;
		k++;
	}
   }

/*Next Move*/
   i = 0;
   while(i < 16){
	printf("Input x and y coordinates (row, col) where you want to insert number %d: \n", turn);
	scanf("%d %d", &x, &y);
	switch(turn){
	case 1:	uno = NextMove(x, y, empty, &turn, uno, Table, &i);
		break;
	case 2: dos = NextMove(x, y, empty, &turn, dos, Table, &i);
		break;
	case 3: tres = NextMove(x, y, empty, &turn, tres, Table, &i);
		break;
	case 4: quatro = NextMove(x, y, empty, &turn, quatro, Table, &i);
		break;
	}
	PrintTable(Table);
   }

/*Free is now an empty set*/
   over = 1;

   EndGame(over, uno, dos, tres, quatro, result, A, B, C, D);

   free(empty);
   free(uno);
   free(dos);
   free(tres);
   free(quatro);

   return 0;
}
