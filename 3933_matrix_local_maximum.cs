//  Note: this implementation hits a timeout on a test involving large matrix. May need rewriting.

int local_max(int val, int j, int i, int** matrix, int matrixSize, int* matrixColSize);

int countLocalMaximums(int** matrix, int matrixSize, int* matrixColSize) {

    int i, j;
    int local_max_count = 0;

    for (j = 0 ; j < matrixSize ; j++) {
        for (i = 0 ; i < *matrixColSize ; i++) {
            local_max_count += local_max(matrix[j][i], j, i, matrix, matrixSize, matrixColSize);
        }
    }

    return local_max_count;

}

int local_max(int val, int j, int i, int** matrix, int matrixSize, int* matrixColSize) {

    if (matrix[j][i] == 0) {
        return 0;
    }

    int x, y, i2, j2;

    for (y = -val ; y < val + 1 ; y++) {
        for (x = -val ; x < val + 1 ; x++) {

            j2 = j + y;
            i2 = i + x;

            if (j2 >= 0 && j2 < matrixSize && i2 >= 0 && i2 < *matrixColSize && (abs(y) + abs(x) != val * 2)) {

                //printf("(j2, i2) = (%d, %d)", j2, i2);

                if (matrix[j2][i2] > val) {
                    return 0;
                }

            }

        }
    }

    return 1;

}

