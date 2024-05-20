#include <iostream>

using namespace std;

int partition(int arr[], int begin, int end)
{
    int val = arr[begin];
    int i = begin;
    int j = end;

    while(i < j)
    {
        while(i < j && arr[j] < val) --j;

        if(i < j)
        {
            arr[i] = arr[j];
            ++i;
        }

        while(i < j && arr[i] > val) ++i;
        
        if(i < j)
        {
            arr[j] = arr[i];
            --j;
        }
    }
    arr[i] = val;
    return i;
}


void selectTopK(int arr[], int begin, int end, int k)
{
    int pos = partition(arr, begin, end);
    if(pos == k - 1)
    {
        return;
    }
    else if(pos > k - 1)
    {
        selectTopK(arr, begin, pos - 1, k);
    }
    else
    {
        selectTopK(arr, pos + 1, end, k);
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {13, 25, 38, 44, 53, 22, 13, 34, 57, 88};
    int size = sizeof(arr) / sizeof(arr[0]);

    int k = 3;
    selectTopK(arr, 0, size - 1, k);

    for(int i = 0; i < k ; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}