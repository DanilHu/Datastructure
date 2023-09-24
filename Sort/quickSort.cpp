#include<iostream>
#include<vector>

#define ll long long

using namespace std;

int partition(vector<int>& vec, int start, int end) {
    int pivotIdx = rand() % (end - start + 1) + start;
    int pivot = vec[pivotIdx];
    swap(vec[end], vec[pivotIdx]);
    int i = start - 1;
    for(int j = start; j <= end - 1; j++) {
        if(vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[end]);
    return i + 1;
}

void quickSort(vector<int>& vec, int start, int end) {
    if(start >= end) return;
    int mid = partition(vec, start, end);
    quickSort(vec, start, mid - 1);
    quickSort(vec, mid + 1, end);
}

int main() {
    vector<int> arr{1, 1, 5, 3, 2, 2, 8, 7, 1000, 945, 361};
    quickSort(arr, 0, arr.size() - 1);
    for(auto num: arr) {
        cout << num << ", ";
    }
    cout << endl;
    return 0;
}