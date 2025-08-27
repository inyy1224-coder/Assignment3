#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// ====================== Item ���� ���� ======================
class Item {
protected:
    string name_;
public:
    Item(const string& name = "������") : name_(name) {}
    virtual ~Item() {}
    virtual void PrintInfo() const {
        cout << "������: " << name_ << endl;
    }
};

class Weapon : public Item {
    int attack_;
public:
    Weapon(const string& name = "����", int attack = 10)
        : Item(name), attack_(attack) {}
    void PrintInfo() const override {
        cout << "����: " << name_ << " (���ݷ�: " << attack_ << ")" << endl;
    }
};

class Potion : public Item {
    int heal_;
public:
    Potion(const string& name = "����", int heal = 20)
        : Item(name), heal_(heal) {}
    void PrintInfo() const override {
        cout << "����: " << name_ << " (ȸ����: " << heal_ << ")" << endl;
    }
};

// ====================== Inventory ���ø� ======================
template <typename T>
class Inventory {
private:
    T* pItems_;     // ���� �迭
    int capacity_;  // �ִ� �뷮
    int size_;      // ���� ������ ����

public:
    // ������
    Inventory(int capacity = 10)
        : capacity_(capacity), size_(0) {
        if (capacity_ <= 0) capacity_ = 1;
        pItems_ = new T[capacity_];
    }

    // �Ҹ���
    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
    }

    // ������ �߰�
    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_] = item;
            size_++;
        }
        else {
            cout << "�κ��丮�� �� á���ϴ�!" << endl;
        }
    }

    // ������ ������ ����
    void RemoveLastItem() {
        if (size_ > 0) {
            size_--;
        }
        else {
            cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
        }
    }

    // ���� ���� ��ȯ
    int GetSize() const { return size_; }

    // �뷮 ��ȯ
    int GetCapacity() const { return capacity_; }

    // ====================== ��� ======================
    // Item �迭�̸� PrintInfo() ȣ��
    template <typename U = T>
    typename enable_if<is_base_of<Item, U>::value>::type
        PrintAllItems() const {
        if (size_ == 0) {
            cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            pItems_[i].PrintInfo();
        }
    }

    // �Ϲ� Ÿ���̸� cout <<
    template <typename U = T>
    typename enable_if<!is_base_of<Item, U>::value>::type
        PrintAllItems() const {
        if (size_ == 0) {
            cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            cout << pItems_[i] << endl;
        }
    }
};

// ====================== �׽�Ʈ ======================
int main() {
    cout << "=== ���� �κ��丮 ===" << endl;
    Inventory<Weapon> weaponInv(3);
    weaponInv.AddItem(Weapon("���", 50));
    weaponInv.AddItem(Weapon("Ȱ", 30));
    weaponInv.AddItem(Weapon("����", 70));
    weaponInv.AddItem(Weapon("â", 40)); // �� á��
    weaponInv.PrintAllItems();

    cout << "\n=== ���� �κ��丮 ===" << endl;
    Inventory<Potion> potionInv(2);
    potionInv.AddItem(Potion("HP ����", 100));
    potionInv.AddItem(Potion("MP ����", 50));
    potionInv.PrintAllItems();

    cout << "\n=== ���� �κ��丮 ===" << endl;
    Inventory<int> intInv(5);
    intInv.AddItem(10);
    intInv.AddItem(20);
    intInv.AddItem(30);
    intInv.PrintAllItems();

    cout << "\n=== ���ڿ� �κ��丮 ===" << endl;
    Inventory<string> strInv(3);
    strInv.AddItem("��ȭ �ֹ���");
    strInv.AddItem("���� ����");
    strInv.PrintAllItems();

    return 0;
}