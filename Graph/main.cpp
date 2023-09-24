// LeetCode: 399
// 1. Graph construct: unordered_map<string, edge> edge: vector<piar<string,
// double>>
// 2. Graph DFS: visit represents nodes that have passed
// 3. success: positive, unsuccess: negative
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

double dfs(unordered_map<string, vector<pair<string, double>>> &graph,
           unordered_set<string> &visit, string start, string end) {
  if (start == end)
    return 1.0;
  visit.emplace(start);
  for (auto &vec : graph[start]) {
    string next = vec.first;
    double value = vec.second;
    if (visit.count(next))
      continue;
    double res = value * dfs(graph, visit, next, end);
    if (res > 0.0)
      return res;
  }
  visit.erase(start);
  return -1.0;
}

double bfs(unordered_map<string, vector<pair<string, double>>> &graph,
           unordered_set<string> &visit, string start, string end) {
  if (start == end)
    return 1.0;
  visit.emplace(start);
  for (auto &vec : graph[start]) {
    string next = vec.first;
    double value = vec.second;
    if (visit.count(next))
      continue;
    double res = value * dfs(graph, visit, next, end);
    if (res > 0.0)
      return res;
  }
  visit.erase(start);
  return -1.0;
}

vector<double> calcEquation(vector<vector<string>> &equations,
                            vector<double> &values,
                            vector<vector<string>> &queries) {
  int n = equations.size(), m = queries.size();
  unordered_map<string, vector<pair<string, double>>> graph;
  for (int i = 0; i < n; i++) {
    string s1 = equations[i][0], s2 = equations[i][1];
    graph[s1].emplace_back(s2, values[i]);
    graph[s2].emplace_back(s1, 1.0 / values[i]);
  }
  vector<double> res(m, -1.0);
  unordered_set<string> visit;
  // lambda函数就是为了直接使用已经定义的东西，没必要让函数结构看起来那么复杂
  //  function<double(string, string)> dfs = [&](string start,
  //                                             string end) -> double {
  //    if (start == end)
  //      return 1.0;
  //    visit.emplace(start);
  //    for (auto &vec : graph[start]) {
  //      string next = vec.first;
  //      double value = vec.second;
  //      if (visit.count(next))
  //        continue;
  //      double res = value * dfs(next, end);
  //      if (res > 0.0)
  //        return res;
  //    }
  //    visit.erase(start);
  //    return -1.0;
  //  };
  for (int i = 0; i < m; i++) {
    string s1 = queries[i][0], s2 = queries[i][1];
    if (graph.count(s1) && graph.count(s2)) {
      visit.clear();
      res[i] = dfs(graph, visit, s1, s2);
    }
  }
  return res;
}

int main() { return 0; }
