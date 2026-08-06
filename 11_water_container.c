#define LIMIT 10000
#define LIMITSIZE 10001

//  Overall approach is to re-arrange data, and reduce computations as a result.
//  One fiddly edge case arose as a result of the data structures chosen - see area_3.

//  The initial brute force solution didn't pass all tests, so optimisations were made.
//  However, the algorithm is still ultimately O(n^2), when all data is unique.

int subtract_s_from_l(int a, int b);

int maxArea(int* height, int heightSize) {

    int i, j;
    int data[LIMITSIZE][2];

    //  Nullify data structure - O(1).

    for (i = 0; i < LIMITSIZE; i++) {
        data[i][0] = -1;
        data[i][1] = -1;
    }

    //  Invert the data structure; store positions via height - O(n).

    for (i = 0; i < heightSize; i++) {
        if (data[height[i]][0] == -1) {
            data[height[i]][0] = i;
        } else {
            data[height[i]][1] = i;
        }
    }

    //  The data is now relatively ordered, so calculate best area - O(n^2) if all data unique.

    int h1, h2;
    int l_up;
    int l_low;
    int r_up;
    int r_low;
    int area_1 = 0;
    int area_2 = 0;
    int area_3 = 0;
    int best_area = 0;

    for (h1 = LIMIT; h1 > 0; h1--) {

        l_up = data[h1][0];
        r_up = data[h1][1];

        if (l_up != -1) {

            for (h2 = h1; h2 > 0 ; h2--) {

                l_low = data[h2][0];
                r_low = data[h2][1];

                if (l_low != -1) {

                    //  Take two heights: h1, h2.
                    //  Generate area using leftmost h1 and rightmost h2, and vice versa.

                    if (l_up != -1 && r_low != -1) {
                        area_1 = h2 * subtract_s_from_l(r_low, l_up);
                    //printf("(h1, h2) = (%d, %d)\n", h1, h2);
                        //printf("  (l, r) = (%d, %d)\n", l_up, r_low);

                    }
                    
                    if (r_up != -1 && l_low != -1) {
                        area_3 = h2 * subtract_s_from_l(r_up, l_low);;
                    //printf("(h1, h2) = (%d, %d)\n", h1, h2);
                        //printf("  (l, r) = (%d, %d)\n", l_low, r_up);
                    }

                    //  In the case that only leftmost is known of h1 or h2, generate an area.
                  
                    if ((l_up != -1 && (r_low == -1 || r_up == -1) && l_low != -1)) {

                        //  Cover the case in which only one instance of a number exists.
                        area_3 = h2 * subtract_s_from_l(l_up, l_low);
                    //printf("(h1, h2) = (%d, %d)\n", h1, h2);
                       //printf("  (l, l) = (%d, %d)\n", l_up, l_low);
                    }

                    if (area_1 > best_area)
                        best_area = area_1;

                    if (area_2 > best_area)
                        best_area = area_2;

                    if (area_3 > best_area)
                        best_area = area_3;

                }

            }

        }
        
    }

    return best_area;
}

int subtract_s_from_l(int a, int b) {

    if (a > b)
        return a - b;

    return b - a;

}
