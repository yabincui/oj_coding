import sys
import Queue

# binary index tree can return min slot.
class MinBIT(object):
    def __init__(self, k):
        self.k = k
        self.sum_array = [0 for x in range(k + 1)]
        self.count_array = [0 for x in range(k)]

    def push(self, value):
        if value >= k:
            return
        self.count_array[value] += 1
        if self.count_array[value] == 1:
            self._setBit(value)

    def pop(self, value):
        if value >= k:
            return
        self.count_array[value] -= 1
        if self.count_array[value] == 0:
            self._clearBit(value)

    def _setBit(self, value):
        value += 1
        while value <= self.k:
            self.sum_array[value] += 1
            value += (value & (~value + 1))

    def _clearBit(self, value):
        value += 1
        while value <= self.k:
            self.sum_array[value] -= 1
            value += (value & (~value + 1))


    def getMinSlot(self):
        if self._getSum(self.k-1) == self.k:
            return self.k
        low = 0
        high = self.k - 1
        while low != high:
            mid = (low + high) / 2
            t = self._getSum(mid)
            #print 'low = %d, high = %d, mid = %d, t = %d, k = %d' % (low, high, mid, t, self.k)
            if t == mid + 1:
                low = mid + 1
            else:
                high = mid
        return high

        
    def _getSum(self, value):
        value += 1
        result = 0
        while value != 0:
            result += self.sum_array[value]
            value &= value - 1
        return result


with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        s = test.split(',')
        (n, k, a, b, c, r) = [int(x) for x in s]
        #print 'n = %d, k = %d' % (n, k)
        sum_array = [0 for x in range(k)]
        count_array = [0 for x in range(k)]
        queue = Queue.Queue(k)
        BIT = MinBIT(k)
        queue.put(a)
        BIT.push(a)
        count = 1
        while count < k:
            a = (b * a + c) % r
            #print 'put count = %d' % count
            queue.put(a)
            BIT.push(a)
            count += 1

        while count < n:
            #print 'get min slot'
            value = BIT.getMinSlot()
            #print 'min slot is %d' % value
            BIT.pop(queue.get())
            #print 'after get pop'
            queue.put(value)
            #print 'after put %d' % value
            BIT.push(value)
            #print 'after push %d' % value
            count += 1
        print value
