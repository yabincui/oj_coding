
MAX_ROW = 4
MAX_COL = 4
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

def dfs(row, col, mask):
    global dr, dc, MAX_ROW, MAX_COL
    if row == MAX_ROW - 1 and col == MAX_COL - 1:
        return 1
    result = 0
    for i in range(len(dr)):
        nr = row + dr[i]
        nc = col + dc[i]
        if nr < 0 or nr >= MAX_ROW or nc < 0 or nc >= MAX_COL:
            continue
        bit = nr * MAX_COL + nc
        if (mask & (1 << bit)) != 0:
            continue
        result += dfs(nr, nc, mask | (1 << bit))
    return result

def main():
    # try dfs solution
    result = dfs(0, 0, 1)
    print result

if __name__ == '__main__':
    main()
