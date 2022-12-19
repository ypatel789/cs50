#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

const int N = 26;
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main(int argc, string argv[])
{
    //case which there are not command line arguments or more than one command line argument, which is a type of command line arguments error.
if (argc != 2)
{
    printf("Usage: ./substitution key\n");
    return 1;
}
//case which there is just one command line argument, but may contain other errors about the command line arguments.
else
{
    int a = strlen(argv[1]);
    //case which the command line argument does not contain 26 characters, which is a type of command line arguments error.
    if (a != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //case which the command line argument contains 26 characters, but may have other errors about the command line arguments.
    else
    {
        for (int i = 0; i < a; i++)
        {
            //case which the 26 characters contain non-alphabetic character(s)
            if ((argv[1][i] < 'A') || ((argv[1][i] > 'Z') && (argv[1][i] < 'a')) || (argv[1][i] > 'z'))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            //case which the 26 characters contain repeated characters
            else
            {
                for (int j = 0; j < i; j++)
                {
                    if ((argv[1][i] == argv[1][j]) || (argv[1][i] == argv[1][j] + 32) || (argv[1][i] == argv[1][j] - 32))
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
            }
        }
    }
}

// get the inputs from users
string s = get_string("plaintext: ");
printf("ciphertext: ");
// the main part of the code, doing encryption
int b = strlen(s);
for (int k = 0; k < b; k++)
{
    // the non-alphabetical characters should remain unchanged
    if ((s[k] < 'A') || ((s[k] > 'Z') && (s[k] < 'a')) || (s[k] > 'z'))
    {
        printf("%c", s[k]);
    }
    // encrypt for Uppercase letters
    else if ((s[k] >= 'A') && (s[k] <= 'Z'))
    {
        int upper = (s[k] - 65) % 26;
        if ((argv[1][upper] >= 97) && (argv[1][upper] <= 122))
        {
            printf("%c", argv[1][upper] - 32);
        }
        else
        {
            printf("%c", argv[1][upper]);
        }
    }
    else if ((s[k] >= 'a') && (s[k] <= 'z'))
    {
        int lower = (s[k] - 97) % 26;
        if ((argv[1][lower] >= 65) && (argv[1][lower] <= 90))
        {
            printf("%c", argv[1][lower] + 32);
        }
        else
        {
            printf("%c", argv[1][lower]);
        }
    }
}
printf("\n");
return 0;

}





