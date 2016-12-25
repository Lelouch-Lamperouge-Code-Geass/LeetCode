class LRUCache{
public:
  struct CacheItem {
    CacheItem(int k, int v):key(k),value(v){}
    int key;
    int value;
  };
  typedef std::list<CacheItem>::iterator ItemPos;
  struct CachePos {
    CachePos(int v, const ItemPos & p):value(v),pos(p) {}
    int value;
    ItemPos pos;
  };

  LRUCache(int capacity) : m_capacity(capacity) {

  }

  int get(int key) {
    if (m_mapper.find(key) == m_mapper.end() ) {
      return -1;
    } else {
      int value = m_mapper[key].value;
      touch(key,value);
      return value;
    }
  }

  void set(int key, int value) {
    touch(key,value);
  }
private:
  // delete if key exist in list, and reinsert it at the front of the list.
  void touch(int key,int value) {
    if (m_mapper.find(key)!=m_mapper.end()) {
      m_lru.erase(m_mapper[key].pos);
    }
    m_lru.push_front(CacheItem(key,value));
    m_mapper[key] = CachePos(value,m_lru.begin());
    if (m_lru.size() == m_capacity+1) {
      m_mapper.erase(m_lru.back().key);
      m_lru.pop_back();
    }
  }
  int m_capacity;
  std::list<CacheItem> m_lru;
  std::unordered_map<int,CachePos> m_mapper;
};
