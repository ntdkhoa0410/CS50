#include <cs50.h>
#include <stdio.h>

/* function declaration*/
int prompt(void);
void printStair(int n);
/* variable declaration*/
int height;

int main(void)
{
 height = prompt();
 if ( height==1 ){
    printf("# #\n");
 }
 else
 {
    printStair(height);
 }
}

int prompt(void)
{
    do
  {
      height = get_int("Enter height size: ");
  }
  while (height < 0);
  return height;
}

void printStair(int n){
    int j = 1;
    while (j < n + 1) {
        for (int k = 0; k < n-j ; k++ ) {
            printf(" ");
        }
        for (int l = j; l > 0; l--) {
            printf("#");
        }

        printf(" ");

        for (int m = 0; m < j ; m++ ) {
            printf("#");
        }
        printf("\n");
        j = j + 1;
    }
}