// UniquePtr.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>

class BaseOb
{
public:
    BaseOb()
    {
        std::cout << "construct Base Ob\n";
    }
    virtual ~BaseOb()
    {
        std::cout << "destruct Base Ob\n";
    }
    virtual void SomeFunc()
    {
        std::cout << "Base Obj Func\n";
    }
};

class DeriveA : public BaseOb
{
public:
    DeriveA()
    {
        std::cout << "construct Derive A\n";
    }
    virtual ~DeriveA()
    {
        std::cout << "destruct Derive A\n";
    }
    virtual void SomeFunc() override
    {
        std::cout << "Derive A Func\n";
    }
};

class DeriveB : public BaseOb
{
public:
    DeriveB()
    {
        std::cout << "construct Derive B\n";
    }
    virtual ~DeriveB()
    {
        std::cout << "destruct Derive B\n";
    }
    virtual void SomeFunc() override
    {
        std::cout << "Derive B Func\n";
    }
};

int main()
{
    std::cout << "Hello World!\n";
    auto uni_pta = std::unique_ptr<BaseOb>(new DeriveA{});
    uni_pta->SomeFunc();
    auto uni_ptb = std::make_unique<DeriveB>(DeriveB{});
    uni_ptb->SomeFunc();
    // unique_ptr 沒有 dynamic pointer cast
    //auto uni_base = std::dynamic_pointer_cast<BaseOb, DeriveA>(uni_pt1);
    //auto uni_get = uni_ptb;
    auto& uni_get = uni_ptb;  // reference 可以
    uni_get->SomeFunc();
    //const std::unique_ptr<BaseOb>& uni_base_get = uni_ptb;  // derive unique ptr 不能轉給 base
    const std::unique_ptr<BaseOb>& uni_base_get = uni_pta;
    uni_base_get->SomeFunc();
    std::unique_ptr<BaseOb> uni_base_move = std::unique_ptr<BaseOb>(move(uni_ptb));  // 如此轉換到 base
    uni_base_move->SomeFunc();
    //uni_ptb->SomeFunc();  // C26800 : use after move, 程式碼分析警告
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
