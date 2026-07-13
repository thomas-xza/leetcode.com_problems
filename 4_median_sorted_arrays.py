class Solution:

    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

        if nums1 == []:
            return self.calc_median(nums2)
        elif nums2 == []:
            return self.calc_median(nums1)

        if nums1[-1] > nums2[-1]:
            arr_iter = nums1
            arr_sub = nums2
        else:
            arr_iter = nums2
            arr_sub = nums1

        new_arr = []

        ##print(arr_iter, arr_sub)

        j, j_end = 0, 0

        for i in range(len(arr_iter)):

            while(j_end < len(arr_sub) and arr_sub[j_end] <= arr_iter[i]):
                j_end += 1

            ##print("arr_sub[j:j_end]: ", arr_sub[j:j_end])


            if arr_sub[j:j_end] != []:
                new_arr = new_arr + arr_sub[j:j_end] + [arr_iter[i]]
                j = j_end
            else:
                new_arr = new_arr + [arr_iter[i]]

            ##print("new_arr:      ", new_arr)

        return self.calc_median(new_arr)


    def quicksort(self, arr):      

        if len(arr) <= 1:
            return arr

        pivot = arr[len(arr) // 2]

        part_1, part_2 = [], []

        for v in arr:
            if v < pivot:
                part_1 = part_1 + [v]
            else:
                part_2 = part_2 + [v]

        res = self.quicksort(part_1) + self.quicksort(part_2)

        print(res)

        return res


    def calc_median(self, arr):
        mid = len(arr) // 2
        if len(arr) % 2 == 0:
            return (arr[mid] + arr[mid-1]) / 2
        else:
            return arr[mid]
