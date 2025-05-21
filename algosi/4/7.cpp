#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, K, T;
    cout << "N: ";
    cin >> N;
    cout << "K: ";
    cin >> K;
    cout << "T: ";
    cin >> T;

    vector<int> orders(N);
    for (int i = 0; i < N; i++) {
        cin >> orders[i];
    }

    // по убыванию дальности
    sort(orders.rbegin(), orders.rend());

    vector<int> couriers;
    
    for (int i = 0; i < N; ++i) {
        bool assigned = false;

        for (int j = 0; j < couriers.size(); j++) {
            if (couriers[j] + orders[i] <= T) {
                couriers[j] += orders[i];
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            couriers.push_back(orders[i]);
        }
    }

    cout << couriers.size() << endl;

    return 0;
}