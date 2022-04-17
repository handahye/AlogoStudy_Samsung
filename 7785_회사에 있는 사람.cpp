#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include<sstream>

using namespace std;
bool cmp(string a, string b) {
    return a > b;
}
int main() {
    int n;
    cin >> n;
    set<string> s;
    for (int i = 0; i < n; i++) {
        string str;
        string name, status;
        cin >> name >> status;
        if (status == "enter") {
            s.insert(name);
        }
        else if (status == "leave") {
            if (s.count(name) == 1) {
                s.erase(name);
            }
        }

    }
    vector<string> ans;
    for (auto iter : s) {
        ans.push_back(iter);
    }
    sort(ans.begin(), ans.end(), cmp);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}