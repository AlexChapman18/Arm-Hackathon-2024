#include <stdio.h>
#include <stdlib.h> 
// for each diagonal

// add in diagonal

// check backpaths

// return end square

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void back(int x, int y, int B[100][100], int A[100][100], int s);
void main2();
int main(){
    for (int i=0;i<100;i++){
        main2();
    }
}

void main2(void)
{
    int A[100][100];
    int n = 100;
    int m = 100;
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char v[102];
    for (int i = 0; i < 100; i++)
    {
        fgets(v, 102, fptr);
        for (int j = 0; j < 100; j++)
        {
            A[i][j] = v[j] - '0';
        }
    }
    fclose(fptr);
    static int B[100][100];

    B[0][0] = A[0][0];
    for (int s = 1; s < n+m; s++)
    {
        int k = MIN(n, s+1);
        for (int i = MAX(0,s-m+1); i < k; i++)
        {
            //process i, s-i
            if (i == 0)
            {
                B[0][s] = B[0][s-1] + A[0][s]; 
            }
            else if (s-i == 0)
            {
                B[i][0] = B[i-1][0] + A[i][0];
            }
            else
            {
                B[i][s-i] = MIN(B[i-1][s-i], B[i][s-i-1]) + A[i][s-i];
            } 
        }
        if (s > 1){
            for (int i = MAX(0,s-m); i < k; i++)
            {
                //operate on (i, s-i-1)
                back(i, s-i, B, A, s);
                

            }
        }
    }
    printf("%i\n\n", B[99][99]);
}


void back(int x, int y, int B[100][100], int A[100][100], int s)
{
    if (x + y > s)
    {
        return;
    }
    int min = 9999;
    if (x != 99)
    {
        int min = MIN(B[x][y+1], min);
    }
    if (y != 99)
    {
        int min = MIN(B[x+1][y], min);
    }
    if (x != 0)
    {
        int min = MIN(B[x-1][y], min);
    }
    if (y != 0)
    {
        int min = MIN(B[x][y-1], min);
    }
    
    if (min + A[x][y] < B[x][y])
    {
        B[x][y] = min + A[x][y];
        if (x != 99)
        {
            back(x, y+1, B, A, s);
        }
        if (y != 99)
        {
            back(x+1, y, B, A, s);
        }
        if (x != 0)
        {
            back(x-1, y, B, A, s);
        }
        if (y != 0)
        {
            back(x, y-1, B, A, s);
        }
    }
}
