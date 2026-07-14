#include <limits.h>

//  This is a brute-force backtracking algorithm. The last few Leetcode tests reject this due to timing.

#define DAYS 1024

typedef struct {
    int end;
    int val;
} option;

int suffix_cut(int* prices, int pricesSize);
int chk_profitability(int* prices, int pricesSize);
int find_next_fit(option (*all_options)[DAYS], int* start, int* id_init, int pricesSize);


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
 
    //  Brute-force backtracking algorithm.

    //  Find next fit, fit into sequence.
    //  Use end date as starting date.
    //  Loop until no more fits available.
    //  Calculate profit, compare to best known profit.
    //  Backtrack, starting from previous addition to sequence onwards.
    //  Continuously backtrack if none available.

    int seq[DAYS] = {0};
    int seq_ids[DAYS] = {0};
    int best_seq[DAYS] = {0};
    int best_profit = 0;
    int s_pt = 0;
    int seq_pt = 0;
    int fit_res = 0;
    int j = 0;  

    //printf("(start, end, val)\n");
    profit = 0;
    i = -1;

    while (seq_pt != -1) {
        
        //  Find next fit, fit into sequence.
        fit_res = find_next_fit(all_options, &s_pt, &i, pricesSize);

        //printf("(fit_res, s_pt, i, seq_pt) = %d, %d, %d %d\n", fit_res, s_pt, i, seq_pt);

        if (fit_res > 0) {
            seq[seq_pt] = s_pt;
            seq_ids[seq_pt] = i;
            seq_pt++;
            
            //  Use end date as new starting date.
            s_pt = all_options[s_pt][i].end;

            //  Begin from start of new day.
            i = 0;

        } else if (fit_res < 0) {

            //  Calculate profit, compare to best known profit.

            profit = 0;

            for (j = 0; j < seq_pt ; j++) {
                profit += all_options[seq[j]][seq_ids[j]].val;
            }

            if (profit > best_profit) {
                best_profit = profit;
                for (j = 0; j < seq_pt ; j++) {
                    best_seq[j] = seq[j];
                }
            }

            // for (j = 0; j < seq_pt; j++) {
            //     printf("%d ", seq[j]);
            // }
            //printf("\nprofit = %d\n", profit);

            //  Backtrack, starting from previous addition to sequence onwards.

            seq_pt--;

            if (seq_pt != -1) {
                s_pt = seq[seq_pt];
                i = seq_ids[seq_pt];
            }

        }

        //  Loop until no more fits available.
    
    }

    // for (s = 0 ; s < pricesSize ; s++) {
    //     i = 0;

    //     while (all_options[s][i].val != 0) {

    //         printf("(%d, %d, %d)\n", s, all_options[s][i].end, all_options[s][i].val);
    //         i++;

    //     }
    // }

    return best_profit;

}


int find_next_fit(option (*all_options)[DAYS], int* start, int* id_init, int pricesSize) {

    int s, i;

    //printf("find_next_fit()\n");

    //printf("(start) = %d\n", *start);
    //printf("(id_init) = %d\n", *id_init);

    for (s = *start ; s < pricesSize ; s++) {

        if (s == *start) {
            i = *(id_init) + 1;
        } else {
            i = 0;
        }

        //printf("(s, i) = %d, %d\n", s, i);

        if (all_options[s][i].val != 0) {

            *start = s;
            *id_init = i;
            return 1;

        }
    
    }

    return -1;

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
