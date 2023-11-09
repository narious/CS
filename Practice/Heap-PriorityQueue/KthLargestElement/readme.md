# [Kth Largest Element in Array](https://leetcode.com/problems/kth-largest-element-in-an-array/description/?envType=study-plan-v2&envId=leetcode-75)

Straight forward priority heap
#### Time/Space complexity
- Time complexity: O(Nlog(K)) : K elemements
- Space complexity: O(k)
### Score
- 100ms (53.47%)
- 57.60mb (63.29%) 
```C++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(begin(nums), end(nums));
        for (int i = 0; i < k - 1; i++)
        {
            if (pq.empty()) {return -1;}
            pq.pop();
        }
        return pq.top();
    }
};

```