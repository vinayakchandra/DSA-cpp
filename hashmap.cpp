#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

void basicOps() {
    //creation
    unordered_map<string, int> m;
    //insertion
    //1
    pair<string, int> p = make_pair("vinu", 3);
    m.insert(p);
    //2
    pair<string, int> pair2("vinayak", 2);
    m.insert(pair2);
    //3
    m["mera"] = 1;
    m["mera"] = 5; //update the values of key: mera to 5

    //search
    cout << m["mera"] << endl;
    cout << m.at("mera") << endl;

    cout << m.at("unknown") << endl;
    cout << m["unknown"] << endl;

    //size
    cout << m.size() << endl;

    //to check presence
    cout << m.count("vinu") << endl;

    //erase
    m.erase("vinu");
    cout << m.size() << endl;

    //traverse
    for (auto i: m) {
        cout << i.first << " " << i.second << endl; //first=key, second = value
    }
    //iterator
    unordered_map<string, int>::iterator it = m.begin();
    while (it != m.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }
}

int maximumFrequency(vector<int> &arr, int n) {
    unordered_map<int, int> count;
    int maxFreq = 0;
    int maxAns = 0;

    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
        maxFreq = max(maxFreq, count[arr[i]]);
    }
//    int maxi = INT_MIN;
//    int ans = -1;
//    for (auto i: count) {
//        if (i.second > maxi) {
//            maxi = i.second;
//            ans = i.first;
//        }
//    }

    for (auto i: arr) {
        if(maxFreq == count[arr[i]]){
            maxAns=arr[i];
            break;
        }
    }
    return maxAns;
}
