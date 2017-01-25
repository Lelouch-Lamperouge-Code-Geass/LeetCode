std::size_t timestamp(0);

class Tweet {
public:
  Tweet(int id) : m_id(id), m_time(timestamp++) {}
  int m_id;
  std::size_t m_time;
};
typedef std::shared_ptr<Tweet> TweetPtr;

class User {
public:
  User(int user_id) : m_id(user_id) {
    followed.insert(user_id); // Follow self
  }
  void Follow(int user_id) {
    followed.insert(user_id);
  }
  void Unfollow(int user_id) {
    followed.erase(user_id);
  }
  void PostTweet(int tweet_id) {
    m_tweets.push_front(std::make_shared<Tweet>(tweet_id));
  }
  int m_id;
  std::unordered_set<int> followed;
  std::deque<TweetPtr> m_tweets;
};
typedef std::shared_ptr<User> UserPtr;

struct TweetSorting {
  bool operator () (TweetPtr & left, TweetPtr & right) {
    return left->m_time < right->m_time;
  }
};

class Twitter {
public:
  /** Initialize your data structure here. */
  Twitter() {

  }

  /** Compose a new tweet. */
  void postTweet(int userId, int tweetId) {
    if (m_users_mapper.count(userId) == 0) {
      m_users_mapper[userId] = std::make_shared<User>(userId);
    }
    m_users_mapper[userId]->PostTweet(tweetId);
  }

  /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
  vector<int> getNewsFeed(int userId) {
    if (m_users_mapper.count(userId) == 0) return vector<int>();
    std::priority_queue<TweetPtr,std::vector<TweetPtr>, TweetSorting> pq; // MaxHeap
    UserPtr cur_user = m_users_mapper[userId];
    for (int followed_id : cur_user->followed) {
      for (TweetPtr & tweet_ptr : m_users_mapper[followed_id]->m_tweets) {
        pq.push(tweet_ptr);
      }
    }
    vector<int> reval;
    for(int i=0;i<10 && !pq.empty();++i) {
      reval.push_back(pq.top()->m_id);
      pq.pop();
    }
    return reval;
  }

  /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
  void follow(int followerId, int followeeId) {
    if (m_users_mapper.count(followerId) == 0) {
      m_users_mapper[followerId] = std::make_shared<User>(followerId);
    }
    if (m_users_mapper.count(followeeId) == 0) {
      m_users_mapper[followeeId] = std::make_shared<User>(followeeId);
    }
    m_users_mapper[followerId]->Follow(followeeId);
  }

  /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
  void unfollow(int followerId, int followeeId) {
    if (m_users_mapper.count(followerId) == 0 || followerId == followeeId) {
      return;
    } else {
      m_users_mapper[followerId]->Unfollow(followeeId);
    }
  }
private:
  std::unordered_map<int,UserPtr> m_users_mapper;
};
