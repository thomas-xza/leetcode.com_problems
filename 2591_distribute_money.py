class Solution:
    def distMoney(self, money: int, children: int) -> int:

        if (money > 0 and children == 0):
            return -1

        r_1 = money - children

        if r_1 < 0:
            return -1
        
        potential_8 = r_1 // 7

        if potential_8 > children:

            return children - 1

        elif potential_8 == children:

            if r_1 % 7 == 0:
                return potential_8
            elif r_1 % 7 > 0:
                return potential_8 - 1
                
        elif potential_8 < children:

            if r_1 % 7 == 0:
                return potential_8

            elif r_1 % 7 == 3:

                if potential_8 == 0:
                    if children == 1:
                        return -1
                    elif children > 1:
                        return 0

                elif potential_8 > 0:
                    if children == 1:
                        return 0
                    elif children > 1:
                        if children - potential_8 == 1:
                            return potential_8 - 1
                        else:
                            return potential_8

            else:
                return potential_8
