// StdAny.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <vector>
#include <any>
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

void func(const std::any& a)
{
    std::any a1 = a;  /// 如果傳進 value, 會再複製一份, 如果用 std::ref 傳進引用, 就會存放引用不會複製
    std::cout << a1.type().name();
    //auto ob = std::any_cast<std::vector<obj>>(a);  /// 傳 value 進來, 這裡又複製一份
    //auto ob_r = std::any_cast<const std::vector<obj>&>(a);  /// 也還是複製一份 value
    //auto ob = std::any_cast<std::vector<obj>>(std::ref(a));  /// by value, by ref 都不能轉, std::cref 也不行
    //auto ob = std::any_cast<std::vector<obj>>(std::ref(a1));  /// 這樣不能轉
    //auto ob = std::any_cast<std::vector<obj>>(std::cref(a));  /// 這樣不能轉
    auto ob = std::any_cast<std::reference_wrapper<std::vector<obj>>>(a1);  /// by reference 要這樣轉
    //ob[3].m_a = -1;  // by value
    ob.get()[3].m_a = -1; // by reference, 要從 wrapper 裡 get 出來
    std::cout << "func return\n";  /// 參數跟著內部變數一起解構
}

int main()
{
    std::cout << "Hello World!\n";
    {
        /// obj 0 --> 9 construct.
        std::vector<obj> obj_vec{ 10 };
        /// copy objs, 不過沒辦法 step into compiler 建立的 copyer
        //std::any a0 = obj_vec;  /// 複製了 obj_vec
        //const std::any& a = obj_vec;  /// 這裡也複製了 obj_vec
        //const std::any& a1 = a0; /// 這個沒有複製
        //const std::any& a2 = std::ref(obj_vec);  /// 這樣不會複製
        //func(obj_vec);  /// 複製一份傳進去
        func(std::ref(obj_vec));  /// 引用傳進去, 不會複製, 但是套了 reference wrapper
        std::cout << "end block\n";
    }
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
