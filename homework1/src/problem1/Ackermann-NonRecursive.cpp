#include<iostream>

int A(int m,int n){
	int a[100000];
	int i = 0;
	while(1){
		if(0 == m){
			if(0==i){
				return ++n;
			}
			n++;
			m=a[i--];
		}
		if(0 == n){
			m--;
			n++;
		}

		if( 0 != m && 0 != n){
			a[++i]=m-1;
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