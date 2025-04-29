#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int l, r;
    long long sum;
    int mn, mx;
    int even, odd;
    Node *left, *right;
    Node(int l, int r): l(l), r(r), sum(0), mn(INT_MAX), mx(INT_MIN), even(0), odd(0), left(nullptr), right(nullptr) {}
};

vector<int> arr;

Node* build(int l, int r) {
    Node* node = new Node(l, r);
    if (l == r) {
        node->sum = arr[l];
        node->mn = arr[l];
        node->mx = arr[l];
        node->even = (arr[l] % 2 == 0);
        node->odd = (arr[l] % 2 != 0);
        return node;
    }
    int m = (l + r) / 2;
    node->left = build(l, m);
    node->right = build(m+1, r);
    node->sum = node->left->sum + node->right->sum;
    node->mn = min(node->left->mn, node->right->mn);
    node->mx = max(node->left->mx, node->right->mx);
    node->even = node->left->even + node->right->even;
    node->odd = node->left->odd + node->right->odd;
    return node;
}

int query_sum(Node* node, int l, int r) {
    if (node->r < l || node->l > r) return 0;
    if (l <= node->l && node->r <= r) return node->sum;
    return query_sum(node->left, l, r) + query_sum(node->right, l, r);
}

int query_min(Node* node, int l, int r) {
    if (node->r < l || node->l > r) return INT_MAX;
    if (l <= node->l && node->r <= r) return node->mn;
    return min(query_min(node->left, l, r), query_min(node->right, l, r));
}

int query_max(Node* node, int l, int r) {
    if (node->r < l || node->l > r) return INT_MIN;
    if (l <= node->l && node->r <= r) return node->mx;
    return max(query_max(node->left, l, r), query_max(node->right, l, r));
}

pair<int, int> query_even_odd(Node* node, int l, int r) {
    if (node->r < l || node->l > r) return {0, 0};
    if (l <= node->l && node->r <= r) return {node->even, node->odd};
    auto le = query_even_odd(node->left, l, r);
    auto ri = query_even_odd(node->right, l, r);
    return {le.first + ri.first, le.second + ri.second};
}

int main() {
    int n;
    cout << "n: ";
    cin >> n;
    arr.resize(n);
    cout << "elements:" << endl;
    for (int i = 0; i < n; ++i) cin >> arr[i];

    Node* root = build(0, n-1);

    int l, r;
    cout << "l, r: ";
    cin >> l >> r;
    if (l < 0 || r >= n || l > r) {
        cout << "Incorrect limits!" << endl;
        return;
    }
    cout << "Sum: " << query_sum(root, l, r) << endl;
    cout << "Min: " << query_min(root, l, r) << endl;
    cout << "Max: " << query_max(root, l, r) << endl;
    auto res = query_even_odd(root, l, r);
    cout << "Even: " << res.first << ", Odd: " << res.second << endl;

    return 0;
}