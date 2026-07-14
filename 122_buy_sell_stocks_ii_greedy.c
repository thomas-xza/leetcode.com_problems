#include <limits.h>

#define DAYS 1024

//  This is a greedy algorithm implementation, which the Leetcode tests reject.

int suffix_cut(int* prices, int pricesSize);
int chk_profitability(int* prices, int pricesSize);

int maxProfit(int* prices, int pricesSize) {

    int i, s, e, v, best_s, best_e, best_v;  //  start, end, value

    pricesSize = suffix_cut(prices, pricesSize);

    if (chk_profitability(prices, pricesSize) == 0)
        return 0;

    const int days = DAYS;

    if (pricesSize > days) {
        printf("Memory requirements higher than allocated. Exiting.");
        return 0;
    }
    
    //  These data structures stores all potential profit values and duration of share holds.
    //  For each entry all_options[a][b]:
    //    a is a the day the share is bought
    //    b is a unique ID
    
    typedef struct {
        int end;
        int val;
    } option;

    option all_options[DAYS][DAYS];
    int id_counter[DAYS] = {0}; 

    for (s = 0 ; s < days ; s++) {
        for (i = 0 ; i < days ; i++) {
            all_options[s][i].end = 0;
            all_options[s][i].val = 0;
        }
    }

    int profit;

    //  Bucket sort the potential profits.

    for (e = pricesSize - 1 ; e > 0 ; e--) {
        for (s = e - 1 ; s >= 0 ; s--) {
            profit = prices[e] - prices[s];

            if (profit > 0) {
                all_options[s][id_counter[s]].end = e;
                all_options[s][id_counter[s]].val = profit;
                id_counter[s]++;
            }
        }
    }

    float profit_per_day = 0;
    float best_profit_per_day;
    int greedy_total = 0;
 
    //  Tests reject greedy algorithms (both most profitable buy-sells, and most profitable-per-day).

    printf("(start, end, val)\n");

    for (s = 0 ; s < pricesSize ; s++) {
        i = 0;
        best_profit_per_day = 0;
        best_s = s;
        best_e = s+1;
        best_v = 0;

         while (all_options[s][i].val != 0) {

            e = all_options[s][i].end;
            v = all_options[s][i].val;

            // if (v > best_v) {
            //     best_e = e;
            //     best_v = v;
            //     best_s = s;
            // }

            //printf("(%d, %d, %d)\n", s, e, v);
             
            profit_per_day = v / (e - s);

            if (profit_per_day > best_profit_per_day) {
                best_profit_per_day = profit_per_day;
                best_e = e;
                best_v = v;
                best_s = s;
            }

            i++;

        }
        
        greedy_total += best_v;

        if (best_e > s+1)
            printf("(%d, %d, %d) best\n", best_s, best_e, best_v);
            s = best_e - 1;

    }

    // for (s = 0 ; s < pricesSize ; s++) {
    //     i = 0;

    //     while (all_options[s][i].val != 0) {

    //         printf("(%d, %d, %d)\n", s, all_options[s][i].end, all_options[s][i].val);
    //         i++;

    //     }
    // }

    return greedy_total;

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
