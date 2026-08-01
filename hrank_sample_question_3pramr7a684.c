//  hackerrank.com/test/sample/questions/3pramr7a684

int* oddNumbers(int l, int r, int* result_count) {
    
    *result_count = 0;
    
    int* a;
    
    int len = r - l + 1;
    
    if (l > r) {
        a = malloc(0 * sizeof(int));
        return a;
    } else {
        a = malloc(len * sizeof(int));
    }
    
    //  Deduce result_count instantaneously, separately, for easier debugging.
    
    if (len % 2 == 0) {
        
       *result_count = len / 2;
        
    } else {
        if (l % 2 == 0) {
            
            *result_count = len / 2;
            
        } else {
            
            *result_count = (len / 2) + 1;
            
        }
    }

    //  Generate the odd numbers with minimal mathematics.
    
    int target_odd = l;
    
    if (l % 2 == 0)
        target_odd = l + 1;
    
    int i;
    int j = 0;
    
    for (i = target_odd; i <= r; i = i + 2) {
        
        a[j] = i;
        j++;
        
    }
    
    return a; 
    
}
