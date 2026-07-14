import "fmt"

//  Automatically ported from Python and then hacked on top of a bit more.
//  Passes 697 / 706 tests, failing only due to time limits.

// countLocalMaximums counts local maximums within the provided 2D matrix.
func countLocalMaximums(matrix [][]int) int {
	rows := matrix
	localMaxCount := 0

	jMax, iMax := 0, 0
	valMax := matrix[0][0]
    valMin := matrix[0][0]
    j_min, i_min := 0, 0
    val_min_max_dist := 0

    all_same := 0

    fmt.Println("matrix size =", len(matrix), len(matrix[0]))

    if len(matrix) == 1 && len(matrix[0]) == 1 {
        if matrix[0][0] == 0 {
            return 0
        } else {
            return 1
        }
    }

	// Find initial max coordinates
	for j, col := range rows {
		for i, val := range col {
            if val <= valMin && val > 0 {
                valMin = val
                j_min = j
                i_min = i
            }
			if val > valMax {
				jMax, iMax = j, i
                valMax = val
                all_same = 0
            } else if val == valMax {
                all_same += 1
            }
            if (abs(jMax - j_min) + abs(iMax - i_min)) > val_min_max_dist {
                val_min_max_dist = (abs(jMax - j_min) + abs(iMax - i_min))
            }
		}
	}

    fmt.Println("val_min_max_dist, valMin, valMax =", val_min_max_dist, valMin, valMax)

    if valMax == 0 {
        return 0
    }

    if valMax >= len(matrix) && valMax >= len(matrix[0]) && (val_min_max_dist <= valMin) {
        max_quantity := 0
        for _, col := range rows {
		    for _, val := range col {

                if val == valMax {
                    max_quantity += 1
                }
            }
        }
        fmt.Println("Counting all max values and exiting.")
        return max_quantity
    }

    if all_same == len(matrix) * len(matrix[0]) {
        return len(matrix) * len(matrix[0])
    }

    fmt.Println("all_same =", all_same)


	// First local_max check matching Python flow
	_, matrix = localMax(valMax, jMax, iMax, matrix)

	// Traverse each cell and count valid local maximums
	for j, col := range rows {
		for i, cell := range col {
			count, updatedMatrix := localMax(cell, j, i, matrix)
			matrix = updatedMatrix
			localMaxCount += count
		}
	}

	//fmt.Println(matrix)
	return localMaxCount
}

// localMax checks whether cell (j, i) with value `val` qualifies as a local maximum.
func localMax(val, j, i int, matrix [][]int) (int, [][]int) {
	if val == 0 {
		return 0, matrix
	}

	numRows := len(matrix)
	if numRows == 0 {
		return 0, matrix
	}
	numCols := len(matrix[0])

	for y := -val; y <= val; y++ {
		for x := -val; x <= val; x++ {
			j2 := j + y
			i2 := i + x

			if (j2 >= 0 && j2 < numRows && i2 >= 0 && i2 < numCols) && (abs(y)+abs(x) != val*2) {
				if matrix[j2][i2] > val {
					return 0, matrix
				}
			}
		}
	}

    //matrix = zeroOutLowerVals(val, j, i, matrix)

	return 1, matrix
}

// zeroOutLowerVals recursively sets values below val to zero under specified conditions.
func zeroOutLowerVals(val, j, i int, matrix [][]int) [][]int {
	if val == 0 {
		return matrix
	}

	numRows := len(matrix)
	if numRows == 0 {
		return matrix
	}
	numCols := len(matrix[0])

	for y := -val + 1; y < val; y++ {
		for x := -val + 1; x < val; x++ {
			j2 := j + y
			i2 := i + x

			if (j2 >= 0 && j2 < numRows && i2 >= 0 && i2 < numCols) && (abs(y)+abs(x) < val*2) {
				val2 := matrix[j2][i2]

				if val2 > 0 && val2 < val && abs(x) <= val2 && abs(y) <= val2 && (abs(x)+abs(y) < val2*2) {
					matrix = zeroOutLowerVals(val2, j2, i2, matrix)
					matrix[j2][i2] = 0
				}
			}
		}
	}

	return matrix
}

// Helper function for absolute value of integers
func abs(n int) int {
	if n < 0 {
		return -n
	}
	return n
}
