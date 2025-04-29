#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int start, end;
};

bool compareByEnd(const Task& a, const Task& b) {
    return a.end < b.end;
}

int main() {
    int n;
    cin >> n;
    vector<Task> tasks(n);
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].start >> tasks[i].end;
    }

    sort(tasks.begin(), tasks.end(), compareByEnd);

    int count = 0;
    int last_end = -1;
    for (const auto& task : tasks) {
        if (task.start >= last_end) {
            count++;
            last_end = task.end;
        }
    }

    cout << count << endl;
    return 0;
}