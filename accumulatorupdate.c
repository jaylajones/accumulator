#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Spaces must be inserted after every four  binary digits for readability.  For consistency, declareall binary strings as character strings of size 20 (to hold the 16 bits, the string terminator character, andspaces, if necessary
unsigned short get_binary_op(char *bin);
void convert_to_binary(short acc, char *bin);
short get_operand(char mode); /* read in numeric value in mode; return value */
void print_acc(short acc);    /* print out accumulator values */
char print_menu(void);        /* print menu and get option */
void add(short *acc, char mode);
void subtract(short *acc, char mode);

char print_menu(void)
{
    char option;
    printf(" Please select one of the following options:\n");
    printf("\nB Binary Mode           & AND with Accumulator       +  Add to Accumulator  \n");
    printf("O Octal Mode            |  OR  with Accmulator      - Subtract from Accumulator   \n");
    printf("H Hexadecimal Mode      ^  XOR with Accumulator      N  Negate Accumulator   \n");
    printf("D Decimal Mode          ~  Complement Accumulator  \n");
    printf("\nC Clear Accumulator     <  Shift Accumulator Left \n");
    printf("S Set Accumulator       >  Shift Accumulator Right\n\n");
    printf("\nQ Quit\n");
    scanf(" %c", &option);
    printf("\nOption: %c\n", option);
    return option;
    /* scanf takes user string entered and stores it in option;
	hopefully printf prints the string value entered by the user too; or would it be *s?? hmm */
    ;
}

void print_acc(short acc)
{
    char array[20];
    convert_to_binary(acc, array);
    /* HOW DO I SET ACC VALUE FROM HERE?? */

    printf("****************************************\n");
    printf("* Accumulator:                         *\n");
    printf("*   Binary  : %s      *\n", array);
    printf("*   Hex     : %04hX                     *\n", acc);
    printf("*   Octal   : %05ho                    *\n", acc);
    printf("*   Decimal : %-5hd                    *\n", acc);
    printf("****************************************\n");
}

short get_operand(char mode) // read in numeric value in mode; return value
{
    short acc = 0;
    char bin_array[20];
    switch (mode)
    {
    case 'B':
        printf("Enter a binary value: ");
        scanf(" %s", bin_array);        //scans users binary string
        acc = get_binary_op(bin_array); // set accumulator to what is returned from calling get_binary_op
        printf("Value entered: %s", bin_array);
        break;
    case 'H':
        printf("Enter a hex value: ");
        scanf(" %hX", &acc);
        printf("Value entered: %hX", acc);
        break;
    case 'O':
        printf("Enter octal value: ");
        scanf(" %ho", &acc);
        printf("Value entered: %ho", acc);
        break;
    case 'D':
        printf("Enter a decimal value: ");
        scanf(" %hd", &acc);
        printf("Value entered: %d", acc);
        break;

    } //switch cases for each possible mode given scans value as such and then it is returned to do its' thing
    printf("\n");
    return acc;
}

unsigned short get_binary_op(char *bin) //convert bin str to short; return value
{
    char array_val;
    unsigned short sum = 0;
    int power = 1;
    int i = 19;
    int adding = 0;

    while (i >= 0)
    {
        array_val = bin[i];
        if (array_val == '\0')
        {
            adding = 1;
        }
        if (adding == 0)
        {
            //something wrong with continue statements
        }
        if (array_val == '1')
        {
            sum += power;
            power *= 2;
        }
        if (array_val == '0')
        {
            power *= 2;
        }
        i--;
    }
    return sum;
}
void convert_to_binary(short acc, char *bin) //convert acc to binary str for output
{
    int i;
    for (i = 18; i >= 0; i--)
    {
        if (i == 4 || i == 9 || i == 14)
        {
            bin[i] = ' ';
            continue;
        }
        if ((acc & 1) == 1)
        {
            bin[i] = '1';
        }
        else
        {
            bin[i] = '0';
        }
        acc = acc >> 1;
    }
    bin[19] = '\0';
}
void add(short *acc, char mode) //call get_operand to get valin mode toadd to accum; detect pos/neg overflow
{
    short num2 = get_operand(mode);
    short num1 = *acc;
    //if(acc>0 && num2>0){
    *acc = num2 + num1;
    if (num1 > 0 && num2 > 0 && (*acc) < 0)
    { // conditional that checks if acc and num2 are positive AND value of acc is negative, then there is an overflow
        printf("overflow error\n");
    }
    if (num1 < 0 && num2 < 0 && (*acc) > 0)
    { // if adding 2 neg numbers and result is positive... overflow has occurred
        printf(" negative overflow errror\n");
    }
}
void subtract(short *acc, char mode) // just like add, but subtract
{
    short num2 = get_operand(mode);
    short num1 = *acc;
    *acc = num1 - num2;
    if (num1 > 0 && num2 < 0 && (*acc) < 0)
    { // case where positive num - neg num; essentially addition but overflow if value returned is negative
        printf(" overflow error \n");
    }
    if (num1 < 0 && num2 > 0 && (*acc) > 0)
    { // case of negative num minus positive num; should be more negative if not... an overlfow has occurred
        printf("negative overflow error\n");
    }
}
//what do binary numbers represent ** 2's comp
int main(void)
{
    /* main menu loop; execute option
or call appropriate function */
    char mode = 'D';
    char input[10];
    short acc;
    int shift_amount;
    char options;
    short num2;
    char valid_input[20] = "OHDCSQB&|^~><+-N";
    char user_option; // may need to change
    do
    {
        print_acc(acc);
        user_option = print_menu(); /*returns the user value*/
        ;
        user_option = toupper(user_option);
        switch (user_option)
        {
        case '<':
            printf("Enter number of positions to left shift accumulator: ");
            printf("%d\n", shift_amount);
            scanf("%d", &shift_amount);
            acc = acc << shift_amount;
            break;

        case '>':
            printf("Enter number of positions to right shift accumulator: ");
            printf("%d\n", shift_amount);
            scanf("%d", &shift_amount);
            acc = acc >> shift_amount;
            break;
        case '&':
            num2 = get_operand(mode);
            acc = acc & num2;
            break;
        case '|': //or operator
            num2 = get_operand(mode);
            acc = acc | num2;
            break;
        case '^': //xor operator
            num2 = get_operand(mode);
            acc = acc ^ num2;
            break;
        case '+': //addition; calls on add function
            add(&acc, mode);
            break;
        case '-': //subtraction; calls on subtract function
            subtract(&acc, mode);
            break;

        case 'N':
            acc *= -1;
            break;
        case '~':
            acc = ~acc;
            break;
        case 'B':
            printf("Mode is Binary\n");
            mode = user_option;
            break;
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
