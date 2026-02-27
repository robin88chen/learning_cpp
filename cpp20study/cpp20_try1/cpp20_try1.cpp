// cpp20_try1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <ranges>
#include <vector>
#include <chrono>

int main()
{
    std::cout << "Hello World!\n";
    auto data_view = std::ranges::iota_view{ 1, 100 };
    std::vector<int> vec{ data_view.begin(), data_view.end() };
    for (auto chunk_data : vec | std::ranges::views::chunk(9)) // C++23 才有的功能
    {
        auto elements = chunk_data | std::ranges::views::take(3);
        std::vector<int> vec_e = { elements.begin(), elements.end() };
        for (auto e : elements)
        {
            std::cout << e << ' ';
        }
    }
    auto sys_tp = std::chrono::system_clock::now();
    auto cur_tp = std::chrono::current_zone()->to_local(sys_tp);
    auto loc_utc_tp = std::chrono::locate_zone("UTC")->to_local(sys_tp);
    std::cout << "\nsys tp: " << sys_tp << "\n";
    std::cout << "cur tp: " << cur_tp << "\n";
    std::cout << "loc utc tp: " << loc_utc_tp << "\n";
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示:
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
