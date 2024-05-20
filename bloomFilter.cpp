#include <iostream>
#include <vector>
#include "stringhash.h"
#include <string>

using namespace std;
/*

布隆过滤器（Bloom filter）是一种空间效率很高的概率型数据结构，用于测试一个元素是否是一个集合的成员。它具有以下特点和作用：

1. **快速查询**：布隆过滤器可以非常快速地进行查询操作，因为它只需要进行几个简单的位运算。

2. **节省空间**：相比于存储所有元素的集合，布隆过滤器可以显著减少所需的存储空间。

3. **概率性**：布隆过滤器可以给出一个元素是否在集合中的确定性答案，但存在一定的误判率。即，它可能会告诉你一个元素不在集合中（假阴性），或者错误地告诉你一个元素在集合中（假阳性）。

4. **无删除操作**：布隆过滤器不支持删除操作，因为删除元素会破坏过滤器的准确性。

5. **动态性**：布隆过滤器可以动态地添加元素，但随着元素的增加，误判率也会增加。

6. **应用场景**：布隆过滤器广泛应用于数据库、缓存系统、网络爬虫等领域，用于减少对存储系统的访问次数，提高系统性能。

7. **可调整性**：布隆过滤器的参数（如位数组的大小和哈希函数的数量）可以根据实际需求进行调整，以平衡空间效率和误判率。

布隆过滤器的工作原理是使用多个哈希函数将集合中的元素映射到位数组中的多个位置。查询时，同样的哈希函数会被用来确定元素是否在位数组的相应位置都被设置为1。如果所有哈希函数都返回1，
则认为元素可能在集合中；如果任何一个返回0，则元素一定不在集合中。

由于布隆过滤器的这些特性，它非常适合用于大规模数据集的快速查找和过滤，尤其是在内存资源有限的情况下。

*/
class BloomFilter
{
public:
    BloomFilter(int bitSize = 1471) : bitSize_(bitSize)
    {
        bitMap_.resize(bitSize_ / 32 + 1);
    }

    //添加元素O(1)
    void setBit(const char* str)
    {
        //计算3组哈希函数的值
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx2 / 32;
        offset = idx2 % 32;
        bitMap_[index] |= (1 << offset);

        index = idx3 / 32;
        offset = idx3 % 32;
        bitMap_[index] |= (1 << offset);
    }

    //查询元素O(1)
    bool getBit(const char* str)
    {
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;    
        
        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        if(0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        index = idx2 / 32;
        offset = idx2 % 32;
        if(0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        index = idx3 / 32;
        offset = idx3 % 32;
        if(0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        return true;
    }

private:
    int bitSize_; //位图的大小
    vector<int> bitMap_; //位图数组
};

//URL黑名单
class BlackList
{
public:
    void add(string url)
    {
        blockList_.setBit(url.c_str());
    }

    bool query(string url)
    {
        return blockList_.getBit(url.c_str());
    }

private:
    BloomFilter blockList_;
};

int main()
{
    BlackList list;
    list.add("http://www.caidu.com");
    list.add("http://www.361buy.com");
    list.add("http://www.cmall.com");
    list.add("http://www.cencent.com");

    string url = "http://www.alibaba.com";
    string url1 = "http://www.cencent.com";
    cout << boolalpha << list.query(url) << endl;
    cout << boolalpha << list.query(url1) << endl;
    return 0;
}