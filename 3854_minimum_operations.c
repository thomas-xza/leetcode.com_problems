//  This needs rewriting as the original problem was not initially understood.
//  It was initially thought that the objective was how to toggle bits to make all numbers odd, or all numbers even.
//  The objective is finding bits required to toggle to make all odd or all even...
//  The resulting code became a mess of the two ideas, but the latter was starting to break out at least.

void simplify_array(int* xs, int xs_len, int* xs_v2);
void print_arr(int* xs, int xs_len);

int find_patterns(int* xs, int xs_len, int* xs_meta);
int maximise_difference(int* xs, int xs_len, int* xs_meta);

int* makeParityAlternating(int* nums, int numsSize, int* returnSize) {

    int* xs_v2 = malloc(numsSize * sizeof(int));

    int* xs_meta = malloc(numsSize * sizeof(int));

    int* answer = malloc(2 * sizeof(int));

    simplify_array(nums, numsSize, xs_v2);

    answer[0] = find_patterns(xs_v2, numsSize, xs_meta);

    answer[1] = maximise_difference(nums, numsSize, xs_meta);

    print_arr(xs_v2, numsSize);

    returnSize[0] = answer[0];

    return answer;

}

int maximise_difference(int* xs, int xs_len, int* xs_meta) {

    //  Ultimately there are only 2 arrays that are parity alternating.

    int* xs_pat_a = malloc(xs_len * sizeof(int));
    int* xs_pat_b = malloc(xs_len * sizeof(int));

    int i, max = -1, min = 65536, max_pos, min_pos;

    //  Find minimums, maximums.

    for (i = 0 ; i < xs_len ; i++) {

        if (xs[i] > max)
            max = xs[i];
            max_pos = i;

        if (xs[i] < min)
            min = xs[i];
            min_pos = i;

    }

    //  Generate the ideal patterns.

    int toggle = 1;

    for (i = 0; i < xs_len; i++) {

        if (toggle == 1) {
            xs_pat_a[i] = 1;
            xs_pat_b[i] = 2;
        } else {
            xs_pat_a[i] = 2;
            xs_pat_b[i] = 1;
        }

        toggle *= -1;

    }

    int max_a = max, min_a = min;
    int max_b = max, min_b = min;

    //  Toggle the patterns, aiming to reduce max(pat_x) - min(pat_x).
    //  Boilerplate style but anyway.

    for (i = 0 ; i < xs_len ; i++) {

        if (xs_meta[i] == xs_pat_a[i]) {

            xs_pat_a[i] = xs[i];

        } else {

            if (xs[i] == max_a) {
                xs_pat_a[i] = xs[i] - 1;
            } else if (xs[i] == min_a) {
                xs_pat_a[i] = xs[i] + 1;
            } else {
                xs_pat_a[i] = xs[i] + 1;
            }

        }

        if (xs_meta[i] == xs_pat_b[i]) {

            xs_pat_b[i] = xs[i];

        } else {

            if (xs[i] == max_b) {
                xs_pat_b[i] = xs[i] - 1;
            } else if (xs[i] == min_b) {
                xs_pat_b[i] = xs[i] + 1;
            } else {
                xs_pat_b[i] = xs[i] + 1;
            }

        }

    }

    //  Recalculate the maximums/minimums (may be a more succint way).

    min_a = 65536, max_a = -65536;
    min_b = 65536, max_b = -65536;

    for (i = 0 ; i < xs_len ; i++) {

        if (xs_pat_a[i] > max_a)
            max_a = xs_pat_a[i];

        if (xs_pat_a[i] < min_a)
            min_a = xs_pat_a[i];

        if (xs_pat_b[i] > max_b)
            max_b = xs_pat_b[i];

        if (xs_pat_b[i] < min_b)
            min_b = xs_pat_b[i];

    }

    print_arr(xs_pat_a, xs_len);
    print_arr(xs_pat_b, xs_len);

    int diff1 = max_a - min_a, diff2 = max_b - min_b;

    printf("(diff1, diff2), (%d, %d)\n", diff1, diff2);

    if (diff1 < diff2)
        return diff1;

    return diff2;

}

int find_patterns(int* xs, int xs_len, int* xs_meta) {

    int* xs_pat_a = malloc(xs_len * sizeof(int));
    int* xs_pat_b = malloc(xs_len * sizeof(int));

    int i;

    //  Generate the ideal patterns.

    int toggle = 1;

    for (i = 0; i < xs_len; i++) {

        if (toggle == 1) {
            xs_pat_a[i] = 1;
            xs_pat_b[i] = 2;
        } else {
            xs_pat_a[i] = 2;
            xs_pat_b[i] = 1;
        }

        toggle *= -1;

    }

    int pat_a = 0, pat_b = 0;

    //  Count the quantities of either embedded pattern.

    print_arr(xs, xs_len);

    for (i = 0 ; i < xs_len ; i++) {

        if (xs[i] == xs_pat_a[i])
            pat_a++;

        if (xs[i] == xs_pat_a[i])
            pat_b++;

    }

    printf("(pattern_a, pattern_b) (%d, %d)\n", pat_a, pat_b);

    if (pat_a < pat_b)
        return pat_a;

    free(xs_pat_a);
    free(xs_pat_b);

    return pat_b;

}

void print_arr(int* xs, int xs_len) {

    int i;

    for (i = 0; i < xs_len ; i++) {
        printf("%d ", xs[i]);
    }

    printf("\n");

}

void simplify_array(int* xs, int xs_len, int* xs_v2) {

    int i;

    for (i = 0; i < xs_len ; i++) {
        if (xs[i] % 2 == 0) {
            xs_v2[i] = 1;
        } else {
            xs_v2[i] = 2;
        }
    }

}

