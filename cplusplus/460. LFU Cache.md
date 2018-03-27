Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

  
* get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
  
* put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

##### Follow up:

Could you do both operations in O(1) time complexity?
  
# Solution
  
```cpp
class LFUCache {
private:

    typedef std::list<int>::iterator FreqListIter;
    struct Entry {   
        Entry(int key, int value, int freq, FreqListIter iter) 
            : m_key(key), m_value(value), m_freq(freq), m_freq_list_iter(iter) {
            
        }
        int m_key;
        int m_value;  
        int m_freq;
        FreqListIter m_freq_list_iter;
    };
    
    std::unordered_map<int, Entry> m_key_to_entry;
    std::unordered_map<int, std::list<int>> m_freq_to_key_list;
    
    // If key exists, remove it
    void removeKey(int key) {
        if (m_key_to_entry.count(key) != 0) {
            Entry entry = m_key_to_entry.at(key);
            m_key_to_entry.erase(key);
            m_freq_to_key_list[entry.m_freq].erase(entry.m_freq_list_iter);
            -- m_entry_count;
            while (m_freq_to_key_list.count(m_min_freq) != 0 && m_freq_to_key_list[m_min_freq].empty()) {
				m_freq_to_key_list.erase(m_min_freq);
                ++ m_min_freq;
            }
        }
    }
    
    // If key exists already, delete exist entry first before adding new entry.
    void addEntry(int key, int value, int freq) {
        if (m_key_to_entry.count(key) != 0) {
            removeKey(key);
        }
        
        m_freq_to_key_list[freq].push_back(key);
        m_key_to_entry.insert(std::make_pair(key, Entry(key, value, freq, -- m_freq_to_key_list[freq].end())));
        ++ m_entry_count;
        if (freq < m_min_freq) {
            m_min_freq = freq;
        }
    }
    
    void removeLfuEntry() {
        int key = m_freq_to_key_list[m_min_freq].front();
        removeKey(key);
    }
    
    int m_min_freq;
    int m_entry_count;
    int m_capacity;
public:
    LFUCache(int capacity) : m_min_freq(0), m_entry_count(0), m_capacity(capacity) {
        
    }
    
    int get(int key) {
        int reval(-1);
        if (m_key_to_entry.count(key) != 0) {
            Entry entry = m_key_to_entry.at(key);
            reval = entry.m_value;
            removeKey(key);
            addEntry(key, entry.m_value, entry.m_freq + 1);
        }
        return reval;
    }
    
    void put(int key, int value) {
        if (m_key_to_entry.count(key) != 0) {
            addEntry(key, value, m_key_to_entry.at(key).m_freq + 1);
        } else {
            if (m_entry_count == m_capacity) {
                removeLfuEntry();
            }

            if (m_entry_count < m_capacity) {
                addEntry(key, value, 0);
            }
        }
    }
};
```
