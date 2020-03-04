#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int coleman(int letters, int words, int sentences);

int main (void)
{
    string text = get_string("Text: ");

    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;

    for (int i = 0, n=strlen(text); i < n; i++)
    {
        if(isalpha(text[i]))
        {
            letter_count++;
        }
        if(isspace(text[i]))
        {
            word_count++;
        }
        if(text[i] == 46 ||text[i] == 33 || text[i] == 63)
        {
            sentence_count++;
        }
    }
    
    if(word_count != 0)
    {
        word_count++;
    }
    
    int coleman_score = coleman(letter_count, word_count, sentence_count);
    
    if(coleman_score > 16)
    {
        printf("Grade 16+\n");
    }
    else if(coleman_score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", coleman_score);
    }
}

int coleman(int letters, int words, int sentences)
{
    return round((0.0588 * ((letters*100.00)/words) - 0.296 * ((sentences*100.00)/words) - 15.8));
}
