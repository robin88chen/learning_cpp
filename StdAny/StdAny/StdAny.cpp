// StdAny.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <vector>
#include <any>
#include <optional>
#include <functional>
#include <unordered_map>

static int s_counter = 0;
class obj
{
public:
    obj() : m_a{ s_counter++ }
    {
        std::cout << " obj " << m_a << " construct. \n";
    };
    obj(const obj& o)
    {
        m_a = o.m_a;
        std::cout << "obj " << m_a << " copied. \n";
    }
    
    ~obj()
    {
        std::cout << " obj " << m_a << " destruct. \n";
    }

    int m_a;
};


class bank
{
public:
    bank()
    {
        std::cout << "bank construct. \n";
    }
    ~bank()
    {
        std::cout << "bank destruct. \n";
    }
    void set(const std::any& a)  
    {
        std::cout << "set bank data. \n";
        m_data = a;
    }

    //template <class T> void set_org(T a) /// 如果參數type 直接寫 T, 會複製傳進來
    template <class T> void set_org(const T& a) /// 這樣是物件參考，參數不會複製
    {
        std::cout << "set bank org data. \n";
        m_data = a; /// 這裡會複製
    }

    const std::any& get()  
    {
        std::cout << "get bank data. \n";
        return m_data;
    }
    template <class T> T get_org()
    {
        std::cout << "get bank org data. \n";
        return std::any_cast<T>(m_data);
    }
    template <class T> std::optional<T> get_opt()
    {
        std::cout << "get bank opt data. \n";
        return std::any_cast<T>(m_data);
    }
    template <class T> std::optional<std::reference_wrapper<T>> get_opt_ref()
    {
        std::cout << "get bank opt data. \n";
        //return std::any_cast<T>(m_data); /// 這樣編譯不過, C2440
        //return std::ref(std::any_cast<T>(m_data)); /// 這樣編譯不過 C2280, C2440
        return std::ref(m_data);
    }
    std::any m_data;
    //const std::any& m_data; /// 不能用
};
using func_any = std::function<std::any(const std::string&)>;
class func_store
{
public:
    std::any invoke(const std::string& name, const std::string& param)
    {
        auto found = m_funcs.find(name);
        if (found != m_funcs.end()) return found->second(param);
        return nullptr;
    }

    std::unordered_map<std::string, func_any> m_funcs;
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

std::any any_invoker(const std::string& param)
{
    return std::string(param);
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

        //func(std::ref(std::any(obj_vec)));  /// std ref 不能這樣用
        std::cout << "end block\n";
    }

    auto b = new bank();
    std::cout << "any bank test\n";
    {
        std::vector<obj> obj_vec{ 10 };
        b->set_org(obj_vec);

        //auto obv = b->get();  /// 取出 std any, 又複製一遍
        const std::any& obv = b->get();  /// 這個不會複製
        std::cout << "bank data got. \n";

        //auto ov = std::any_cast<std::vector<obj>>(obv);  /// 這個會複製
        //const std::vector<obj>& ov1 = std::any_cast<std::vector<obj>>(obv);  /// 照樣會複製
        //auto ov1 = std::any_cast<const std::vector<obj>&>(obv);  /// 照樣會複製, auto 不是引用
        //const std::vector<obj>& ov1 = std::any_cast<const std::vector<obj>&>(obv);  /// 這就沒有複製了
        //const std::vector<obj>& ov1 = std::any_cast<std::vector<obj>>(obv);  /// 有複製, 因為 any cast 物件而不是參考
        //auto& ov1 = std::any_cast<const std::vector<obj>&>(obv);  /// 這就沒有複製了

        //const std::vector<obj>& ov2 = b->get_org<std::vector<obj>>();  /// 有複製
        //const std::vector<obj>& ov2 = b->get_org<const std::vector<obj>&>();  /// 沒有複製
        //auto ov2 = b->get_org<const std::vector<obj>&>();  /// 有複製, auto 不是引用
        //auto& ov2 = b->get_org<const std::vector<obj>&>();  /// 沒有複製
        auto& ov2 = b->get_org<std::vector<obj>&>();  /// 沒有複製, 可以取出來改
        ov2[8].m_a = -23;
        std::cout << "end block\n";
    }
    /// 結論是, any 是 value, 建構或指定時會複製一份; 取值時並不會特別複製一份
    std::cout << "delete bank\n";
    delete b;

    auto b1 = new bank();
    std::cout << "any bank optional test\n";
    {
        std::vector<obj> obj_vec{ 10 };
        b1->set_org(obj_vec);

        //auto ov1 = b1->get_opt<const std::vector<obj>&>();  /// optional 不能拿引用
        auto ov1 = b1->get_opt<std::vector<obj>>();  /// optional 給 value, 所以會複製
        //auto ov1 = b1->get_opt_ref<std::vector<obj>>();  /// optional 不給傳
        auto ov2 = b1->get_opt_ref<std::any>(); /// 只能取 std::any
        std::cout << "end block\n";
    }
    /// 結論是, optional 只能裝 value, 會複製一份;
    std::cout << "delete bank\n";
    delete b1;

    std::cout << "any func store\n";
    auto fs = new func_store();
    fs->m_funcs.emplace("any_invoker", any_invoker);
    std::cout << "invoke func : " << std::any_cast<std::string>(fs->invoke("any_invoker", "test string")) << "\n";
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
