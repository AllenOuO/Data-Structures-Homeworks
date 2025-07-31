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

    return 0;
}
