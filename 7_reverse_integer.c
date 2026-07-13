int reverse(int x){

    if (-10 < x && x < 10) {
        return x;
    }

    char str[1024] = {0};
    char str_rev[1024] = {0};
    sprintf(str, "%d", x);
    int end = 0;
    int i;

    for (i = 0; i < 16 ; i++) {
        printf("%02d %c %d \n", i, str[i], str[i]);
        if (end == 0 && str[i] == 0) {
            end = i - 1;
        }
    }

    printf("end char: %d \n", i);

    if (str[0] == '-')
        str_rev[0] = '-';

    for (i = end; i >= 0 ; i--) {
        if (str[0] == '-') {
            if (i != 0)
                str_rev[end - i + 1] = str[i];
        } else {
            str_rev[end - i] = str[i];
        }
    }

    for (i = 0; i < 16 ; i++) {
        printf("%02d %c %d \n", i, str_rev[i], str_rev[i]);
    }

    char max[11] = "2147483647";
    int diff = 0;
    int check_overflow = 0;

    if (end > 9 && str[0] != '-') {
        return 0;
    } else if (end > 10 && str[0] == '-') {
        return 0;
    } else if (end == 9 && str[0] != '-') {
        check_overflow = 1;
    }  else if (end == 10 && str[0] == '-') {
        check_overflow = 1;
        diff = 1;
    }

    if (check_overflow == 1) {
        printf("checking overflow...\n");
        for (i = 0; i < 10 ; i++) {
            printf("%c %c \n", str_rev[i + diff], max[i]);          
            if (str_rev[i + diff] > max[i]) {
                return 0;
            } else if (str_rev[i + diff] < max[i]) {
                break;
            }
        }
    }

    return atoi(str_rev);

}
