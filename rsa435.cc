// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigUnsigned generate(BigUnsigned x) {
    
    BigUnsigned X = BigUnsigned(2);
    for(int i=1; i<256; i++) {
        x = (x*10) + rand() % 10;
    }
    x = (x*10)+7;
    
    return x;
}

BigUnsigned testPrime(BigUnsigned x, BigUnsigned a) {
    
    BigUnsigned test = BigUnsigned(0);
    BigUnsigned exp = x-1;
    
    test = modexp(a, exp, x);
    
    while(test!=1) {
        //x=x+10;
        //test = modexp(a, exp, x);
        
        test = BigUnsigned(0);
        for(int i=1; i<256; i++) {
            test = (x*10) + rand() % 10;
        }
        test = (x*10)+7;
//        std::cout << "test: " << test << '\n';
        
        test = modexp(a, exp, x);
    }
    std::cout << "prime: " << x << '\n';
    
    return x;
}

void writeToFile(BigUnsigned x, BigUnsigned y, std::string filename) {
    
    std::ofstream file;
    file.open (filename);
    file << x << '\n';
    file << y;
    file.close();
    
    return;
}

BigUnsigned testE(BigUnsigned x, BigUnsigned y) {
    BigUnsigned irp = gcd(x, y);
    while(irp != 1) {
        x=x+2;
        testE(x, y);
        std::cout << x << std::endl << std::endl;
    }
    
    return x;
}

int main() {
	/* The library throws `const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a `try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	/*try {
		      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigInteger big1 = BigInteger(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigInteger big2 = BigInteger(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigInteger big3 = big1*big2;
      std::cout <<big3;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}
        */
        
        BigUnsigned p = BigUnsigned(1);
        p = generate(p);
        std::cout << "p: " << p << '\n';
        
        BigUnsigned q = BigUnsigned(1);
        q = generate(q);
        std::cout << "q: " << q << '\n';
        
        BigUnsigned a1 = BigUnsigned(2);
        BigUnsigned a2 = BigUnsigned(7);
        
        p = testPrime(p, a1);
        p = testPrime(p, a2);
        q = testPrime(q, a1);
        q = testPrime(q, a2);

        writeToFile(p, q, "p_q.txt");
        
        BigUnsigned n = p*q;
        BigUnsigned phi_n = (p-1)*(q-1);
        BigUnsigned e = 438727;
        e = testE(e, phi_n);
        std::cout << "e: " << e << '\n';
        
        BigUnsigned d = modinv(e, phi_n);
        std::cout << "d: " << d << '\n';
        
        writeToFile(e, n, "e_n.txt");
        writeToFile(d, n, "d_n.txt");
        
	return 0;
}

