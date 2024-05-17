#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

/*
有两个文件分别是a和b，各自存放约1亿条ip地址，每个ip地址占用4个字节的存储空间，内存限制使用100M。
找出两个文件中重复的ip地址并输出。

思路1：将a文件中的ip存放在一个哈希表中，然后遍历文件b中的ip，每遍历一个ip地址，在哈希表中搜索一下，
搜到的，就是两个文件重复的ip并进行输出。unordered_set unordered_map

思路2: 有1亿个整数，最大值不超过1亿，谁是第一个重复的，谁是第一个不重复的，都有哪些元素重复了？ 内存限制100M

1亿 = 100M
100M * 4 = 400M * 2 = 800M 正负

位图算法
int bitmap[100000000/32 + 1] -> 3.2M 取上界

缺陷：如果有一个数字过大，而整体的数字个数较少，会浪费存储空间。适用于数据的个数与数据序列中最大值相当的情况。
不能统计重复次数。

以下是位图算法：
*/

int main()
{
    vector<int> vec{12, 77, 43, 83, 92, 44, 25, 20, 12};

    //定义位图数组
    int max = vec[0];
    for(int i = 1; i < vec.size(); ++i)
    {
        if(vec[i] > max)
        {
            max = vec[i];
        }
    }

    int* bitmap = new int[max / 32 + 1]();
    unique_ptr<int> ptr(bitmap);

    //查找第一个重复出现的数字
    for(auto key : vec)
    {
        int index = key / 32;
        int offset = key % 32;

        //获取key对应位的数值
        if((bitmap[index] & (1 << offset)) == 0)
        {
            //key之前没有出现过，记录key
            bitmap[index] |= (1 << offset);
        }
        else
        {
            //cout << "第一个重复出现的数字是：" << key << endl;
            //return 0;

            cout << key << "重复出现了!" << endl;
        }
    }

    vector<int> vec1 = {1, 2, 3, 4};
    for(auto key : vec1)
    {
        int index = key / 32;
        int offset = key % 32;
        if((bitmap[index] & (1 << offset)) == 0)
        {
            //cout << key << "是第一个没有重复出现的数字!" << endl;
            //return 0;
            cout << key << "没有重复出现!" << endl;
        }
    }

    return 0;
}