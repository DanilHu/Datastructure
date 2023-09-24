#include <algorithm>
#include<iostream>
#include<memory>
#include <vector>

using namespace std;


int main()
{
	// auto_ptr<int> pt(auto_ptr<int> (new int(3)));
	vector<unique_ptr<int>> vec;	
	unique_ptr<int> p1(new int(2));
	unique_ptr<int> p2(std::move(p1));
	vec.push_back(std::move(p2));
	cout << vec[0].get() << endl;
	// 两个裸指针同时对一个unique_ptr赋值就会出现double free的问题
	return 0;
}
