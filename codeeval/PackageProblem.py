import sys


def main():
    with open(sys.argv[1], 'r') as test_cases:
        for test in test_cases:
            test = test.strip()
            if len(test) == 0:
                continue
            (total_weight, items) = test.split(':')
            total_weight = float(total_weight)
            items = items.strip().split(' ')
            for i in range(len(items)):
                (index, weight, price) = \
                    items[i][items[i].index('(') + 1 : items[i].index(')')].split(',')
                index = int(index)
                weight = float(weight)
                price = float(price[1:])
                items[i] = (index, weight, price)
            n = len(items)
            mask = (1 << n) - 1
            s = [-1 for x in range(mask + 1)]
            s[0] = (0, 0)
            for i in range(1, mask + 1):
                bit = -1
                for j in range(0, n):
                    if (i & (1 << j)) != 0:
                        bit = j
                        break
                prev = i & ~(1 << bit)
                s[i] = (s[prev][0] + items[bit][1], s[prev][1] + items[bit][2])
            best_weight = -1
            best_price = -1
            best_bits = 0
            for i in range(0, mask + 1):
                if s[i][0] <= total_weight:
                    if s[i][1] > best_price or (s[i][1] == best_price and s[i][0] < best_weight):
                        best_weight = s[i][0]
                        best_price = s[i][1]
                        best_bits = i
            result_list = []
            for i in range(n):
                if (best_bits & (1 << i)) != 0:
                    result_list.append(items[i][0])
            result_list = sorted(result_list)
            if len(result_list) == 0:
                print '-'
            else:
                for i in range(len(result_list)):
                    if i != 0:
                        sys.stdout.write(',')
                    sys.stdout.write('%d' % result_list[i])
                print


main()
