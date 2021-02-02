// container_move.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>

static int s_counter = 0;
static int s_counter2 = 0;
class obj
{
public:
    obj() : m_a{ s_counter++ }
    {
        std::cout << " obj " << m_a << " construct. \n";
    };
    ~obj()
    {
        std::cout << " obj " << m_a << " destruct. \n";
    }
    int m_a;
};
class obj2
{
public:
    obj2() : m_a{ s_counter2++ }
    {
        std::cout << " obj2 " << m_a << " construct. \n";
    };
    ~obj2()
    {
        std::cout << " obj2 " << m_a << " destruct. \n";
    }
    obj2(const obj2& o)
    {
        m_a = o.m_a;
        std::cout << "obj2 " << m_a << " copy. \n";
    }
    obj2& operator=(const obj2& o)
    {
        m_a = o.m_a;
        std::cout << "obj2 " << m_a << " copy assignment. \n";
        return *this;
    }
    int m_a;
};
int main()
{
    std::cout << "Hello World!\n";
    {
        /// obj 0 --> 9 construct.
        std::vector<obj> obj_vec{ 10 };
        /// copy objs, 不過沒辦法 step into compiler 建立的 copyer
        std::vector<obj> obj_vec2 = obj_vec;

        /// 解構子呼叫 obj 0 --> 9, 兩輪
    }

    std::cout << "move test\n";
    {
        /// obj 10 --> 19 construct.
        std::vector<obj> obj_vec{ 10 };
        /// move objs, obj 20 --> 29 construct.
        std::vector<obj> obj_vec2 = std::vector<obj>{ 10 };
        std::cout << "destruct vectors!! \n";
        /// 解構子呼叫 obj 20 --> 29, obj 10 --> 19
        /// 證實了第二行是移動
    }
    std::cout << "copy construct test\n";
    {
        /// obj 0 --> 9 construct.
        std::vector<obj2> obj_vec{ 10 };
        /// copy objs, call copy constructor 0 --> 9, 並沒有呼叫 copy assignment
        std::vector<obj2> obj_vec2 = obj_vec;

        /// 解構子呼叫 obj 0 --> 9, 兩輪
    }

    std::cout << "copyable move test\n";
    {
        /// obj 10 --> 19 construct.
        std::vector<obj2> obj_vec{ 10 };
        /// move objs, obj 20 --> 29 construct. 沒有呼叫 copy constructor
        std::vector<obj2> obj_vec2 = std::vector<obj2>{ 10 };
        std::cout << "destruct vectors!! \n";
        /// 解構子呼叫 obj 20 --> 29, obj 10 --> 19
        /// 證實了第二行是移動
    }

    std::cout << "The End.\n";
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
