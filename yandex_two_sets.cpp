#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    int n = 40;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> a[i])) return;
    }

    // Храним {сумма: маска_подмножества}
    // Маска — это 64-битное число, где i-й бит означает включение i-го элемента
    unordered_map<ll, ll> sums;
    
    // Инициализация генератора случайных чисел
    mt19937_64 rng(1337); 
    
    while (true) {
        ll mask = 0;
        ll current_sum = 0;
        
        // Генерируем случайную маску для 40 элементов
        // Каждое подмножество равновероятно
        for (int i = 0; i < n; ++i) {
            if (rng() % 2) {
                mask |= (1LL << i);
                current_sum += a[i];
            }
        }

        if (mask == 0) continue;

        if (sums.count(current_sum)) {
            ll prev_mask = sums[current_sum];
            if (prev_mask == mask) continue;

            // Убираем общие элементы (пересечение подмножеств)
            ll common = prev_mask & mask;
            ll final_mask1 = prev_mask ^ common;
            ll final_mask2 = mask ^ common;

            // Если после удаления общих элементов одно из множеств стало пустым
            if (final_mask1 == 0 || final_mask2 == 0) continue;

            // Вывод первого множества
            vector<int> res1, res2;
            for (int i = 0; i < n; ++i) {
                if ((final_mask1 >> i) & 1) res1.push_back(i + 1);
                if ((final_mask2 >> i) & 1) res2.push_back(i + 1);
            }

            cout << res1.size() << "\n";
            for (int i = 0; i < res1.size(); ++i) {
                cout << res1[i] << (i == res1.size() - 1 ? "" : " ");
            }
            cout << "\n";

            // Вывод второго множества
            cout << res2.size() << "\n";
            for (int i = 0; i < res2.size(); ++i) {
                cout << res2[i] << (i == res2.size() - 1 ? "" : " ");
            }
            cout << "\n";

            return;
        }

        sums[current_sum] = mask;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
