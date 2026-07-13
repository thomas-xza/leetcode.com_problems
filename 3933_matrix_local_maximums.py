##  Note: this implementation hits a timeout on a test involving large matrix. May need rewriting.

class Solution:
    def countLocalMaximums(self, matrix: list[list[int]]) -> int:

        rows = matrix

        local_max_count = 0
        
        for j, col in enumerate(rows):

            for i, cell in enumerate(col):

                local_max_count += self.local_max(cell, j, i, matrix)

        return local_max_count


    def local_max(self, val: int, j: int, i:int, matrix: list[list[int]]) -> int:

        if val == 0:
            return 0

        #print(f"Checking {val} at ({i}, {j}).")

        for y in range(-val, val + 1):

            for x in range(-val, val + 1):

                j2 = j + y
                i2 = i + x

                if (j2 >= 0 and j2 < len(matrix) and i2 >= 0 and i2 < len(matrix[0])) and (abs(y) + abs(x) != val * 2):

                    #print(f"(j2, i2) = ({j2}, {i2})")

                    if matrix[j2][i2] > val:
                        return 0
        
        return 1

