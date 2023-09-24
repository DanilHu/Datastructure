#include "../utils/AutoBuf.h"
#include <cassert>
#include <deque>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

int main() {
    AutoBuf buf;
    deque<char> que;

    for(int k = 0; k < 1000; k++) {
        int len = rand() % 10000 + 1;
        string s;
        for(int j = 0; j < len; j++) {
            char c = j * 1000000007;
            que.push_back(j);
            s.push_back(j);
        }
        buf.Append(s.c_str(), s.length());
        assert(que.size() == buf.Size());
    }

    {
        auto iter = que.begin();
        struct iovec iov[1024];
        int ret = buf.GetIOVec(iov, 1024);
        for(int i = 0; i < ret; i++) {
            for(int j = 0; j < iov[i].iov_len; j++) {
                assert(((char*)iov[i].iov_base)[j] == *iter);
                iter++;
            }
        }
    }

    {
        size_t eraseSize = (rand() % que.size()) / 2;
        buf.Pop(eraseSize);
        for(size_t i = 0; i < eraseSize; i++) {
            que.pop_front();
        }
        assert(que.size() == buf.Size());

        auto iter = que.begin();
        struct iovec iov[1024];
        int ret = buf.GetIOVec(iov, 1024);
        for(int i = 0; i < ret; i++) {
            for(int j = 0; j < iov[i].iov_len; j++) {
                assert(((char*)iov[i].iov_base)[j] == *iter);
                iter++;
            }
        }
        assert(iter == que.end());
    }
    cout << "finish" << endl;
}