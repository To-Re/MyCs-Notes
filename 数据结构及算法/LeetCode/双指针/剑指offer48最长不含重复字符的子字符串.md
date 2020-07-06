```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool book[256] = {0};
        int ans = 0, n = s.size();
        for(int i = 0, j = 0; i < n; ++i) {
            while(book[s[i]]) book[s[j++]] = false;
            book[s[i]] = true;
            ans = max(ans, i-j+1);
        }
        return ans;
    }
};
```

