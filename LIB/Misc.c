#include "Misc.h"

u8 BinarySearch(const float* arr, u8 size, float target)
{
    u8 left = 0;
    u8 right = size - 1;
    u8 mid;

    // Out of range handling
    if (target >= arr[0])
        return 0xff;

    if (target <= arr[size - 1])
        return 0xff;

    while (left <= right)
    {
        mid = (left + right) >> 1;

        // Found interval:
        // table[mid] >= target > table[mid+1]
        if ((arr[mid] >= target) && (target > arr[mid + 1]))
        {
            return mid;
        }

        // Search lower half
        if (target > arr[mid])
        {
            right = mid - 1;
        }
        // Search upper half
        else
        {
            left = mid + 1;
        }
    }

    return 0xff;
}

void InsertionSort(u16* arr, u8 n)
{
    u8 i, j;
    u16 key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}