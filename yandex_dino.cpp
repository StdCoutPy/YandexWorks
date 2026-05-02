#include <iostream>
#include <vector>

using namespace std;

// Структура для припятствий 
struct Prepyatstvie {
    long long natchalo;
    long long konec;
    int stoimost;
};

int main() {
    // Для быстро работало
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int kolvo_p;
    if (!(cin >> kolvo_p)) return 0;

    vector<long long> v_coords(kolvo_p);
    for (int i = 0; i < kolvo_p; i++) cin >> v_coords[i];

    vector<int> v_types(kolvo_p);
    for (int i = 0; i < kolvo_p; i++) cin >> v_types[i];

    vector<Prepyatstvie> trassa;
    for (int i = 0; i < kolvo_p; i++) {
        long long dlinna = 0;
        int points = 0;
        
        // определяем каой  тип тут
        if (v_types[i] == 1) { dlinna = 1; points = 1; }
        else if (v_types[i] == 2) { dlinna = 2; points = 3; }
        else { dlinna = 4; points = 5; }

        long long current_end = v_coords[i] + dlinna;

        // тут проверка если трасса сломаная (пересечения всякие)
        if (!trassa.empty() && v_coords[i] <= trassa.back().konec) {
            cout << 0 << endl;
            return 0;
        }
        trassa.push_back({v_coords[i], current_end, points});
    }

    int kolvo_jumps;
    cin >> kolvo_jumps;
    vector<long long> j_start(kolvo_jumps);
    for (int i = 0; i < kolvo_jumps; i++) cin >> j_start[i];
    vector<long long> j_len(kolvo_jumps);
    for (int i = 0; i < kolvo_jumps; i++) cin >> j_len[i];

    long long final_score = 0;
    int p_ukazatel = 0;

    for (int j = 0; j < kolvo_jumps; j++) {
        long long start_faza = j_start[j];
        long long finish_faza = j_start[j] + j_len[j];

        // если дино не увидел припятствие сзади
        while (p_ukazatel < kolvo_p && trassa[p_ukazatel].konec <= start_faza) {
            final_score--;
            p_ukazatel++;
        }

        // чекаем все че попадает под прыжок
        while (p_ukazatel < kolvo_p && trassa[p_ukazatel].natchalo < finish_faza) {
            if (trassa[p_ukazatel].natchalo >= start_faza && trassa[p_ukazatel].konec <= finish_faza) {
                final_score += trassa[p_ukazatel].stoimost; //  УРАА!!
            } else {
                final_score--; // не долетел или зацепил
            }
            p_ukazatel++;
        }
    }

    // если остались припятствия впереди которые не прыгали
    final_score -= (kolvo_p - p_ukazatel);

    // итоговое чило не меньше нуля по правилам
    if (final_score < 0) final_score = 0;
    cout << final_score << endl;

    return 0;
}
