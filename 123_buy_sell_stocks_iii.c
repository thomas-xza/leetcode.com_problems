#include <limits.h>

//  The implementation idea is to compress the prices list, and then select best two options from a much more limited range. 
//  This is an O(n^2) solution!
//  Admittedly, it shouldn't have been implemented in C; the algorithm is fast enough, writing C has slowed down the process of implementation.

//  Currently, a few last Leetcode tests fail to pass, and they are too highly scaled to debug; there is some unknown discrepancy between the algorithm used to write the tests, and this one.
//  98.24% of the (alleged) max profit is reached, in the case of the first failing test.

#define DAYS 1024

int suffix_cut(int* prices, int pricesSize);
int chk_profitability(int* prices, int pricesSize);
int compress_ascending_or_descending(int* prices, int pricesSize, int direction);
void print_prices(int* prices, int pricesSize);
int merge_smallest_adjacent_profits(int* prices, int pricesSize);
int gen_options(int* prices, int pricesSize, int* options);
int calc_profit(int* prices, int pricesSize);
int cut_calc_profit(int* prices, int pricesSize, int target);

int maxProfit(int* prices, int pricesSize) {

    int i;  //  start, end, value

    pricesSize = suffix_cut(prices, pricesSize);

    if (chk_profitability(prices, pricesSize) == 0)
        return 0;

    int profit = 0;

    print_prices(prices, pricesSize);
    printf("Compressing prices...\n");
    pricesSize = compress_ascending_or_descending(prices, pricesSize, -1);
    pricesSize = compress_ascending_or_descending(prices, pricesSize, 1);
    print_prices(prices, pricesSize);

    int options[DAYS] = {0};

    gen_options(prices, pricesSize, options);

    int target_size;

    if (options[1] > 0) {
        target_size = 4;
    } else {
        target_size = 5;
    }

    printf("Merging prices...\n");

    int max_profit = INT_MIN;
    int new_profit = calc_profit(prices, pricesSize);
    int prices_size_prev = INT_MAX;

    while (pricesSize > target_size && new_profit >= max_profit && pricesSize != prices_size_prev) {
        prices_size_prev = pricesSize;
        max_profit = new_profit;
        gen_options(prices, pricesSize, options);
        print_prices(options, pricesSize);
        pricesSize = merge_smallest_adjacent_profits(prices, pricesSize);
        print_prices(prices, pricesSize);
        new_profit = calc_profit(prices, pricesSize);
        printf("new_profit: %d \n", new_profit);
    }

    if (new_profit > max_profit)
        return new_profit;

    return max_profit;

}


int calc_profit(int* prices, int pricesSize) {

    int i;
    int most_profitable[2] = {0};
    int most_profitable_pos[2] = {0};

    int options[DAYS] = {0};
    gen_options(prices, pricesSize, options);

    for (i = 0 ; i < pricesSize; i++) {
        if (options[i] > most_profitable[0]) {
            most_profitable[0] = options[i];
            most_profitable_pos[0] = i;
        }
    }

    for (i = 0 ; i < pricesSize; i++) {
        if (options[i] > most_profitable[1] &&
            i != most_profitable_pos[0]) {
            most_profitable[1] = options[i];
            most_profitable_pos[1] = i;
        }
    }

    printf("(%d, %d), (%d, %d)\n", most_profitable[0], most_profitable_pos[0], most_profitable[1], most_profitable_pos[1]);

    return most_profitable[0] + most_profitable[1];

}


