#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[])
{
    vector<int> vec;
    srand(time(0));
    for(int i = 0; i < 10000; ++i)
    {
        vec.emplace_back(rand() % 1000);
    }

    //统计出现次数最小的前三个数字
    int k = 3;
    unordered_map<int, int> map;
    for(auto key : vec)
    {
        map[key]++;
    }

    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> maxHeap(
        [](Type& a, Type& b) -> bool {
            return a.second < b.second;
        }
    );

    auto it = map.begin();
    for(int i = 0; i < k; ++i, ++it)
    {
        maxHeap.push(*it);
    }

    for(; it!= map.end(); ++it)
    {
        if(maxHeap.top().second > it->second)
        {
            maxHeap.pop();
            maxHeap.push(*it);
        }
    }

    while(!maxHeap.empty())
    {
        cout << "key: " << maxHeap.top().first << " count: " << maxHeap.top().second << endl;
        maxHeap.pop();
    }

    //统计出现次数最大的前三个数字
    priority_queue<Type, vector<Type>, Comp> minHeap(
        [](Type& a, Type& b) -> bool {
            return a.second > b.second;
        }
    );

    it = map.begin();
    for(int i = 0; i < k; ++i, ++it)
    {
        minHeap.push(*it);
    }

    for(; it != map.end(); ++it)
    {
        if(minHeap.top().second < it->second)
        {
            minHeap.pop();
            minHeap.push(*it);
        }
    }

    cout << "------------------------------------------" << endl;       
    while(!minHeap.empty())
    {
        cout << "key: " << minHeap.top().first << " count: " << minHeap.top().second << endl;
        minHeap.pop();
    }

    return 0;
}

