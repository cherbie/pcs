public class Twitter
{
    public Twitter()
    {
        m_followers = new Dictionary<int, ISet<int>>();
        m_tweets = new List<Tuple<int, int>>();
    }

    public void PostTweet(int userId, int tweetId)
    {
        m_tweets.Add(makeTweetPair(userId, tweetId));
    }

    public IList<int> GetNewsFeed(int userId)
    {
        ISet<int> userFollowers;
        m_followers.TryGetValue(userId, out userFollowers);

        var newsFeed = (from tweet in m_tweets
                        where (userFollowers != null && userFollowers.Contains(tweet.Item2))
                                           || (tweet.Item2 == userId)
                        select tweet).Reverse().Take(10).Select((tweet) => tweet.Item1).ToList();
        return newsFeed;
    }

    public void Follow(int followerId, int followeeId)
    {
        ISet<int> userFollowers;
        m_followers.TryGetValue(followerId, out userFollowers);
        if (userFollowers == null)
        {
            userFollowers = new HashSet<int>();
        }
        userFollowers.Add(followeeId);
        m_followers[followerId] = userFollowers;
    }

    public void Unfollow(int followerId, int followeeId)
    {
        ISet<int> userFollowers;
        if (!m_followers.TryGetValue(followerId, out userFollowers))
            return;

        if (userFollowers != null)
        {
            userFollowers.Remove(followeeId);
            m_followers[followerId] = userFollowers;
        }
    }

    private Tuple<int, int> makeTweetPair(int userId, int tweetId)
    {
        return Tuple.Create(tweetId, userId);
    }

    private IDictionary<int /*userId*/, ISet<int /*userId*/>> m_followers;
    private IList<Tuple<int /*tweetId*/, int/*userId*/>> m_tweets;
}
