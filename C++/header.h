/*

	Lucas Araújo Pena - 13/0056162
	SCIC0201 - Segurança Computacional - 2021/1
	Professor: João Gondim
	Trabalho de Implementação: Gerador/Verificador de Assinaturas

	Linguagem: C++11
	SO: Windows 10
	Compilado no Visual Studio 2019

*/

#ifndef __HEADER_H__
#define __HEADER_H__

// ---------- Classes ----------
class RSA {
   public:
    unsigned long long p, q = 0;   // p input (primo)
    unsigned long long n;          // n = p * q
    unsigned long long phi;        // phi = (p-1) * (q-1)
    unsigned long long d;          // (e * d) mod phi = 1
    unsigned long long e;          // 1 < e < phi (e and phi coprime)
    unsigned keysize = 16;         // Tamanho da chave
    unsigned MRIterations = 20;    // Iterações de Miller-Rabin

    void                getPrimeNumbers();
    unsigned long long  generatePrimeNumbers();
    void                primalityCheck();
    bool                millerRabin(unsigned long long number, unsigned iterations);
    bool                isPrime(unsigned long long number, unsigned MRIterations);
    void                calculate_n();
    void                calculate_phi();
    void                calculate_e();
    void                calculate_d();
    void                RSA_Enc(std::string      mensagem);
    void                RSA_Dec(std::vector<int> mensagem);

    std::string mensagem;
    std::vector<int> mensagem_cifrada;
    std::vector<int> mensagem_decifrada;

};

// ---------- Funções ----------
// Gera um número primo
unsigned long long RSA::generatePrimeNumbers() {
    unsigned long long number = 0;
    unsigned min = pow(2, keysize - 1);
    unsigned max = pow(2, keysize) - 1;

    number = min + rand() % max;
    
    // Roda o loop até encontrar um candidato a primo
    if(isPrime(number, MRIterations)){
        return number;
    } else {
        generatePrimeNumbers();
    }

}

// Checa se o número é primo
bool RSA::isPrime(unsigned long long number, unsigned MRIterations){
    unsigned long long c = number - 1;

    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    while(c % 2 == 0){
        c /= 2;
    }

    for (unsigned i = 0; i < MRIterations; i++){
        if(!millerRabin(number, c)) {
            return false;
        }
    }

    return true;
}

// Teste de Miller-Rabin
bool RSA::millerRabin(unsigned long long number, unsigned c) {
    unsigned a = 2 + rand() % (number - 2);
    unsigned x = modulo(a, c, number);

    if(x == 1 | x == (n - 1)) {
        return true;
    }

    while(c != number - 1){
        x = modulo(x, 2, number);
        c *= 2;

        if( x == 1 ) {
            return false;
        } else if( x == number - 1 ) {
            return true;
        }
    }

    return false;
}

// Calcula o valor de n
void RSA::calculate_n() {
    n = p * q;
    PRINT_TWO_ELEMENTS("n:   ", n);
}

// Calcula o valor de phi (Totiente de Euler)
void RSA::calculate_phi() {
    phi = (p - 1) * (q - 1);
    PRINT_TWO_ELEMENTS("phi: ", phi);
}

// Calcula o valor de e
void RSA::calculate_e() {
    unsigned long long i = 2;
    unsigned min = pow(2, keysize - 1);
    unsigned max = pow(2, keysize) - 1;

    i = min + rand() % max;

    if (gcd(i, phi) != 1){
        calculate_e();
    }
    else {
        e = i;
        PRINT_TWO_ELEMENTS("e:   ", e);

        if (e >= phi)
            ERROR("'e' eh igual ou maior que phi(n).");
    }


}

// Calcula o valor de d
void RSA::calculate_d() {
    unsigned k = 1;

    while(((k * phi) + 1) % e != 0){
      k++;
    }

    d = (1 + (k * phi))/e;
    PRINT_TWO_ELEMENTS("d:   ", d);
}

// Encripta a mensagem
void RSA::RSA_Enc(std::string received_message) {
    //for(int x = 0; received_message[x] != '\0'; x++){
    //    std::cout << received_message[x] <<" -> "<< int ( received_message[x] ) <<'\n';
    //}
 
    PRINT("");

    for(int x = 0; received_message[x] != '\0'; x++){
        unsigned msg = int(received_message[x]);
        double cypher = modulo(msg, e, n);
        mensagem_cifrada.push_back(cypher);
    }

    PRINT_INLINE("Mensagem criptografada:   ");
    for (auto i = mensagem_cifrada.begin(); i != mensagem_cifrada.end(); ++i){
        std::cout << char(*i); // << ' ';   
    }
}

// Decifra a mensagem
void RSA::RSA_Dec(std::vector<int> received_message) {
    for(auto x = received_message.begin(); x != received_message.end(); ++x){
        unsigned my_char = *x;
        double message = modulo(my_char, d, n);
        mensagem_decifrada.push_back(message);
    }

    PRINT_INLINE("Mensagem decriptografada: ");
    for (auto i = mensagem_decifrada.begin(); i != mensagem_decifrada.end(); ++i){
        std::cout << char(*i); // << ' ';   
    }
}

#endif
