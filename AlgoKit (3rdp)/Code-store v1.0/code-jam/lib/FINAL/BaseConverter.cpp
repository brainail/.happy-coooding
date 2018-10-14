/**
 * BaseConverter
 * Only for positive integers
 * and bases between 2 and 36
 */
#include <cstdio>
#include <cstring>
#include <cmath>

char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
                 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                };

char * decimalToAny(int number, int base)
{
    int digitValue;
    char *result = new char[40];
    int counter = 0;

    if((number > 0) && (base >= 2 && base <= 36))
        while(number) {
            digitValue = number % base;
            number /= base;
            result[counter++] = digits[digitValue];
        }

    result[strlen(result)] = '\0';
    return result;
}

int main()
{
    int number = 255, base = 16;
    char * ea = decimalToAny(number, base);
    printf("dec(255) = (%s, base %d)\n", ea, base);
    return 0;
}
