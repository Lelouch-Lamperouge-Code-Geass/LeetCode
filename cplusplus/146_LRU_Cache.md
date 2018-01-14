Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?
  
Example:
```
LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4  
```

# Solution

The problem can be solved with a hashtable that keeps track of the keys and its values in the double linked list. One interesting property about double linked list is that the node can remove itself without other reference. In addition, it takes constant time to add and remove nodes from the head or tail.

The the cache reaches its capacity, we need evict the least recently used item out. We need to pop the oldest item out of the list and also erase the corresponding entry in the HashMap. Therefore, we must store key in the list, while value can be storeed in the list or the HashMap.

##### Solution  one
```cpp
class LRUCache {
private:
    std::list<std::pair<int,int>> m_items;
    typedef std::list<std::pair<int,int>>::iterator ListPosition;
    std::unordered_map<int, ListPosition> m_mapper;
    int m_capacity;
public:
    LRUCache(int capacity) : m_capacity(capacity) {
        
    }
    
    int get(int key) {
        int reval(-1);
        if (m_mapper.count(key) > 0) {
            reval = m_mapper[key]->second;
            erase_item_by_key(key); // erase if exispt
            add_item(key, reval); // add to begin of LRU
        }
        
        return reval;
    }
    
    void put(int key, int value) {
        if (m_items.size() == m_capacity && m_mapper.count(key) == 0) {
            // reach capacity and this is a new item,
            // delete the least recently used item
            evict_lru_item();
        }
        erase_item_by_key(key);
        add_item(key, value);
    }
    
private:
    void erase_item_by_key(int key) {
        if (m_mapper.count(key) > 0) {
            ListPosition list_position = m_mapper[key];
            m_items.erase(list_position);
            m_mapper.erase(key);
        }
    }
    
    void add_item(int key, int value) {
        m_items.push_front(std::make_pair(key, value));
        m_mapper[key] = m_items.begin();
    }
    
    void evict_lru_item() {
        if (!m_items.empty()) {
            erase_item_by_key(m_items.back().first);
        }
    }
};
```

A different style.

```cpp
class LRUCache {
private:
    typedef std::list<pair<int, int>>::iterator ListPos;
    std::list<pair<int, int>> m_list;
    std::unordered_map<int, ListPos> m_mapper;
    int m_capacity;
    void acccessExistedItemByKey(int key) {
        if (m_mapper.count(key)) {
            ListPos list_pos = m_mapper[key];
            const int value = list_pos->second;
            m_list.erase(list_pos);
            m_list.push_front(make_pair(key,value));
            m_mapper[key] = m_list.begin();
        }
    }
public:
    LRUCache(int capacity) : m_capacity(capacity){
        
    }
    
    int get(int key) {
        if (!m_mapper.count(key)) {
            return -1;
        } else {
            acccessExistedItemByKey(key);
            return m_mapper[key]->second;
        }
    }
    
    void put(int key, int value) {
        if (m_mapper.count(key)) {
            acccessExistedItemByKey(key);
            m_mapper[key]->second = value;
        } else {
            if (m_list.size() == m_capacity) {
                int delete_key = m_list.back().first;
                m_list.pop_back();
                m_mapper.erase(delete_key);
            }
            m_list.push_front(make_pair(key, value));
            m_mapper[key] = m_list.begin();
        }
    }
};

 ```

##### Solution two : a more generic solution with template.

```cpp
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
```
