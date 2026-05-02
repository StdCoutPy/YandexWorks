import sys

# Увеличиваем лимит рекурсии для глубоких деревьев
sys.setrecursionlimit(2000)

def solve():
    try:
        line1 = sys.stdin.readline()
        if not line1: return
        n = int(line1.strip())
        line2 = sys.stdin.readline()
        if not line2: return
        w = list(map(int, line2.split()))
    except ValueError:
        return

    # Префиксные суммы для быстрого вычисления суммы весов на отрезке
    pref = [0] * (n + 1)
    for i in range(n):
        pref[i+1] = pref[i] + w[i]

    def get_sum(i, j):
        return pref[j+1] - pref[i]

    # dp[i][j] - минимальная стоимость
    dp = [[0] * n for _ in range(n)]
    # roots[i][j] - список всех корней, дающих минимум
    roots = [[[] for _ in range(n)] for _ in range(n)]

    for length in range(1, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if length == 1:
                dp[i][j] = w[i]
                roots[i][j] = [i]
                continue
            
            sum_w = get_sum(i, j)
            min_val = float('inf')
            
            for r in range(i, j + 1):
                left = dp[i][r-1] if r > i else 0
                right = dp[r+1][j] if r < j else 0
                current = sum_w + left + right
                
                if current < min_val:
                    min_val = current
                    roots[i][j] = [r]
                elif current == min_val:
                    roots[i][j].append(r)
            dp[i][j] = min_val

    results = []

    # Рекурсивная генерация всех описаний деревьев
    def generate_trees(i, j):
        if i > j:
            return [[]]
        
        res = []
        for r in roots[i][j]:
            left_trees = generate_trees(i, r - 1)
            right_trees = generate_trees(r + 1, j)
            for lt in left_trees:
                for rt in right_trees:
                    # Описание: корень + левое поддерево + правое поддерево
                    res.append([r + 1] + lt + rt)
        return res

    all_trees = generate_trees(0, n - 1)
    
    print(len(all_trees))
    for tree in all_trees:
        print(*(tree))

solve()
