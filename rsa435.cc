// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool testPrime(BigUnsigned x, BigInteger a1, BigInteger a2) {
    
    BigUnsigned test = modexp(a1, x-1, x);
    
    if(test == 1) {
        test = modexp(a2, x-1, x);
        if(test == 1) {
            return true;
        }
    }
    return false;
}

BigUnsigned generate(BigUnsigned x, BigInteger a1, BigInteger a2) {
    
    while(1) {
        for(int i=0; i<278; i++) {
            x = (x*10) + (rand() % 10);
        }
        x = (x*10)+7;
        
        if(testPrime(x, a1, a2)) {
            break;
        }
        else
            x=BigUnsigned(1);
    }
    
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
        BigUnsigned q = BigUnsigned(1);
        BigInteger a1 = 2;
        BigInteger a2 = 7;
    
        p = generate(p, a1, a2);
        std::cout << "p: " << p << '\n';
    
        q = generate(q, a1, a2);
        std::cout << "q: " << q << '\n';
        std::cout << "gosh gordon, we done it" << '\n';
        
//        p = testPrime(p, a1);
//        p = testPrime(p, a2);
//        q = testPrime(q, a1);
//        q = testPrime(q, a2);

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

