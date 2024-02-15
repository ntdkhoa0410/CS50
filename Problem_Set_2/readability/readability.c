#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters_number = count_letters(text);
    int words_number = count_words(text);
    int sentences_number = count_sentences(text);
    float L = (float)letters_number / (float)words_number * 100;
    float S = (float)sentences_number / (float)words_number * 100;
    float index =  0.0588 * L - 0.296 * S - 15.8;
    printf ("index before: %.2f\n", index);
    if (index < 0){
        printf("Before Grade 1\n");
    }
    else if (index > 16){
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", (int)round(index));
    }
}

int count_letters(string text){
    int number = 0;
    for (int i = 0 ; i < strlen(text) ; i ++ )
        {
        if( isalpha(text[i]) ){
            number = number + 1 ;
        }
    }
    return number;
}

int count_words(string text){
     int word = 0;
    for (int i = 0 ; i < strlen(text) ; i ++ )
        {
        if( isspace(text[i]) ){
            word  = word  + 1 ;
        }
        else if (ispunct(text[i]) && (text[i+1])=='\0')
        {
            word  = word  + 1 ;
        }
    }
    return word;
}

int count_sentences(string text){
     int sentence = 0;
    for (int i = 0 ; i < strlen(text) ; i ++ ){
        if( (text[i])=='.' || (text[i])=='!' || (text[i])=='?'){
            sentence  = sentence  + 1 ;
        }
    }
    return sentence;
}

