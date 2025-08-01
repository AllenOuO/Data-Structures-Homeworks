# 41143158

作業二

## 解題說明
本作業要求實作一個 Polynomial 類別，並支援多項式輸入與輸出（ >> 與 << 運算子），加法，乘法及取值運算。
### 解題策略
1. Term 類別包含係數coef與次方數exp。
2. 同時跑兩個 term 陣列，若次方數相同則加總係數，否則直接加入次方較大的項。
3. 對於 p1 p2 每項配對相乘，使用 NewTerm() 將其加入新多項式中，呼叫 SortAndCombine() 合併同次方項。
4. 使用 sum += coef × pow(x, exp) 計算每一項在 x 代入後的值。
5. 動態配置記憶體，確保空間充足。

## 程式實作
程式碼：
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
    friend istream& operator>>(istream&, Polynomial&);
    friend ostream& operator<<(ostream&, const Polynomial&);
private:
    float coef;
    int exp;
};

class Polynomial {
public:
    Polynomial();
    Polynomial(const Polynomial& other);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);

    Polynomial Add(Polynomial poly);
    Polynomial Mult(Polynomial poly);
    float Eval(float f);

    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray;
    int capacity;
    int terms;

    void NewTerm(float coef, int exp);
    void Resize();
    void SortAndCombine();
};

Polynomial::Polynomial() {
    capacity = 4;
    termArray = new Term[capacity];
    terms = 0;
}

Polynomial::~Polynomial() {
    delete[] termArray;
}

Polynomial::Polynomial(const Polynomial& other) {
    capacity = other.capacity;
    terms = other.terms;
    termArray = new Term[capacity];
    for (int i = 0; i < terms; i++)
        termArray[i] = other.termArray[i];
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] termArray;
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++)
            termArray[i] = other.termArray[i];
    }
    return *this;
}

void Polynomial::NewTerm(float c, int e) {
    if (c == 0) return;
    if (terms == capacity)
        Resize();
    termArray[terms].coef = c;
    termArray[terms].exp = e;
    terms++;
}

void Polynomial::Resize() {
    capacity *= 2;
    Term* newArray = new Term[capacity];
    for (int i = 0; i < terms; i++)
        newArray[i] = termArray[i];
    delete[] termArray;
    termArray = newArray;
}

void Polynomial::SortAndCombine() {
    sort(termArray, termArray + terms, [](const Term& a, const Term& b) {
        return a.exp > b.exp;
    });

    int newIndex = 0;
    for (int i = 1; i < terms; ++i) {
        if (termArray[newIndex].exp == termArray[i].exp) {
            termArray[newIndex].coef += termArray[i].coef;
        } else {
            newIndex++;
            termArray[newIndex] = termArray[i];
        }
    }
    terms = (termArray[newIndex].coef == 0) ? newIndex : newIndex + 1;
}

Polynomial Polynomial::Add(Polynomial poly) {
    Polynomial result;
    int i = 0, j = 0;
    while (i < terms && j < poly.terms) {
        if (termArray[i].exp > poly.termArray[j].exp)
            result.NewTerm(termArray[i].coef, termArray[i++].exp);
        else if (termArray[i].exp < poly.termArray[j].exp)
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j++].exp);
        else {
            float sum = termArray[i].coef + poly.termArray[j].coef;
            if (sum != 0)
                result.NewTerm(sum, termArray[i].exp);
            i++; j++;
        }
    }
    while (i < terms)
        result.NewTerm(termArray[i].coef, termArray[i++].exp);
    while (j < poly.terms)
        result.NewTerm(poly.termArray[j].coef, poly.termArray[j++].exp);
    return result;
}

Polynomial Polynomial::Mult(Polynomial poly) {
    Polynomial result;
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;
            result.NewTerm(newCoef, newExp);
        }
    }
    result.SortAndCombine();
    return result;
}

float Polynomial::Eval(float f) {
    float sum = 0;
    for (int i = 0; i < terms; i++) {
        sum += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return sum;
}

istream& operator>>(istream& in, Polynomial& poly) {
    poly.terms = 0;
    int n;
    in >> n;
    for (int i = 0; i < n; ++i) {
        float coef;
        int exp;
        in >> coef >> exp;
        poly.NewTerm(coef, exp);
    }
    poly.SortAndCombine();
    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    if (poly.terms == 0) {
        out << "0";
        return out;
    }

    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0)
            out << " + ";
        out << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return out;
}

int main() {
    Polynomial p1, p2;
    cout << "P1(x) :\n";
    cin >> p1;
    cout << "P2(x) :\n";
    cin >> p2;
    Polynomial sum = p1.Add(p2);
    Polynomial prod = p1.Mult(p2);
    cout << "P1(x) = " << p1 << endl;
    cout << "P2(x)= " << p2 << endl;
    cout << "P1 + P2 = " << sum << endl;
    cout << "P1 * P2 = " << prod << endl;
    float val;
    cout << "Input x :\n";
    cin >> val;
    cout << "P1(" << val << ") = " << p1.Eval(val) << endl;
}
```

## 效能分析
時間複雜度：<br>
m -> 多項式 P1 項的個數，n -> 多項式 P2 項的個數。<br>
加法： $O(m + n)$<br>
乘法： $O(m × n)$<br>
求值： $O(1)$

空間複雜度：<br>
加法： $O(m + n)$<br>
乘法： $O(m × n)$<br>
求值： $O(1)$

## 測試與驗證
測試結果
```
P1(x) :
2
3 2
5 0
P2(x) :
2
2 2
-5 0
P1(x) = 3x^2 + 5x^0
P2(x)= 2x^2 + -5x^0
P1 + P2 = 5x^2
P1 * P2 = 6x^4 + -5x^2 + -25x^0
Input x :
2
P1(2) = 17
```

## 申論及開發報告
本次作業主要目標是設計一個支援多項式運算的 Polynomial 類別。為達成此目標，我將多項式表示為一組 Term 結構的陣列，每個 Term 包含係數與次方數。設計重點在於正確處理多項式的加法、乘法與取值運算，並支援動態記憶體配置以容納任意數量的項。

採用動態陣列（Term* termArray）來儲存多項式項數，搭配記憶體管理（Resize()）來避免空間不足。此做法能在不使用 STL 容器下管理資料。使用 SortAndCombine() 將項次相同者合併並排序。

加法採用兩指標法同時掃描兩個多項式的 termArray，依照次方數比對並合併。乘法則為雙層迴圈暴力相乘，所有項成對相乘後統一呼叫 SortAndCombine()。

針對 << 運算子的輸出做了格式化處理，確保每一項以正確的格式顯示。
