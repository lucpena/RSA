/*

	Lucas Araújo Pena - 13/0056162
	SCIC0201 - Segurança Computacional - 2021/1
	Professor: João Gondim
	Trabalho de Implementação: Gerador/Verificador de Assinaturas

	Linguagem: C++11
	SO: Windows 10
	Compilado no Visual Studio 2019
    
    Alguns primos:

    25013
    25121  

*/

// Includes
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <iomanip>

#include "utils.h"
#include "header.h"

// Main loop
int main() {
    try {
        // Gerando as chaves
        RSA RSA_Helper;

        // Calculando os numeros primos p e q
        PRINT("Calculando numeros primos e RSA......");
        PRINT("");

        RSA_Helper.p = RSA_Helper.generatePrimeNumbers();
        RSA_Helper.q = RSA_Helper.generatePrimeNumbers();

        PRINT_TWO_ELEMENTS("p -> ", RSA_Helper.p);
        PRINT_TWO_ELEMENTS("q -> ", RSA_Helper.q);

        PRINT("");
        RSA_Helper.calculate_n();
        RSA_Helper.calculate_phi();
        RSA_Helper.calculate_e();
        RSA_Helper.calculate_d();
        PRINT("");

        // Recebendo a mensagem para ser criptografada
        PRINT_INLINE("Entre com a frase para ser criptografada: ");
        GET(RSA_Helper.mensagem);

        // Criptografando com RSA
        PRINT("");
        RSA_Helper.RSA_Enc(RSA_Helper.mensagem);

        // Decriptografando com RSA
        PRINT("");
        RSA_Helper.RSA_Dec(RSA_Helper.mensagem_cifrada);
        PRINT("");

    } catch (std::runtime_error& s) {
        PRINT(s.what());
    }

    return 0;
}