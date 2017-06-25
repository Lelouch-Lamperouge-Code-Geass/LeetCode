// Let's give a general implementaion of LFU.
// NOTICE that this solution doesn't meet the requirement
// "All options are O(1)"
// We need to optimize remove_LFU_item() in order to satisfy requirements. 
class LFUCache {
private:
  typedef std::list< std::pair<int, int> > PairList;
  typedef PairList::iterator PairListIter;
  typedef std::vector< PairList > ArrayList;
  ArrayList m_array_list;

  // <Key, <ArrayListIndex, ListIter> >
  std::unordered_map<int, std::pair<int, PairListIter> > m_mapper;
  int m_capacity;
  int m_count;

  // Time complexity O(n), n represents the frequency array size
  void remove_LFU_item() {
    for (std::size_t i = 0, arr_size = m_array_list.size(); i < arr_size; ++i) {
      if (!m_array_list[i].empty()) {
        PairListIter iter = m_array_list[i].begin();
        int key = (*iter).first;
        m_mapper.erase(key);
        m_array_list[i].erase(iter);
        -- m_count;
        break;
      }
    }
  }

  // Add new pair only if the key is not in the mapper
  void add_new_pair(int key, int value) {
    if (m_mapper.count(key) == 0) {
      if (m_array_list.empty()) m_array_list.push_back(PairList());
      m_array_list[0].push_back(std::make_pair(key,value));
      PairListIter iter = -- m_array_list[0].end();
      m_mapper[key] = std::make_pair(0, iter);
      ++ m_count;
    }
  }

  // Incrase the frequence of a key
  void increase_frequency(int key) {
    if (m_mapper.count(key) != 0) {
      PairListIter list_iter= m_mapper[key].second;
      int val = (*list_iter).second;
      int new_array_list_index =  m_mapper[key].first + 1;
      m_array_list[m_mapper[key].first].erase(list_iter);
      if (m_array_list.size() == new_array_list_index) {
        m_array_list.push_back(PairList());
      }

      m_array_list[new_array_list_index].push_back(std::make_pair(key,val));
      m_mapper[key].second = ( -- m_array_list[new_array_list_index].end() );
      m_mapper[key].first = new_array_list_index;
    }
  }
public:
  LFUCache(int capacity) : m_capacity(capacity), m_count(0) {

  }

  int get(int key) {
    int reval(-1);

    if (m_mapper.count(key) != 0) {
      increase_frequency(key);
      PairListIter iter = m_mapper[key].second;
      reval = (*iter).second;
    }

    return reval;
  }

  void put(int key, int value) {
    if (m_mapper.count(key) != 0) {
      increase_frequency(key);
      PairListIter iter = m_mapper[key].second;
      (*iter).second = value;
    } else {
      if (m_count == m_capacity) {
        remove_LFU_item();
      }

      if (m_count < m_capacity) {
        add_new_pair(key, value);
      }
    }
  }
};

// How to optimize the remove_LRU_item() ?
// We can use HashMap instead of ArrayList.
// And use min_m_min_frequency to track the list of min frequence items.
class LFUCache {
public:
  LFUCache(int capacity) : m_capacity(capacity), m_min_frequency(0), m_size(0) {

  }

  int get(int key) {
    if (m_key_to_list_position.count(key) == 0) return -1; // cache miss

    std::size_t frequency = m_key_to_value_freq[key].second;
    m_frequency_to_keys[frequency].erase(m_key_to_list_position[key]);

    std::size_t new_frequency = frequency + 1; // increase frequency of this key
    m_key_to_value_freq[key].second = new_frequency;
    m_frequency_to_keys[new_frequency].push_back(key);

    m_key_to_list_position[key] = --m_frequency_to_keys[new_frequency].end();

    if (m_frequency_to_keys[m_min_frequency].size() == 0) {
      ++ m_min_frequency;
    }

    return m_key_to_value_freq[key].first;
  }

  void put(int key, int value) {
    if (m_capacity == 0) return;

    if (m_key_to_value_freq.count(key) != 0) {
      get(key);
      m_key_to_value_freq[key].first = value;
    } else {
      if (m_size == m_capacity) {
        int delete_key = m_frequency_to_keys[m_min_frequency].front();
        erase(delete_key);
      }

      m_key_to_value_freq[key] = {value, 1};
      m_frequency_to_keys[1].push_back(key);
      m_key_to_list_position[key] = --m_frequency_to_keys[1].end();
      m_min_frequency = 1;
      ++ m_size;
    }
  }
  void erase(int key) {
    if (m_key_to_value_freq.count(key) != 0 ) {
      m_key_to_value_freq.erase(key);
      m_key_to_list_position.erase(key);
      m_frequency_to_keys[m_min_frequency].pop_front();
      -- m_size;
    }
  }
private:
  std::size_t m_capacity;
  std::size_t m_size;
  std::size_t m_min_frequency;
  unordered_map<int, pair<int, std::size_t> > m_key_to_value_freq; //key to {value,freq};
  unordered_map<std::size_t, list<int>>  m_frequency_to_keys;  //frequency to key list;
  unordered_map<int, list<int>::iterator> m_key_to_list_position; //key to list iterator;
};
