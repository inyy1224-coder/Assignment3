#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// ====================== Item 계층 구조 ======================
class Item {
protected:
    string name_;
public:
    Item(const string& name = "아이템") : name_(name) {}
    virtual ~Item() {}
    virtual void PrintInfo() const {
        cout << "아이템: " << name_ << endl;
    }
};

class Weapon : public Item {
    int attack_;
public:
    Weapon(const string& name = "무기", int attack = 10)
        : Item(name), attack_(attack) {}
    void PrintInfo() const override {
        cout << "무기: " << name_ << " (공격력: " << attack_ << ")" << endl;
    }
};

class Potion : public Item {
    int heal_;
public:
    Potion(const string& name = "포션", int heal = 20)
        : Item(name), heal_(heal) {}
    void PrintInfo() const override {
        cout << "포션: " << name_ << " (회복량: " << heal_ << ")" << endl;
    }
};

// ====================== Inventory 템플릿 ======================
template <typename T>
class Inventory {
private:
    T* pItems_;     // 동적 배열
    int capacity_;  // 최대 용량
    int size_;      // 현재 아이템 개수

public:
    // 생성자
    Inventory(int capacity = 10)
        : capacity_(capacity), size_(0) {
        if (capacity_ <= 0) capacity_ = 1;
        pItems_ = new T[capacity_];
    }

    // 소멸자
    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
    }

    // 아이템 추가
    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_] = item;
            size_++;
        }
        else {
            cout << "인벤토리가 꽉 찼습니다!" << endl;
        }
    }

    // 마지막 아이템 제거
    void RemoveLastItem() {
        if (size_ > 0) {
            size_--;
        }
        else {
            cout << "인벤토리가 비어있습니다." << endl;
        }
    }

    // 현재 개수 반환
    int GetSize() const { return size_; }

    // 용량 반환
    int GetCapacity() const { return capacity_; }

    // ====================== 출력 ======================
    // Item 계열이면 PrintInfo() 호출
    template <typename U = T>
    typename enable_if<is_base_of<Item, U>::value>::type
        PrintAllItems() const {
        if (size_ == 0) {
            cout << "인벤토리가 비어있습니다." << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            pItems_[i].PrintInfo();
        }
    }

    // 일반 타입이면 cout <<
    template <typename U = T>
    typename enable_if<!is_base_of<Item, U>::value>::type
        PrintAllItems() const {
        if (size_ == 0) {
            cout << "인벤토리가 비어있습니다." << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            cout << pItems_[i] << endl;
        }
    }
};

// ====================== 테스트 ======================
int main() {
    cout << "=== 무기 인벤토리 ===" << endl;
    Inventory<Weapon> weaponInv(3);
    weaponInv.AddItem(Weapon("장검", 50));
    weaponInv.AddItem(Weapon("활", 30));
    weaponInv.AddItem(Weapon("도끼", 70));
    weaponInv.AddItem(Weapon("창", 40)); // 꽉 찼음
    weaponInv.PrintAllItems();

    cout << "\n=== 포션 인벤토리 ===" << endl;
    Inventory<Potion> potionInv(2);
    potionInv.AddItem(Potion("HP 포션", 100));
    potionInv.AddItem(Potion("MP 포션", 50));
    potionInv.PrintAllItems();

    cout << "\n=== 정수 인벤토리 ===" << endl;
    Inventory<int> intInv(5);
    intInv.AddItem(10);
    intInv.AddItem(20);
    intInv.AddItem(30);
    intInv.PrintAllItems();

    cout << "\n=== 문자열 인벤토리 ===" << endl;
    Inventory<string> strInv(3);
    strInv.AddItem("강화 주문서");
    strInv.AddItem("포션 설명서");
    strInv.PrintAllItems();

    return 0;
}