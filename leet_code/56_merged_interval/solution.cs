public class Solution {
    public int[][] Merge(int[][] intervals) {
        Array.Sort(intervals, (int[] a, int[] b) => a[0] - b[0]);
    
        List<int[]> result = new();
        for (int i = 0; i < intervals.Length; i++)
        {
            int l = intervals[i][0], r = intervals[i][1];
            for (int j = i + 1; j < intervals.Length; j++)
            {
                var (a, b) = (intervals[j][0], intervals[j][1]);
                if (l <= a && a <= r) {
                    // can be merged
                    if (b > r) r = b;
                } else break;
                i = j;
           }
            result.Add(new int[2]{l, r});
        }

        return result.ToArray();
    }
}
