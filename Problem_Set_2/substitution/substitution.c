#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_valid(string text);
void cypher(string key, string text);
char alphabet[] = {'A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z'};
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!check_valid(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
     string text = get_string("plaintext: ");
     cypher(text, argv[1]);
}

bool check_valid(string text){
    bool flag = true ;
    int length = strlen(text);
    if ( length !=26 ){
        flag = false;
    }
    else {
        for (int i = 0; i < length ; i ++){
            if (!isalpha(text[i])){
                flag = false;
                printf("Key must only contain alphabetic characters.\n");
                break;
            }
            else if (i!=0){
                for ( int j = 0; j < i; j++){
                    if ( tolower(text[i]) == tolower(text[j]) ){
                        flag = false;
                        printf("Key must not contain repeated characters.\n");
                        break;
                    }
                }
            }
        }
    }
    return flag;
}

void cypher(string text, string key){
    int text_length = strlen(text);
    char cypher[text_length + 1] ;
    cypher[text_length] = '\0';
    for (int i = 0; i < text_length; i++){
        if (ispunct(text[i]) || isdigit(text[i])){
            cypher[i] = text[i];
        }
        else if (isspace(text[i])){
            cypher[i] = ' ';
        }
        else{
            for (int j = 0; j < strlen(alphabet); j++){
                if ((toupper(text[i]) == (alphabet[j])) && isupper(text[i]) ){
                    cypher[i] = toupper(key[j]);
                }
                else if ((toupper(text[i]) == (alphabet[j])) && islower(text[i])){
                    cypher[i] = tolower(key[j]);
                }
            }

        }
    }
    printf("ciphertext: %s\n", cypher);
    return ;
}