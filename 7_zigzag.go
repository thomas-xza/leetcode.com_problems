
//  NOTE this was automatically ported via LLM, from a Python implementation.
//  (I lost the original Python implementation as Leetcode stores client-side but seemingly only submitted version).

import (
	"fmt"
)

// convert rearranges the characters of s in the “zig‑zag” pattern
// described by the original Python solution and returns the
// resulting string.
func convert(s string, numRows int) string {
	// The Python version prints the length; we omit that for a clean API.
	if numRows == 1 {
		return s
	}

	// matrix will hold each “row slice” of the zig‑zag.
	matrix := [][]rune{}

	// Position in the input string.
	strPos := 0

	// A template row filled with spaces (runes) of length numRows.
	newRow := make([]rune, numRows)
	for i := range newRow {
		newRow[i] = ' '
	}

	// Index of the row that receives a single character on the
	// “return” part of the zig‑zag.
	zzRowPos := 0

	for strPos < len(s) {
		// copy a fresh row template – deep copy like Python’s copy.deepcopy
		row := make([]rune, numRows)
		copy(row, newRow)

		if zzRowPos == 0 {
			// Fill the whole column (going down).
			for i := 0; i < len(row) && strPos < len(s); i++ {
				row[i] = rune(s[strPos])
				strPos++
			}
			zzRowPos = numRows - 2 // next step will start moving up
		} else {
			// Fill a single cell on the upward diagonal.
			row[zzRowPos] = rune(s[strPos])
			strPos++
			zzRowPos--
		}
		matrix = append(matrix, row)
	}

	// Build the final string by reading column‑wise, skipping spaces.
	var final []rune
	for i := 0; i < numRows; i++ {
		for _, r := range matrix {
			if r[i] != ' ' {
				final = append(final, r[i])
			}
		}
	}
	return string(final)
}
