#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Entering name in to the code
string name = get_string("What's your name? ");

    // Replying back with hello, name
    printf("hello, %s\n", name);
}