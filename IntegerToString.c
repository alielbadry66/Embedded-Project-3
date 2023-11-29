#include "IntegerToString.h"

void integerToString(int num, char *str) {
    // Handle the sign (positive or negative)
    if (num < 0) {
        num = -num;
        *str = '-';
        str++;
    }

    // Convert the integer part to a string
    int i = 0;

    do {
        str[i] = (char)(num % 10) + '0';
        num /= 10;
        i++;
    } while (num > 0);

    int len = i;
    int j = 0;

    // Reverse the integer part string to ensure that the string contains the digits in the correct order.
    while (j < len / 2) {
        char temp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = temp;
        j++;
    }

    str[i] = '\0';  // Null-terminate the string
}
