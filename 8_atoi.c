#include <limits.h>

int myAtoi(char* s) {

    int i = 0;
    int j = 0;
    int begin = 0;
    int end = 0;
    int sign = 1;
    int first_char = 0;
    int sign_read = 0;
    char read[512] = {0};

    while (*(s + i) != 0) {
        printf("%c \n", *(s + i));

        if (begin == 0) {

            if (*(s + i) == ' ') {

            } else if (
                    (*(s + i) - 48 >= 0 &&
                   *(s + i) - 48 <= 9) ||
                   *(s + i) == '-' ||
                   *(s + i) == '+') {
                begin = 1;
                first_char = 1;

            } else {
                return 0;
            }
        }
            
        if (begin == 1 && end == 0) {

            if (*(s + i) == '0' && (first_char == 1 || sign_read == 1)) {

                if (*(s + i + 1) == '+' || *(s + i + 1) == '-') {
                    return 0;
                }
                
            } else if (*(s + i) == '+' || *(s + i) == '-'){

                if (first_char == 1) {
                    sign = (*(s + i) - 44) * -1;
                    sign_read = 1;
                    first_char = 0;
                } else {
                    if (myAtoi(&read[0]) == 0) {
                        printf("detected invalid\n");
                        return 0;
                    } else {
                        end = i;
                    }
                }

            } else if (*(s + i) - 48 >= 0 &&
                   *(s + i) - 48 <= 9) {
                read[j] = *(s + i);
                printf("read %c \n", read[j]);
                j++;
                first_char = 0;
                sign_read = 0;

            } else {
                end = i;
            }
        }

        i++;
    }

    printf("read: %s \n", read);

    int null_pos = 0;
    while (read[null_pos] != 0)
        null_pos++;

    printf("\ni = %d \n", i);
    
    long long int multiplier = 1;
    long long int total = 0;

    long long int int_max_32 = INT_MAX;

    for (i = null_pos - 1; i >= 0 ; i--) {

        total += (read[i] - 48) * multiplier;
        printf("%ld %ld %ld \n", read[i] - 48, multiplier, total);

        if (total > int_max_32 || multiplier > int_max_32) {
            total = int_max_32 + 1;
            i = 0;
        }

        multiplier = multiplier * 10;
    }

    printf("\ntotal = %ld \n", total);

    if (sign == -1)
        total = total * -1;

    if (total > INT_MAX)
        return INT_MAX;
    
    if (total < INT_MIN)
        return INT_MIN;

    return total;
}
```
