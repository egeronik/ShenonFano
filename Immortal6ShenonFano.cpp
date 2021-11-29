#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

struct node {
    int n=0;
    char c=0;
    node* left = NULL; //1
    node* right = NULL;//0
};


vector<pair<int, char>> countEntry(string s) {
    map<char, int> m;//Key, count
    vector<pair<int, char>> v;//Count, key

    for (int i = 0; i < s.length(); ++i) {
        m[s[i]]++;
    }
    for (auto& i : m) {
        v.push_back(std::make_pair(i.second, i.first));
    }
    sort(v.rbegin(), v.rend());
    return v;
}


node* makeSFTree(vector<pair<int, char>> v) {
    node* ans = new node;
    if (v.size() == 1) {
        ans->c = v[0].second;
        ans->n = v[0].first;
        return ans;
    }
    
    int right = 0, left = 0;
    for (int i = 0; i < v.size(); ++i) {
        right += v[i].first;
    }
    for (int i = 0; i < v.size(); ++i) {
        left += v[i].first;
        right -= v[i].first;
        if (left >= right) {
            vector<pair<int, char>> lv(v.begin(), v.begin()+i+1);
            vector<pair<int, char>> rv(v.begin()+i+1, v.end());
            node* l = makeSFTree(lv);
            node* r = makeSFTree(rv);
            ans->n = l->n + r->n;
            ans->left = l;
            ans->right = r;
            return ans;
        }
    }
    return NULL;

}

void traversal(node* myNode, int l) {
    int i;
    if (myNode) {
        traversal(myNode->right, l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << myNode->n << '|' << myNode->c << '\n';
        traversal(myNode->left, l + 1);
    }
}

map<char, string> mChSt;
map<string, char> mStCh;

void makeMap(node* N, string path) {
    if (N == NULL) return;
    if (N->left == NULL && N->right == NULL) {
        mChSt[N->c] = path;
        mStCh[path] = N->c;
    }
    else {
        makeMap(N->left, path + "0");
        makeMap(N->right, path + "1");
    }
}



string codeString(string s) {
    string ans = "";
    for (int i = 0; i < s.length(); ++i) {
        ans += mChSt[s[i]];
    }
    return ans;
}

string decodeString(string s) {
    string ans = "";
    string tmp = "";
    for (int i = 0; i < s.length(); ++i) {
        tmp += s[i];
        if (mStCh.find(tmp) != mStCh.end()) {
            ans += mStCh[tmp];
            tmp = "";
        }
    }
    return ans;
}

int main()
{
    string s = "aaaaaaaaaabbbbbbbbccccccdddddeeeefff";
    cin >> s;
    vector<pair<int, char>> st = countEntry(s);
    cout << "Char count table:\n";
    for (auto& i : st) {
        cout << i.first << ' ' << i.second << '\n';
    }
    node* tree = makeSFTree(st);
    cout << "Tree:\n";
    traversal(tree, 0);
    makeMap(tree, "");
    for (auto& i : mChSt) {
        cout << i.first << ' ' << i.second << '\n';
    }
    int n = 0;
    string endCode = codeString(s);
    cout << "Result: " << endCode << '\n';
    cout << "Decoded result: " << decodeString(endCode) << '\n';
    cout << "Uncoded size: " << s.length() * 8 << " bits\n";
    cout << "End size:     " << endCode.length() << " bits\n";




}