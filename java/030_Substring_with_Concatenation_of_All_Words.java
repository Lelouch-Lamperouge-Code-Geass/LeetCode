// travel all the words combinations to maintain a window
// there are wl(word len) times travel
// each time, n/wl words, mostly 2 times travel for each word
// one left side of the window, the other right side of the window
// so, time complexity O(wl * 2 * N/wl) = O(2N)
    
public class Solution {
    public List<Integer> findSubstring(String s, String[] words) {
       List<Integer> reval = new ArrayList<Integer>();
        if (words == null || words.length == 0) return reval;
        final Integer word_length = words[0].length();
        HashMap<String, Integer> mapper = new HashMap<String, Integer>();
        for (String word : words) {
            if (mapper. containsKey(word)) {
                mapper.put(word, mapper.get(word) + 1);
            } else {
                mapper.put(word, 1);
            }
        }
        
        for (Integer i = 0, s_length = s.length(); i < word_length; ++i) {
            Integer start = i, pos = i, count = words.length;
            while (pos + word_length <= s_length) {
                String cur_word = s.substring(pos, pos + word_length);
                if (mapper.get(cur_word) != null && mapper.get(cur_word) != 0) { // need this word
                    mapper.put(cur_word, mapper.get(cur_word) - 1);
                    -- count;
                    if (count == 0) { // add start to return value, and remove the first word
                        reval.add(start);
                        String temp_word = s.substring(start, start + word_length);
                        mapper.put(temp_word, mapper.get(temp_word) + 1);
                        ++ count;
                        start += word_length;
                    }
                    pos += word_length;
                } else {
                    if (mapper.get(cur_word) == null) { // mismatch, discard all words in this window
                        while (start < pos) {
                            String temp_word = s.substring(start, start + word_length);
                            mapper.put(temp_word, mapper.get(temp_word) + 1);
                            ++ count;
                            start += word_length;
                        }
                        pos += word_length;
                        start = pos;
                    } else { // mapper.get(cur_word) == 0, means we have more cur_word than we need
                         while (start < pos && ! s.substring(start, start + word_length).equals(cur_word)) {
                            String temp_word = s.substring(start, start + word_length);
                            mapper.put(temp_word, mapper.get(temp_word) + 1);
                            ++ count;
                            start += word_length;
                         };
                         
                         String temp_word = s.substring(start, start + word_length);
                         mapper.put(temp_word, mapper.get(temp_word) + 1);
                         ++ count;
                         start += word_length;
                         
                    }
                }
            }
            
            // Importan! Reset the map count
            while (start < pos ) {
                String temp_word = s.substring(start, start + word_length);
                mapper.put(temp_word, mapper.get(temp_word) + 1);
                ++ count;
                start += word_length;
            }
        }
        return reval;
    }
}
