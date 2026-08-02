#define sz 108576

//  Fails test:
//  [2,1,4,3,5,6,8,7,10,9,11,12,13,14,95606,60350,87687,15,16,17,18,27749]
//  Due to execution time limit.

int chk_subarray(int* nums, int a, int b, int k, int m, int* p_lookup, int* q, int wipe_memory);

long long countSubarrays(int* nums, int numsSize, int k, int m) {

    int i, j, n;
    int min_size = k * m;
    int res = 0;
    long long int answer = 0;
    int wipe_memory;

    //  sz should be max n within nums.
    //  p_lookup holds address of quantity count.

    int* p_lookup = malloc(sz * sizeof(int));  

    //  q holds quantities of the related value.

    int* q = malloc(sz * sizeof(int));

    for (i = 0; i < numsSize; i++) {

        for (j = i; j < numsSize; j++) {

            //  Check if subarray starting at nums[i], ending nums[j], meets (k, m) condition.

            res = 0;

            //printf("(i, j) (%d, %d)\n", i, j);

            if ((j - i + 1) >= min_size) {
                
                res = chk_subarray(nums, i, j, k, m, p_lookup, q, wipe_memory);
            }

            answer = answer + res;

        }

        wipe_memory = 0;

        //  As the preceding number is to be cut, reduce quantity counted.

        n = nums[i];

        q[p_lookup[n]] -= 1;

        if (q[p_lookup[n]] == 0)
            p_lookup[n] = -1;
            wipe_memory = 1;

    }

    free(p_lookup);
    free(q);

    return answer;
    
}

int chk_subarray(int* nums, int a, int b, int k, int m, int* p_lookup, int* q, int wipe_memory) {

    int i, n;

    // for (i = 0; i < sz; i++) {
    //     q[i] = 0;
    //     p_lookup[i] = -1;
    // }

    int new_q = 0;

    if (wipe_memory) {

        for (i = 0; i < sz; i++) {
            q[i] = 0;
            p_lookup[i] = -1;
        }

        i = a;

    } else {
        i = b;
    }

    for (i = i ; i <= b; i++) {

        //  Extract the numbers from nums.

        n = nums[i];

        //  Check if it has been found before.

        if (p_lookup[n] == -1) {

            p_lookup[n] = new_q;
            new_q++;

        }

        //  Iterate the quantity of n found.

        q[p_lookup[n]] = q[p_lookup[n]] + 1;

        //printf("(n, p_lookup, q) (%d, %d, %d)\n", n, p_lookup[n], q[p_lookup[n]]);

    }

    //  Check first that k is satisfied, by checking quantity of quantities counted.

    int distinct_ints_found = new_q;

    if (distinct_ints_found != k) {
        return 0;
    }

    //  Check that each distinct integer appeared at least m times.

    for (i = 0; i < new_q; i++) {

        if (q[i] < m) 
            return 0;

    }

    //printf("return 1\n");
    return 1;

}

