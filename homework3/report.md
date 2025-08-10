# 41143158

作業三

## 解題說明
本作業要求實作一個 Polynomial 類別，並支援多項式輸入與輸出（ >> 與 << 運算子），加/減/乘法及取值運算，需使用環狀鏈結串列。
### 解題策略
1. 採用鏈結串列儲存多項式，每個節點包含係數 coef、次方數 exp，以及指向下一節點的指標 link。
2. 
3. 
4. 
5. 

## 程式實作
程式碼：
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial
{
private:
    struct Node
    {
        int coef;
        int exp;
        Node *link;
    };
    Node *head;
    void Clear();
    void InsertTerm(int coef, int exp);

public:
    Polynomial();
    Polynomial(const Polynomial &other);
    ~Polynomial();
    Polynomial &operator=(const Polynomial &other);
    Polynomial operator+(const Polynomial &b) const;
    Polynomial operator-(const Polynomial &b) const;
    Polynomial operator*(const Polynomial &b) const;
    float Evaluate(float x) const;
    friend istream &operator>>(istream &in, Polynomial &poly);
    friend ostream &operator<<(ostream &out, const Polynomial &poly);
};

void Polynomial::Clear()
{
    Node *curr = head->link;
    while (curr != head)
    {
        Node *temp = curr;
        curr = curr->link;
        delete temp;
    }
    head->link = head;
}

void Polynomial::InsertTerm(int coef, int exp)
{
    if (coef == 0)
        return;
    Node *prev = head;
    Node *curr = head->link;
    while (curr != head && curr->exp > exp)
    {
        prev = curr;
        curr = curr->link;
    }
    if (curr != head && curr->exp == exp)
    {
        curr->coef += coef;
        if (curr->coef == 0)
        {
            prev->link = curr->link;
            delete curr;
        }
    }
    else
    {
        Node *newNode = new Node{coef, exp, curr};
        prev->link = newNode;
    }
}

Polynomial::Polynomial()
{
    head = new Node{0, -1, nullptr};
    head->link = head;
}

Polynomial::~Polynomial()
{
    Clear();
    delete head;
}

Polynomial::Polynomial(const Polynomial &other)
{
    head = new Node{0, -1, nullptr};
    head->link = head;
    Node *curr = other.head->link;
    while (curr != other.head)
    {
        InsertTerm(curr->coef, curr->exp);
        curr = curr->link;
    }
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
    if (this != &other)
    {
        Clear();
        Node *curr = other.head->link;
        while (curr != other.head)
        {
            InsertTerm(curr->coef, curr->exp);
            curr = curr->link;
        }
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &b) const
{
    Polynomial result;
    Node *aNode = head->link;
    Node *bNode = b.head->link;
    while (aNode != head && bNode != b.head)
    {
        if (aNode->exp > bNode->exp)
        {
            result.InsertTerm(aNode->coef, aNode->exp);
            aNode = aNode->link;
        }
        else if (aNode->exp < bNode->exp)
        {
            result.InsertTerm(bNode->coef, bNode->exp);
            bNode = bNode->link;
        }
        else
        {
            result.InsertTerm(aNode->coef + bNode->coef, aNode->exp);
            aNode = aNode->link;
            bNode = bNode->link;
        }
    }
    while (aNode != head)
    {
        result.InsertTerm(aNode->coef, aNode->exp);
        aNode = aNode->link;
    }

    while (bNode != b.head)
    {
        result.InsertTerm(bNode->coef, bNode->exp);
        bNode = bNode->link;
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial &b) const
{
    Polynomial result;
    Node *aNode = head->link;
    Node *bNode = b.head->link;
    while (aNode != head && bNode != b.head)
    {
        if (aNode->exp > bNode->exp)
        {
            result.InsertTerm(aNode->coef, aNode->exp);
            aNode = aNode->link;
        }
        else if (aNode->exp < bNode->exp)
        {
            result.InsertTerm(-bNode->coef, bNode->exp);
            bNode = bNode->link;
        }
        else
        {
            result.InsertTerm(aNode->coef - bNode->coef, aNode->exp);
            aNode = aNode->link;
            bNode = bNode->link;
        }
    }
    while (aNode != head)
    {
        result.InsertTerm(aNode->coef, aNode->exp);
        aNode = aNode->link;
    }
    while (bNode != b.head)
    {
        result.InsertTerm(-bNode->coef, bNode->exp);
        bNode = bNode->link;
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial &b) const
{
    Polynomial result;
    for (Node *aNode = head->link; aNode != head; aNode = aNode->link)
    {
        for (Node *bNode = b.head->link; bNode != b.head; bNode = bNode->link)
        {
            int newCoef = aNode->coef * bNode->coef;
            int newExp = aNode->exp + bNode->exp;
            result.InsertTerm(newCoef, newExp);
        }
    }
    return result;
}

float Polynomial::Evaluate(float x) const
{
    float sum = 0;
    for (Node *curr = head->link; curr != head; curr = curr->link)
    {
        sum += curr->coef * pow(x, curr->exp);
    }
    return sum;
}

istream &operator>>(istream &in, Polynomial &poly)
{
    poly.Clear();
    int n;
    in >> n;
    for (int i = 0; i < n; ++i)
    {
        int coef, exp;
        in >> coef >> exp;
        poly.InsertTerm(coef, exp);
    }
    return in;
}

ostream &operator<<(ostream &out, const Polynomial &poly)
{
    auto curr = poly.head->link;
    if (curr == poly.head)
    {
        out << "0";
        return out;
    }
    bool first = true;
    while (curr != poly.head)
    {
        if (!first)
            out << " + ";
        out << curr->coef << "x^" << curr->exp;
        first = false;
        curr = curr->link;
    }
    return out;
}

int main()
{
    Polynomial p1, p2;
    cout << "P1(x) :\n";
    cin >> p1;
    cout << "P2(x) :\n";
    cin >> p2;
    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;
    cout << "P1(x) = " << p1 << endl;
    cout << "P2(x) = " << p2 << endl;
    cout << "P1 + P2 = " << sum << endl;
    cout << "P1 - P2 = " << diff << endl;
    cout << "P1 * P2 = " << prod << endl;
    float val;
    cout << "Enter x to evaluate P1(x): ";
    cin >> val;
    cout << "P1(" << val << ") = " << p1.Evaluate(val) << endl;
}
```

## 效能分析
時間複雜度：<br>
m → 多項式 P1 項的個數，n → 多項式 P2 項的個數。<br>
加法： $O(m + n)$<br>
減法： $O(m + n)$<br>
乘法： $O(m \times n)$<br>
求值： $O(m)$

空間複雜度：<br>
加法： $O(m + n)$<br>
減法： $O(m + n)$<br>
乘法： $O(m \times n)$<br>
求值： $O(1)$

## 測試與驗證
測試結果
```

```

## 申論及開發報告
