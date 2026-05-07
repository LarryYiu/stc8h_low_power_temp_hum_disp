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