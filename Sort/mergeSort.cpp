#include<iostream>
#include<vector>

#define ll long long

using namespace std;

void merge(vector<int>& vec, int left, int mid, int right) {
    vector<int> leftVec(vec.begin() + left, vec.begin() + mid + 1);
    vector<int> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);
    leftVec.push_back(INT_MAX);
    rightVec.push_back(INT_MAX);
    int index1 = 0, index2 = 0;
    for(int i = left; i <= right; i++) {
        if(leftVec[index1] < rightVec[index2]) {
            vec[i] = leftVec[index1];
            index1++;
        } else {
            vec[i] = rightVec[index2];
            index2++;
        }
    }
}

void mergeSort(vector<int>& vec, int left, int right) {
    if(left >= right) return;
    int mid = (right + left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

int main() {
    vector<int> arr{3, 6, 2, 7, 35, 753, 1, 2, 33, 34};
    mergeSort(arr, 0, arr.size() - 1);
    for(auto num: arr) {
        cout << num << ", ";
    }
    cout << endl;
    return 0;
}