#include <iostream>
#include <vector>

using namespace std;

/* There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique

 

Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
 

Constraints:

gas.length == n
cost.length == n
1 <= n <= 104
0 <= gas[i], cost[i] <= 104 */

// The premise that a circuit can be completed is that SUM(gas[i] - cost[i]) has to be greater than 0. 

// Proof: We can define a variable Remain[i] such that it represents how much gas left when reaches i. 
// Remain[i] = Remain[i - 1] - cost[i - 1] + gas[i] -- (1)
// Remain[i] - cost[i] = Remain[i - 1] - cost[i - 1] + gas[i] - cost[i] -- (2)
// To reach every point of i the left-hand side of (2) has to be invariant true.

// Also, we can derive Remain[start] - cost[start] = gas[start] - cost[start] -- (3)
// So, to successfully reach point <start + 1> we will have:
// Remain[start + 1] - cost[start + 1] = gas[start] - cost[start] + gas[start + 1] - cost[start + 1] -- (4)
// So on and so forth for Remain[start + N] - cost[start + N] it will be the summumation of gas[i] - cost[i].
// Thus iff Remain[start + N] - cost[start + N] > 0 then we can get summumation of gas[i] - cost[i] has to 
// be greater than 0.

// The question would be where should be (and how to calculate) the starting point?
// We can examine every point where remain gas < 0. Suppose this point is K1, then It's not reachable from 
// 0 ~ K1 - 1 and we need to check K1 is the possible starting point. If K1 ~ K2 < 0 then it means K2 is 
// not reachable from K1 and we need to start from K2. By this way we can check every possible starting point
// without missing one. Suppose there is K3 can be starting point where K1 < K3 < K2. If K1 ~ K3 < 0 then
// K3 is not reachable from K1 then a possible starting point would be K3 which will be covered by the algorithm,
// so K3 is only not able to reach K2 but K3 can be reachable from K1. Then in this case K3 cannot be starting
// point. Because Remain[K3] should be 0 if K3 is starting point, which is impossible to become a starting point.
// And in this case, K1 cannot be starting point either because it cannot reach to K2. So K2 is the only
// candidate of starting point. 

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = 0;
        int sum = 0;
        int tank = 0;
        
        for (int i = 0; i < gas.size(); i++) {
            if (tank < 0) {
                tank = 0; // this inidicates a starting point.
                start = i;
            }
            
            int curr = gas[i] - cost[i];
            sum += curr;
            tank += curr;
        }
        
        return sum >= 0 ? start : -1;
    }
};