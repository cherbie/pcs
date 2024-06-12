public class Solution {
    public int LongestPalindrome(string s) {
        if (s.Length < 2) return s.Length;
    
        int[] tally = new int[125];

        foreach (char c in s) {
            tally[(int)c] += 1;
        }

        int longest = 0;
        bool skipped = false;
        for (int i = 65; i < 125; i++) {
            int count = tally[i];
            if (count < 1) continue;
            if (count % 2 == 0) longest += count;  
            else {
                skipped = true;
                longest += count-1;
            }
        }

        return skipped ? longest + 1 : longest;
    }
}