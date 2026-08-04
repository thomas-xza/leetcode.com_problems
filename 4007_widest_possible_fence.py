from collections import Counter
import copy

##  Relatively brute-force solution. Hits memory limits on test 195/856.

class Solution:

    def maximumWidth(self, planks: list[int]) -> int:

        if len(planks) == 1:
            return 1

        h_min = min(planks)
        h_max = max(planks)
        h_range = h_max - h_min

        # h_avg = sum(planks) / len(planks)

        # mid = len(planks // 2)

        # if len(planks) % 2 == 1:
        #     h_median = planks[mid]
        # else:
        #     h_median = (planks[mid] + planks[mid + 1]) / 2

        counts = Counter(planks)

        planks_uniq = list(counts.keys())

        heights = {}

        for i in range(min(planks_uniq), max(planks_uniq) * 2 + 1):

            heights[i] = 0

        for i in range(len(planks_uniq)):

            for j in range(i, len(planks_uniq)):

                p1 = planks_uniq[i]
                p2 = planks_uniq[j]

                h = p1 + p2

                if p1 == p2:
                    
                    if counts[h] != 0:
                        heights[h] += counts[p1] // 2

                else:

                    heights[h] += min([counts[p1], counts[p2]])

        for i in list(counts.keys()):

            heights[i] += counts[i]

        return max(heights.values())


        # for i in range(h_min, h_max + 1):

        #     if i not in counts:

        #       counts[i] = 0

        # # h_mid = h_min + (h_range // 2)

        # if h_median < h_avg:
        #     h_limit = h_avg
        # elif h_median > h_avg:
        #     hb

        # fence_len_max = 0

        # for h_target in range(h_min, h_limit + 1):

        #     ##print(h_target)

        #     h_target_mid = h_min + ((h_target - 1 - h_min) // 2)

        #     counts_tmp = copy.deepcopy(counts)

        #     fence_len = 0

        #     ##print(h_min, h_target, h_target_mid)

        #     for h_part in range(h_min, h_target_mid + 1):

        #         if counts_tmp[h_part] != 0:

        #             h_part_2 = h_target - h_part

        #             ##print(f"(h_target, h_part, h_part_2) ({h_target}, {h_part}, {h_part_2})")

        #             while counts_tmp[h_part] > 0 and counts_tmp[h_part_2] > 0:

        #                     counts_tmp[h_part] -= 1
        #                     counts_tmp[h_part_2] -= 1
        #                     fence_len += 1

        #     fence_len += counts_tmp[h_target]

        #     if fence_len > fence_len_max:

        #         fence_len_max = fence_len

        # return fence_len_max
