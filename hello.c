#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Please input your name:\n");
    printf("hello, %s\n", name);
}
