#include <stdio.h>
#include <string.h>
#include <ctype.h>
short get_operand(char mode); /* read in numeric value in mode; return value */
void print_acc(short acc);    /* print out accumulator values */
char print_menu(void);        /* print menu and get option */

int main(void)
{ /* main menu loop; execute option
or call appropriate function */
    char mode = 'D';
    char input[10];
    short acc;
    char options;
    char valid_input[7] = "OHDCSQ";
    char user_option; // may need to change
    do
    {
        print_acc(acc);
        user_option = print_menu(); /*returns the user value*/
        ;
        user_option = toupper(user_option);
        switch (user_option)
        {
        case 'O':
            printf("Mode is Octal\n");
            mode = user_option;
            break;
        case 'H':
            printf("Mode is Hexadecimal\n");
            mode = user_option;
            break;
        case 'D':
            printf("Mode is Decimal\n");
            mode = user_option;
            break;
        case 'C':
            acc = 0;
            break;
        case 'S':
            acc = get_operand(mode);
            break;
        case 'Q':
            break;
        default:
            printf("Invalid option: %c\n", user_option);
        }
    } while (user_option != 'Q');
    return acc;
}

char print_menu(void)
{
    char option;
    printf(" Please select one of the following options:\n");
    printf("O Octal Mode\n");
    printf("H Hexadecimal Mode\n");
    printf("D Decimal Mode \n");
    printf("C Clear Accumulator\n");
    printf("S Set Accumulator\n");
    printf("Q Quit\n");
    scanf(" %c", &option);
    printf("Option: %c\n", option);
    return option; /* scanf takes user string entered and stores it in option;
	hopefully printf prints the string value entered by the user too; or would it be *s?? hmm */
    ;
}

void print_acc(short acc)
{
    /* HOW DO I SET ACC VALUE FROM HERE?? */

    printf("****************************************\n");
    printf("* Accumulator:                         *\n");
    printf("*   Hex     : %04hX                     *\n", acc);
    printf("*   Octal   : %05ho                    *\n", acc);
    printf("*   Decimal : %-5hd                    *\n", acc);
    printf("****************************************\n");
}

short get_operand(char mode) // read in numeric value in mode; return value
{
    short acc = 0;
    switch (mode)
    {
    case 'H':
        scanf(" %hX", &acc);
        printf("Enter a hex value: %hX\n", acc);
        break;
    case 'O':
        scanf(" %ho", &acc);
        printf("enter octal value: %ho\n", acc);
        break;
    case 'D':
        scanf(" %hd", &acc);
        printf("Enter a decimal value:%d \n", acc);
        break;
    } //switch cases for each possible mode given scans value as such and then it is returned to do its' thing
    return acc;
}