
#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>
#define max 9
void Checkinput(int**,int,int,int);/*check: not the same num exist and put into square*/
void Print(int**,int);/*print the square*/
void Free(int**,int);/*free the pointers*/
void Magic(int**,int);/*check if it is magic square*/

int main() {
    char c;
    int i = 0, num = 0, num1 = 0, count = 0;
    int **a;
    enum status {
        OUT, FIRST
    };
    int state = FIRST;
    printf("please enter the size of the square(number between 3-10) and the \n");

    while ((c = getchar()) !=EOF){
        if (!((isdigit(c) || (c == "\t") || (c == "\b")))) {/*make sure no other tabs then \t \b and numbers*/
            printf("EROR:the number of the square must be type of int");
            exit(0);
        }
        switch (state) {
            case FIRST:/*first digit at the kalet*/
                while (isdigit(c)) {/*Read the value*/
                    num1 = num1 * 10 + (c - '0');
                    c = getchar();
                }
                if ((num1 < 3) || (num1 > max)) {/*good size of the square*/
                    printf("EROR:the number of the sqare must be beetwin 3 to 9");
                    exit(0);
                }
                a = (int **) malloc(num1 * sizeof(int *));/*bulds the array*/
                for (; i <= num1; i++)
                    a[i] = (int *) malloc(num1 * sizeof(int));
                c = getchar();
                state = OUT;

            case OUT:/*for the rest of kelets*/
                num = 0;
                while (isdigit(c)) {/*Read the value*/
                    num = num * 10 + (c - '0');
                    c = getchar();
                }
                count++;
                if ((num < 1) || (num > (num1 * num1))) {
                    printf("EROR:the value not in the curect range");
                    exit(0);
                }
                if ((count) > num1 * num1) {
                    printf("EROR:to many params");
                    exit(0);
                } else
                    Checkinput(a, num,count, num1);

        }
       }

    if (count < (num1 * num1)) {
        printf("EROR:you need more params.. sorrey next time");
        exit(0);
    }

        Print(a,num1);
        Magic(a,num1);
        Free(&a,num1);

        return 1;
    }
    void Print(int **a, int num) {
        int i = 0;
        int j = 0;
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++)
                printf("%2d\t", a[i][j]);

            printf("\n");
        }
    }
    void Free(int **a, int num) {
        int i = 0;
        for (; i < num; i++)
            free(a[i]);
        free(a);
    }
    void Checkinput(int **a, int x, int place, int num) {
        int i = 0;
        int j = 0;
        int count = 0;
        for (; i < num; i++) {/*check if already exists*/
            for (j = 0; j < num; j++)
                if ((a[i][j]) && (a[i][j] == x)) {
                    printf("eror:the number %d allredy exist", x);
                    exit(0);
                }
        }
        for (i = 0; i < num; i++) {/*put intoarray*/
            for (j = 0; j < num; j++) {
                if (count == (place-1))
                    a[i][j] = x;
                count++;
            }
        }
    }

    void Magic(int **a, int num) {
        
        int sum3 = 0;
        int sum2 = 0;
        int sum = 0;
        int i, j;
        for (i = 0; i < num; i++)
            sum = sum + a[0][i];
        for (i = 0; i < num; i++) {/*checks an amount in the coulomns and row of the square*/
            for (j = 0; j < num; j++) {
                sum2 = sum2 + a[i][j];
                sum3 = sum3 + a[j][i];
            }
            if ((sum != sum2) || (sum != sum3)) {
                printf("the square is not magic");
                return;
            }
            sum2 = 0;
            sum3 = 0;
        }
        sum2 = sum3 = 0;
        for (i = 0; i < num; i++) {/**checks an amount in slant of the square*/
            sum2 = sum2 + a[i][i];
            sum3 = sum3 + a[i][(num - 1) - i];
        }
        if ((sum != sum2) || (sum != sum3)) {
            printf("the square is not magic");
            return;
        }
        printf("***the square is  magic!!!***");
    }

