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


// Below is a solution using template

#include <iostream>
#include <cassert>
#include <unordered_map>
#include <list>
#include <memory>

template <typename KeyType, typename ValueType>
class LRU {
private:

  struct ListItem {
    ListItem(KeyType key, ValueType value) : m_key(key), m_value(value){}

    KeyType m_key;
    ValueType m_value;
  };
  typedef std::shared_ptr<ListItem> ListItemPtr;
  typedef std::list<ListItemPtr> LruList;
  typedef typename std::list<ListItemPtr>::iterator LruListPos;
  typedef std::unordered_map<KeyType, LruListPos> LruMapper;

public:
  LRU(std::size_t capacity) : m_capacity(capacity) {
    SetDefaultValue(ValueType());
  }

  void SetDefaultValue(ValueType val) {
    m_default_value = val;
  }
  void SetCapacity(std::size_t capacity) {
    m_capacity = capacity;
  }
  ValueType Get(KeyType key) {
    if (m_mapper.count(key) == 0) {
      return m_default_value;
    } else {
      // copy and swap
      LruListPos pos = m_mapper[key];
      const ListItemPtr & cur_item_ptr = *pos;
      m_list.push_front(cur_item_ptr);
      m_mapper[key] = m_list.begin();

      // erase
      m_list.erase(pos);

      return m_list.front()->m_value;
    }
  }

  void Set(KeyType key, ValueType value) {
    if (m_mapper.count(key) != 0) {
      ValueType cc = Get(key);
      m_list.front()->m_value = value;
    } else {
      if (m_list.size() == m_capacity) {
        KeyType delete_key = m_list.back()->m_key;
        m_list.pop_back();
        m_mapper.erase(delete_key);
      }

      m_list.push_front(std::make_shared<ListItem>(key,value));
      m_mapper[key] = m_list.begin();
    }
  }
private:
  ValueType m_default_value;
  std::size_t m_capacity;
  LruList m_list;
  LruMapper m_mapper;
};

class LRUCache {
public:
  LRUCache(int capacity) : m_cache(LRU<int,int>(capacity)) {
    m_cache.SetDefaultValue(-1);
  }

  int get(int key) {
    return m_cache.Get(key);
  }

  void put(int key, int value) {
    m_cache.Set(key,value);
  }
private:
  LRU<int,int> m_cache;
};
