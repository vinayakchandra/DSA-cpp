#include <iostream>
#include <vector>

using namespace std;

static bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

//TC: O(NlogN), sp: O(N)
int maxMeetings(int start[], int end[], int n) {
    vector<pair<int, int> > v;

    //making array where each element is of (start, end)
    for (int i = 0; i < n; i++) {
        pair<int, int> p = make_pair(start[i], end[i]);
        v.push_back(p);
    }
    //sorting in ascending order
    sort(v.begin(), v.end(), cmp);
    int count = 1; // pehli meeting consider karli
    int ansEnd = v[0].second;
    for (int i = 1; i < n; i++) {
        if (v[i].first > ansEnd) {
            count++;
            ansEnd = v[i].second;
        }
    }
    return count;
}

int main() {
    return 0;
}