class SnakeGame {
private:
  /** Initialize your data structure here.
      @param width - screen width
      @param height - screen height
      @param food - A list of food positions
      E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. 
  */
  int m_screen_width;
  int m_screen_height;
  int m_food_index;
  vector<pair<int, int>> m_food;
  set<pair<int, int>> m_hist;
  deque<pair<int, int>> m_snake_cells;
public:
  SnakeGame(int width, int height, vector<pair<int, int>> food) {
    m_food = food;
    m_screen_width = width;
    m_screen_height = height;
    m_food_index = 0;
    m_snake_cells.push_back(make_pair(0, 0));
  }

  /** Moves the snake.
      @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
      @return The game's score after the move. Return -1 if game over.
      Game over when snake crosses the screen boundary or bites its body. 
  */
  int move(string direction) {
    int row_of_snake_head = m_snake_cells.front().first, col_of_snake_head = m_snake_cells.front().second;
    pair<int, int> snake_tail = m_snake_cells.back();
    m_snake_cells.pop_back();
    m_hist.erase(snake_tail);

    if (direction == "U") {
      row_of_snake_head--;
    } else if (direction == "D") {
      row_of_snake_head++;
    } else if (direction == "L") {
      col_of_snake_head--;
    } else if (direction == "R") {
      col_of_snake_head++;
    }

    // Right now [row_of_snake_head,col_of_snake_head] is the cell the snake head will touch 
    if (row_of_snake_head < 0
        || col_of_snake_head < 0
        || col_of_snake_head >= m_screen_width
        || row_of_snake_head >= m_screen_height
        || m_m_hist.count(make_pair(row_of_snake_head, col_of_snake_head))) {
      return -1;
    }

    m_hist.insert(make_pair(row_of_snake_head, col_of_snake_head));
    m_snake_cells.push_front(make_pair(row_of_snake_head, col_of_snake_head));

    if (pos >= food.size()) { // Eat all food
      return m_snake_cells.size() - 1;
    }

    if (row_of_snake_head == food[m_food_index].first
        && col_of_snake_head == food[m_food_index].second) {
      // Get a food, put the deleted tail node back
      ++ m_food_index;
      m_snake_cells.push_back(snake_tail);
      m_hist.insert(snake_tail);
    }

    return m_snake_cells.size() - 1;
  }
};
