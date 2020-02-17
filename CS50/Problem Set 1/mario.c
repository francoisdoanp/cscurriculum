#include <cs50.h>
#include <stdio.h>

void create_pyramid(int size);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height:\n");
    }while (height < 1 || height > 8);
    create_pyramid(height);
    printf("\n");
}

void create_pyramid(int size)
{
    for(int i=size-1; i>=0; i--){
        for(int l=i; l>=0;l--){
            printf(" ");
        }
        for(int j=size; j>i; j--){
            printf("#");
        }
        printf("  ");
        for(int k=size; k>i; k--){
            printf("#");
        }
        printf("\n");
    }
}