int merge_smallest_adjacent_profits(int* prices, int pricesSize) {

    //  Iterate over the prices, find smallest two ascending options, merge.

    //  Conditions for resulting merge:
    //  Overall profit must be larger than before merge.

    //  TODO: try fitting cut_calc_profit() into this function.

    int options[DAYS] = {0};
    int i, potential_merge;
    int best_merge = INT_MAX;
    int best_profit = INT_MIN;

    for (i = 0 ; i < pricesSize - 1; i++) {
        printf("i = %d\n", i);
        options[i+1] = prices[i+1] - prices[i];
        //printf("%d ", options[i+1]);
        if (i > 1) {
            potential_merge = options[i-1] + options[i] + options[i+1];
            printf("potential_merge = %d\n", potential_merge);
            if (prices[i-2] <= prices[i-1] &&
                prices[i-2] <= prices[i] &&
                prices[i-2] <= prices[i+1] &&
                prices[i-1] >= prices[i] &&
                prices[i-1] < prices[i+1] &&
                prices[i] <= prices[i+1] &&
                potential_merge <= best_merge &&
                potential_merge >= 0) {
            if (cut_calc_profit(prices, pricesSize, i-1) > best_profit) {
                best_merge = i - 1;
                printf("best_merge = %d \n", i);
            }
            }
        }
    }

    if (best_merge == INT_MAX)
        return pricesSize;

    for (i = best_merge ; i < pricesSize - 2 ; i++) {
        prices[i] = prices[i+2];
    }

    return pricesSize - 2;

}


int cut_calc_profit(int* prices, int pricesSize, int target) {

    int prices_new[DAYS] = {0};
    int i;
    
    for (i = 0; i < pricesSize - 2; i++) {
        if (i < target) {
        prices_new[i] = prices[i];
        } else {
            prices_new[i] = prices[i+2];
        }
    }

    return calc_profit(prices_new, pricesSize - 2);

}


int gen_options(int* prices, int pricesSize, int* options) {

    int i;
    for (i = 0 ; i < pricesSize - 1; i++) {
        options[i+1] = prices[i+1] - prices[i];
        //printf("%d ", options[i+1]);
    }
    return 0;

}


void print_prices(int* prices, int pricesSize) {

    int i;
    for (i = 0; i < pricesSize; i++) {
        printf("%d ", prices[i]);
    }
    printf("\n");

}


int compress_ascending_or_descending(int* prices, int pricesSize, int direction) {

    int prices_new[DAYS] = {0};
    int seq = 0;
    int j = 0;
    int i;

    for (i = 0; i < pricesSize; i++) {

        if (direction == 1 && i < pricesSize - 1 && prices[i] <= prices[i+1]) {
            seq++;
        } else if (direction == -1 && i < pricesSize - 1 && prices[i] >= prices[i+1]) {
            seq++;
        } else if (seq >= 1) {
            prices_new[j] = prices[i - seq];
            prices_new[j+1] = prices[i];
            //printf("%d %d ", prices_new[j], prices_new[j+1]);
            j += 2;
            seq = 0;
        } else {
            prices_new[j] = prices[i];
            //printf("%d ", prices_new[j]);
            j += 1;
            seq = 0;
        }
        //printf("(%d, %d) ", prices[i], seq);

    }

    int prices_size_new = j;
    j = 0;

    for (i = 0 ; i < pricesSize ; i++) {
        if (i < prices_size_new) {
            prices[i] = prices_new[j];
            //printf("(%d) ", prices_new[j]);
            j++;
        } else {
            prices[i] = -1;
        }
    }

    return prices_size_new;

}


int suffix_cut(int* prices, int pricesSize) {

    int suffix_zeros_cut = 0;

    if (prices[pricesSize - 1] == 0) {
        for (int i = pricesSize - 1; i >= 0 ; i--) {
            if (suffix_zeros_cut == 0 && prices[i] == 0)
                pricesSize -= 1;
            if (prices[i] == 0 && prices[i-1] != 0)
                suffix_zeros_cut = 1;
        }
    }

    return pricesSize;

}


int chk_profitability(int* prices, int pricesSize) {

    int check_profitability = 0;

    for (int i = 0 ; i < pricesSize - 1 ; i++) {
        if (prices[i + 1] - prices[i] > 0)
            check_profitability += 1;
    }

    return check_profitability;

}
