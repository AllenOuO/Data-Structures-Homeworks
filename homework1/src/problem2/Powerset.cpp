#include <iostream>
#include <sstream>
#include <string>

int main(){
    std::string line;
    std::cout << "Input: ";
    getline(std::cin, line);
    std::stringstream ss(line);
    std::string token;
    std::string subs[100];
    int n = 0;
    while(ss >> token) 
        subs[n++] = token;
    std::cout << "{";
    bool a = true;
    int total = 1 << n;
    for(int i = 0; i < total; ++i)
    {
        if(!a) 
            std::cout << ", ";
        std::cout << "{";
    for(int j = 0; j < n; ++j)
    {
        if (i & (1 << j))
            std::cout << subs[j];
    }
    std::cout << "}";
    a = false;
    }
    std::cout << "}" << std::endl;
}
