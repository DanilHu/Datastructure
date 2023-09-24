#include<iostream>
#include<vector>
using namespace std;

class BitMap {
private:
  static constexpr int BLOCK_SIZE  = 8;
  vector<char> m_map;
  int m_size;

public:
  explicit BitMap(int mapSize): m_size(mapSize) {
    m_map.resize(m_size);
  }

  void set(int index) {
    int blockIdx = index / BLOCK_SIZE;
    int blockOffset = index % BLOCK_SIZE;
    m_map[blockIdx] |= (0x1 << blockOffset);
  }

  void reset(int index) {
    int blockIdx = index / BLOCK_SIZE;
    int blockOffset = index % BLOCK_SIZE;
    m_map[blockIdx] &= ~(0x1 << blockOffset);
  }

  bool test(int index) {
    int blockIdx = index / BLOCK_SIZE;
    int blockOffset = index % BLOCK_SIZE;
    return (m_map[blockIdx] >> (blockOffset)) != 0;
  }
};

int main() {
  BitMap bitMap(10000);
  bitMap.set(500);
  cout << bitMap.test(500) << endl;
  cout << bitMap.test(1000) << endl;
  return 0;
}
