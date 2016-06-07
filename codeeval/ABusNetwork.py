# This solution is not completely right, some special cases might be missing.

import sys
import Queue

INF = 1e9

class Node:
    def __init__(self, stop, route):
        self.key = (stop, route)
        self.neighbors = {}
        self.dist = INF
        self.fixed_dist = False

    def addNeighbor(self, other, cost):
        if self.neighbors.has_key(other):
            value = min(self.neighbors.get(other), cost)
            self.neighbors[other] = value
        else:
            self.neighbors[other] = cost

    def __hash__(self):
        return hash(self.key)

    def __eq__(self, other):
        return self.key == other.key

def findShortestPath(nodes, start, end):
    if start == end:
        return 0
    if len(nodes) == 0 or len(nodes[0]) == 0:
        return None
    route_count = len(nodes[0])
    queue = Queue.PriorityQueue()
    for i in range(route_count):
        nodes[start][i].dist = 0
        queue.put((0, nodes[start][i]))
    while not queue.empty():
        (cur_dist, cur_node) = queue.get()
        if cur_dist > cur_node.dist:
            continue
        cur_node.fixed_dist = True
        if cur_node.key[0] == end and cur_node.key[1] >= 0:
            return cur_dist
        for next_node in cur_node.neighbors.keys():
            if next_node.fixed_dist:
                continue
            d = cur_dist + cur_node.neighbors[next_node]
            if d < next_node.dist:
                next_node.dist = d
                queue.put((d, next_node))
    return None

    
def main():
  line = 1
  with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        #print test
        #continue
        items = test.split(' ')
        s = items[0]
        items = items[1:]
        s = s[s.index('(') + 1 : s.index(')')].split(',')
        start = int(s[0])
        end = int(s[1])
        #print 'line = %d' % line
        line += 1
        routes = []
        max_id = max(start, end)
        for i in range(len(items)):
            (a, s) = items[i].split('=')
            if a != ('R%d' % (i + 1)):
                print a
            s = s[s.index('[') + 1 : s.index(']')]
            strs = s.split(',')
            nums = []
            for t in strs:
                nums.append(int(t))
            routes.append(nums)
            max_id = max(max_id, max(nums))
        old_routes = sorted(routes)
        routes = []
        for r in old_routes:
            if len(routes) == 0 or routes[-1] != r:
                routes.append(r)
        nodes = []
        for i in range(max_id + 1):
            nodes.append([])
            for j in range(len(routes)):
                nodes[i].append(Node(i, j))
        for i in range(len(routes)):
            route = routes[i]
            for j in range(len(route)):
                if j == 0:
                    continue
                a = route[j - 1]
                b = route[j]
                if a == b:
                    print '%d is %d' % (a, b)
                nodes[a][i].addNeighbor(nodes[b][i], 7)
                nodes[b][i].addNeighbor(nodes[a][i], 7)
        routes_on_ids = [[] for x in range(max_id + 1)]
        for i in range(len(routes)):
            for j in routes[i]:
                routes_on_ids[j].append(i)
        change_nodes = []
        for i in range(max_id + 1):
            change_nodes.append(Node(i, -1))
            for r in routes_on_ids[i]:
                nodes[i][r].addNeighbor(change_nodes[i], 12)
                change_nodes[i].addNeighbor(nodes[i][r], 0)
        result = findShortestPath(nodes, start, end)
        print result

#import cProfile as profile
#profile.run("main();")
main()
