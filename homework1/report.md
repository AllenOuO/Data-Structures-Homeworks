# 41143158

作業一

## 解題說明

本作業有兩個問題：

### 問題一：Ackermann 函數
要求撰寫遞迴/非遞迴版本的 Ackermann 函數程式。

### 解題策略
1. 直接按照其基本數學定義實現遞迴版本
2.  
3. 

### 問題二：Power Set 生成
Power Set 是一集合內所有子集合組成的集合。

### 解題策略
1. 
2.  
3. 

## 程式實作

### 問題一：Ackermann 函數

遞迴版本程式碼：

```cpp
#include <iostream>

int A(int m, int n);
int A(int m, int n){
    if (m == 0) return n + 1;
    else if (n == 0) return A(m - 1, 1);
    else return A(m - 1, A(m, n - 1));
}

int main(){
    int m, n;
    while(1){
        std::cout << "Enter m and n: ";
        std::cin >> m >> n;
        std::cout << "A(" << m << ", " << n << ") = " << A(m, n) << std::endl;
    }
}
```

非遞迴版本程式碼：

```cpp
#include<iostream>

int A(int m,int n){
    int a[100000];
    int i = 0;
    while(1){
        if(0 == m){
            if(0 == i){
                return ++n;
	    }
	    n++;
            m = a[i--];
        }
        if(0 == n){
            m--;
            n++;
        }
        if( 0 != m && 0 != n){
            a[++i] = m - 1;
            n--;
        }
    }
}

int main(){
    int m, n;
    while(1){
        std::cout << "Enter m and n: ";
        std::cin >> m >> n;
        std::cout << "A(" << m << ", " << n << ") = " << A(m, n) << std::endl;
    }
}
```

### 問題二：Power Set 生成

程式碼：

```cpp
#include <iostream>
```

## 效能分析

### 問題一：Ackermann 函數效能比較
1. 時間複雜度：程式的時間複雜度為 $O()$。
2. 空間複雜度：空間複雜度為 $O()$。

### 問題二：Power Set 生成效能比較
1. 時間複雜度：程式的時間複雜度為 $O()$。
2. 空間複雜度：空間複雜度為 $O()$。

## 測試與驗證


## 申論及開發報告

