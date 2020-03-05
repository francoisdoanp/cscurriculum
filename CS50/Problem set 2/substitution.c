#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int letter_position(int letter);

int main(int argc, string argv[])
{

    if(argc != 2)
    {
        printf("You need to enter one key.\n");
        return 1;
    }

    string key = argv[1];

    if(strlen(key) != 26)
    {
        printf("Usage: ./substitution key 1\n");
        return 1;
    }

    int key_num = atoi(key);

    for(int j = 0; j < 26; j++)
    {
        if(key[j] < 65 || key[j] > 122 || (key[j] > 90 && key[j] < 97))
        {
            printf("Usage: ./substitution key 2\n");
            return 1;
        }
        else if(key[j] > 97)
        {
            key[j] = key[j] - 32;
        }
    }

    for(int l = 0; l < 26; l++)
    {
        for(int i = l+1; i < 26; i++)
        {
            if(key[l] == key[i])
            {
                printf("Usage: ./substitution key 3\n");
                return 1;
            }
        }
    }

    string text = get_string("Plain text: ");
    int length = strlen(text) -1;
    int text_num = atoi(text);
    int cipher[length];


    for(int i = 0; i <= length; i++){
        if(isalpha(text[i]) && isupper(text[i]))
        {
            cipher[i] = key[letter_position(text[i])];
        }
        else if(isalpha(text[i]) && islower(text[i]))
        {
            cipher[i] = key[letter_position(toupper(text[i]))];
            cipher[i] = tolower(cipher[i]);
        }
        else
        {
            cipher[i] = text[i];
        }
    }


    printf("ciphertext: ");

    for(int i = 0; i <= length; i++)
    {
        printf("%c", cipher[i]);
    }

    printf("\n");

}

int letter_position(int letter)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabet_num = atoi(alphabet);

    for(int i = 0; i < 26; i++){
        if(letter == alphabet[i])
        {
            return i;
        }
    }

    return 0;
}
