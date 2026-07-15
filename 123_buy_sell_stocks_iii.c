#include <limits.h>

//  The implementation is to compress the prices list, and then select best two options from a much more limited range. 
//  This is an O(n) solution!

//  Note that further compression is required to past the last few tests.

#define DAYS 1024

int suffix_cut(int* prices, int pricesSize);
int chk_profitability(int* prices, int pricesSize);
int compress_ascending_or_descending(int* prices, int pricesSize, int direction);
void print_prices(int* prices, int pricesSize);


int maxProfit(int* prices, int pricesSize) {

    int i;  //  start, end, value

    pricesSize = suffix_cut(prices, pricesSize);

    int profit = 0;

    print_prices(prices, pricesSize);
    printf("Compressing prices...\n");
    pricesSize = compress_ascending_or_descending(prices, pricesSize, -1);
    pricesSize = compress_ascending_or_descending(prices, pricesSize, 1);
    print_prices(prices, pricesSize);

    int most_profitable[2] = {0};
    int most_profitable_pos[2] = {0};

    int options[DAYS] = {0};

    for (i = 0 ; i < pricesSize - 1; i++) {
        options[i] = prices[i+1] - prices[i];
        printf("%d ", options[i]);
    }
    printf("\n");

    for (i = 0 ; i < pricesSize - 1; i++) {
        if (options[i] > most_profitable[0]) {
            most_profitable[0] = options[i];
            most_profitable_pos[0] = i;
        }
    }

    for (i = 0 ; i < pricesSize - 1; i++) {
        if (options[i] > most_profitable[1] &&
            i != most_profitable_pos[0]) {
            most_profitable[1] = options[i];
            most_profitable_pos[1] = i;
        }
    }

    printf("(%d, %d), (%d, %d)\n", most_profitable[0], most_profitable_pos[0], most_profitable[1], most_profitable_pos[1]);

    if (chk_profitability(prices, pricesSize) == 0)
        return 0;

    return most_profitable[0] + most_profitable[1];

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

    printf("\n");

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
