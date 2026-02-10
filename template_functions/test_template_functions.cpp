#include <iostream>
#include <cassert>
#include <cstdint>   // для int16_t, int32_t, int64_t

// Подключаем все заголовочные файлы
#include "IsSortedUntil.hpp"
#include "Unique.hpp"
#include "Copy_CopyBackward.hpp"
#include "Revers_Rotate.hpp"
#include "Remove.hpp"
#include "BinarySearch.hpp"
#include "Merge.hpp"

int main() {
    using namespace std;

    // =============================
    // 1. IsSortedUntil
    int arr1[]{1, 2, 2, 3, 3, 4, 2, 5, 6};
    auto p1 = IsSortedUntil(arr1, arr1 + 9);
    assert(p1 == arr1 + 6); // 2 нарушает порядок
    cout << "IsSortedUntil passed\n";

    // =============================
    // 2. Unique
    int arr2[]{1, 2, 2, 3, 3, 4, 5, 5, 6};
    auto p2 = Unique(arr2, arr2 + 9);
    assert(p2 == arr2 + 6); // уникальные: 1 2 3 4 5 6
    cout << "Unique passed\n";

    // =============================
    // 3. Copy & CopyBackward
    int src[] = {5, 6, 7};
    int dest[3]{0};
    auto p3 = Copy(src, src + 3, dest);
    assert(p3 == dest + 3 && dest[0] == 5 && dest[2] == 7);
    
    int dest2[3]{0};
    auto p4 = CopyBackward(src, src + 3, dest2 + 3);
    assert(p4 == dest2 + 3 && dest2[0] == 5 && dest2[2] == 7);
    cout << "Copy & CopyBackward passed\n";

    // =============================
    // 4. Reverse & Rotate
    int arr3[]{1, 2, 3, 4, 5};
    Reverse(arr3 + 1, arr3 + 4); // [1, 4, 3, 2, 5]
    assert(arr3[1] == 4 && arr3[3] == 2);

    Rotate(arr3, arr3 + 2, arr3 + 5); // [3, 2, 5, 1, 4]
    assert(arr3[0] == 3 && arr3[4] == 4);
    cout << "Reverse & Rotate passed\n";

    // =============================
    // 5. Remove
    int arr4[]{1, 2, 6, 4, 1, 1, 8, 0, 1};
    auto p5 = Remove(arr4, arr4 + 9, 1);
    assert(p5 == arr4 + 5); // [2,6,4,8,0]
    cout << "Remove passed\n";

    // =============================
    // 6. BinarySearch, LowerBound, UpperBound
    int arr5[]{1, 2, 3, 3, 5};
    assert(BinarySearch(arr5, arr5 + 5, 3) == true);
    assert(BinarySearch(arr5, arr5 + 5, 4) == false);

    auto lb = LowerBound(arr5, arr5 + 5, 3);
    auto ub = UpperBound(arr5, arr5 + 5, 3);
    assert(lb == arr5 + 2);
    assert(ub == arr5 + 4);
    cout << "BinarySearch, LowerBound, UpperBound passed\n";

    // =============================
    // 7. Merge
    int16_t first[2]{1, 4};
    int32_t second[3]{2, 3, 5};
    int64_t out[5]{0};
    auto p7 = Merge(first, first + 2, second, second + 3, out);
    assert(p7 == out + 5);
    for(int i=0;i<5;++i) assert(out[i] == i+1);
    cout << "Merge passed\n";

    cout << "All tests passed successfully!\n";

    return 0;
}
