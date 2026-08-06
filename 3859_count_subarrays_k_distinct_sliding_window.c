#define sz 108576

//  Fails test:
//  [1,3,5,5,5,3,7,1,2,4,9,2,7,1,7,8,6,4,8,1,7,6,2,2,5,3,10,8,7,10,3,10,6,1,8,5,9,6,6,10,8,9,4,3,9,4,4,2,9,10,72621,18740,22094,45787,8903,73884,31381,47672,2025,27183,45912]
//  Due to execution time limit.

int chk_subarray(int* nums, int k, int m, int w, int b, int target, int* k_vals, int* k_vals_size, int* k_vals_pos, int* k_vals_quant);

void wipe_memory(int* k_vals, int* k_vals_size, int* k_vals_pos, int* k_vals_quant);

void remove_n(int n, int* k_vals, int* k_vals_size, int* k_vals_pos);

void print_vals(int* k_vals, int* k_vals_size, int* k_vals_quant, int* k_vals_pos);

long long countSubarrays(int* nums, int numsSize, int k, int m) {

    int w, j, n, target = 0;
    int min_size = k * m;
    long long int answer = 0;

    //  k_vals holds distinct integer values, unsorted.
    //  k_vals_size holds the total quantity of values within k_values.
    //  k_vals_pos holds position of value n within k_values, for k_values_pos[n].
    //  k_vals_quant holds quantity of value n, for k_quant[n].

    int* k_vals = malloc(sz * sizeof(int));
    int* k_vals_size = malloc(sizeof(int));
    int* k_vals_pos = malloc(sz * sizeof(int));
    int* k_vals_quant = malloc(sz * sizeof(int));

    //  Initialise memory.

    wipe_memory(k_vals, k_vals_size, k_vals_pos, k_vals_quant);

    for (w = numsSize; w >= min_size; w--) {

        for (j = 0; j + (w - 1) < numsSize; j++) {

            //printf("(w, j) (%d, %d)\n", w, j);

            //  Check if subarray starting at nums[i], ending nums[j], meets (k, m) condition.

            answer += chk_subarray(nums, k, m, w, j, target, k_vals, k_vals_size, k_vals_pos, k_vals_quant);
            target = j + w;

            //  As the preceding number from nums is to be cut, reduce quantity counted.

            n = nums[j];

            k_vals_quant[n] -= 1;

            //printf("Removing %d.\n", n);

            //print_vals(k_vals, k_vals_size, k_vals_pos, k_vals_quant);

            if (k_vals_quant[n] == 0) {
                remove_n(n, k_vals, k_vals_size, k_vals_pos);
            }

            //printf("Removed %d.\n", n);

            //print_vals(k_vals, k_vals_size, k_vals_pos, k_vals_quant);

        }

        wipe_memory(k_vals, k_vals_size, k_vals_pos, k_vals_quant);
        target = 0;

    }

    free(k_vals);
    free(k_vals_size);
    free(k_vals_pos);
    free(k_vals_quant);

    return answer;
    
}


void remove_n(int n, int* k_vals, int* k_vals_size, int* k_vals_pos) {

    //  Extract last element of k_vals, and nullify within k_vals.

    int k_mv_val = k_vals[*k_vals_size - 1];
    k_vals[*k_vals_size - 1] = -1;

    //  Extract position of value to be removed from k_vals, nullify within k_vals_pos.

    int k_del_pos = k_vals_pos[n];
    k_vals_pos[n] = -1;

    //  Overwrite data in k_vals.

    k_vals[k_del_pos] = k_mv_val;

    //  Point k_vals_pos of moved data to new location.

    k_vals_pos[k_mv_val] = k_del_pos;

    *k_vals_size -= 1;

}


int chk_subarray(int* nums, int k, int m, int w, int pos, int target, int* k_vals, int* k_vals_size, int* k_vals_pos, int* k_vals_quant) {

    int i, n;

    for (i = target ; i <= (pos + w - 1) ; i++) {

        //  Extract the number from nums.

        n = nums[i];

        //printf("%d ", n);

        //  Check if it has been found before.

        if (k_vals_pos[n] == -1) {

            //  If new integer, store integer and metadata.

            k_vals[*k_vals_size] = n;

            k_vals_pos[n] = *k_vals_size;

            *k_vals_size += 1;

        }

        //  Iterate the quantity of n found.

        k_vals_quant[n] += 1;

    }

    //printf("\n");

    //print_vals(k_vals, k_vals_size, k_vals_pos, k_vals_quant);

    //  Check first that k is satisfied, by checking quantity of quantities counted.

    if (*k_vals_size != k) {
        return 0;
    }

    //  Check that each distinct integer appeared at least m times.

    for (i = 0; i < *k_vals_size; i++) {

        if (k_vals_quant[k_vals[i]] < m) {
            return 0;
        }

    }

    //printf("Returning 1.\n");
    return 1;

}


void wipe_memory(int* k_vals, int* k_vals_size, int* k_vals_pos, int* k_vals_quant) {

    //printf("Wiping memory.\n");

    int i;

    for (i = 0; i < sz; i++) {
        k_vals[i] = -1;
        k_vals_pos[i] = -1;
        k_vals_quant[i] = 0;
    }

    *k_vals_size = 0;

}


void print_vals(int* k_vals, int* k_vals_size, int* k_vals_pos, int* k_vals_quant) {

    int i, n;

    for (i = 0 ; i < *k_vals_size ; i++) {

        n = k_vals[i];

        //printf("(k_val, k_quant, k_pos) (%d %d %d)\n", k_vals[i], k_vals_quant[n], k_vals_pos[n]);
        
    }

    //printf("\n");

}
