#include "mssm.h"
#include "gtest/gtest.h"
#include <vector>

template <typename T>
std::vector<T> mergeSort(std::vector<T> list)
{
    if(list.size() == 1) return list;
    if(list.size() == 2)
    {
        if(list[0] > list[1])
        {
            swap(list[0], list[1]);
            return list;
        }
    }
    if(list.size() > 2)
    {
        std::vector<T> lList = {};
        std::vector<T> rList = {};
        for(int i = 0; i < list.size() / 2; i++)
        {
            lList.push_back(list[i]);
        }
        for(int i = list.size() / 2; i < list.size(); i++)
        {
            rList.push_back(list[i]);
        }
        lList = mergeSort(lList);
        rList = mergeSort(rList);
        list = {};

        int lIndex = 0;
        int rIndex = 0;
        while(true)
        {
            if(lIndex < lList.size() && rIndex < rList.size())
            {
                if(lList[lIndex] <= rList[rIndex])
                {
                    list.push_back(lList[lIndex]);
                    lIndex++;
                }
                if(lList[lIndex] > rList[rIndex])
                {
                    list.push_back(rList[rIndex]);
                    rIndex++;
                }
            }
            else if (lIndex < lList.size())
            {
                list.push_back(lList[lIndex]);
                lIndex++;
            }
            else if (rIndex < rList.size())
            {
                list.push_back(rList[rIndex]);
                rIndex++;
            }
            else break;
        }
        return list;
    }
    return list;
}

TEST(TestSort, TestSortList)
{
    std::vector<int> list = { 5,3,8,145,324,22,0,-100,-25 };
    std::vector<int> expected = { -100,-25,0,3,5,8,22,145,324 };
    ASSERT_EQ(mergeSort(list), expected);
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
