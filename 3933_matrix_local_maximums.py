
class Solution:

    def countLocalMaximums(self, matrix: list[list[int]]) -> int:

        rows = matrix

        local_max_count = 0

        j_max, i_max = 0, 0
        val_max = 0

        matrix_tuple = ()

        for j, col in enumerate(rows):

            for i, val in enumerate(col):

                # matrix_tuple = matrix_tuple + ((j, i, val),)

                if val > val_max:
                   j_max, i_max = j, i

        count, matrix = self.local_max(val_max, j_max, i_max, matrix)

        if 

        # matrix_tuple = sorted(matrix_tuple, key=lambda x: x[2])

        for cell in matrix_tuple:

            count, matrix = self.local_max(cell[2], cell[0], cell[1], matrix)
            local_max_count += count
        
        for j, col in enumerate(rows):

            for i, cell in enumerate(col):

                count, matrix = self.local_max(cell, j, i, matrix)
                local_max_count += count
                ##print(f"Local max count: {local_max_count}")
                ##print(matrix)

        print(matrix)

        return local_max_count


    def local_max(self, val: int, j: int, i:int, matrix: list[list[int]]) -> int:

        if val == 0:
            return 0, matrix

        ##print(f"Checking {val} at ({i}, {j}).")

        for y in range(-val, val + 1):

            for x in range(-val, val + 1):

                j2 = j + y
                i2 = i + x

                if (j2 >= 0 and j2 < len(matrix) and i2 >= 0 and i2 < len(matrix[0])) and (abs(y) + abs(x) != val * 2):

                    #print(f"(j2, i2) = ({j2}, {i2})")

                    if matrix[j2][i2] > val:
                        return 0, matrix

        ##matrix = self.zero_out_lower_vals(val, j, i, matrix)

        return 1, matrix


    def zero_out_lower_vals(self, val: int, j: int, i:int, matrix: list[list[int]]):

        if val == 0:
            return matrix

        for y in range(-val + 1, val):

            for x in range(-val + 1, val):

                j2 = j + y
                i2 = i + x

                if (j2 >= 0 and j2 < len(matrix) and i2 >= 0 and i2 < len(matrix[0])) and (abs(y) + abs(x) < val * 2):

                    val2 = matrix[j2][i2]

                    if (val2 > 0 and val2 < val and abs(x) <= val2 and abs(y) <= val2 and (abs(x) + abs(y) < val2 * 2)):

                        matrix = self.zero_out_lower_vals(val2, j2, i2, matrix)
                        matrix[j2][i2] = 0

        return matrix
