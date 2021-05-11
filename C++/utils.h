/*

	Lucas Araújo Pena - 13/0056162
	SCIC0201 - Segurança Computacional - 2021/1
	Professor: João Gondim
	Trabalho de Implementação: Gerador/Verificador de Assinaturas

	Linguagem: C++11
	SO: Windows 10
	Compilado no Visual Studio 2019

*/

#ifndef __UTILS_H__
#define __UTILS_H__

// Macros
#define PRINT(X) 					std::cout << X << std::endl;
#define PRINT_INLINE(X) 			std::cout << X;
#define PRINT_TWO_ELEMENTS(X, Y) 	std::cout << X << Y << std::endl;
#define GET(X) 						std::cin >> X;
#define GET_MESSAGE(X) 				std::cin.getline(X, sizeof(X));
#define GETLINE(X) 					std::getline(std::cin, X);
#define ERROR(X) 					throw(std::runtime_error(X));

// Greater Common Divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Exponenciação Modular
int modulo(int a, int b, int n){
    long long x=1, y=a;
    while (b > 0) {
        if (b%2 == 1) {
            x = (x*y) % n; 
        }
        y = (y*y) % n;
        b /= 2;
    }
    return x % n;
}

#endif