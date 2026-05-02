import sys
import random

def solve():
    # Читаем все числа и преобразуем в список
    data = sys.stdin.read().split()
    if not data: return
    a = [int(x) for x in data]
    n = len(a)
    
    # Храним {сумма: кортеж_индексов}
    sums = {}
    
    # Чтобы ускорить процесс, будем брать случайные подмножества 
    # фиксированного размера (например, 20 элементов из 40)
    # Этого более чем достаточно для нахождения коллизии
    indices_pool = list(range(n))
    
    while True:
        # random.sample работает быстрее, чем ручной цикл по 40 элементам
        sample_idx = random.sample(indices_pool, 20)
        current_sum = sum(a[i] for i in sample_idx)
        
        if current_sum in sums:
            prev_indices = sums[current_sum]
            
            # Превращаем в множества для поиска пересечений
            s1 = set(sample_idx)
            s2 = set(prev_indices)
            
            # Если наборы идентичны (маловероятно), продолжаем
            if s1 == s2: continue
            
            # Убираем общие индексы
            common = s1 & s2
            res1 = [i + 1 for i in s1 if i not in common]
            res2 = [i + 1 for i in s2 if i not in common]
            
            # Вывод по формату
            print(len(res1))
            print(*(res1))
            print(len(res2))
            print(*(res2))
            return
        
        sums[current_sum] = tuple(sample_idx)

if __name__ == '__main__':
    solve()
