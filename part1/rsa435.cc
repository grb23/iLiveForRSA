// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

//Test if is prime
bool isPrime(BigUnsigned x, BigInteger a1, BigInteger a2) {
    
    //Initialize for testing
    BigUnsigned testPrime = modexp(a1, x-1, x);
    
    if(testPrime == 1) {
        testPrime = modexp(a2, x-1, x);
        if(testPrime == 1) {
            //Passes both tests, is a prime
            return true;
        }
    }
    //Failed, is not a prime
    return false;
}

//Generate large primes p and q
BigUnsigned generate(BigUnsigned x, BigInteger a1, BigInteger a2) {
    
    while(1) {
        for(int i=0; i<278; i++) {
            //Start with random large number
            x = (x*10) + (rand() % 10);
        }
        //Make sure last digit is a 7
        x = (x*10)+7;
        
        //If it is prime, break and return
        if(isPrime(x, a1, a2)) {
            break;
        }
        else
            //If it is not prime, start over
            x=BigUnsigned(1);
    }
    
    return x;
}

//Store in a file
void writeToFile(BigUnsigned x, BigUnsigned y, std::string filename) {
    
    std::ofstream file;
    file.open (filename);
    file << x << '\n';
    file << y;
    file.close();
    
    return;
}

//Test that e is relatively prime to phi of n
bool testE(BigUnsigned e, BigUnsigned phi_n) {
    BigUnsigned r = gcd(e, phi_n);
    //GCD of e and phi of n must be one
    while(r != 1) {
        //Skip all even numbers
        e=e+2;
        testE(e, phi_n);
//        std::cout << "e: " << e << std::endl << std::endl;
        //reset remainder and check new e
        r = gcd(e, phi_n);
    }
    //e is relatively prime
    return true;
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
    
        //Initialize p and q
        BigUnsigned p = BigUnsigned(1);
        BigUnsigned q = BigUnsigned(1);
        //Pick two a values to test p and q
        BigInteger a1 = 2;
        BigInteger a2 = 7;
    
        //Generate large prime p
        p = generate(p, a1, a2);
        std::cout << "p: " << p << '\n';
    
        //Generate large prime q
        q = generate(q, a1, a2);
        std::cout << "q: " << q << '\n';

        //Store p and q
        writeToFile(p, q, "p_q.txt");
    
        //Compute n from p and q
        BigUnsigned n = p*q;
        std::cout << "n: " << n << '\n';
        //Compute phi of n from p and q
        BigUnsigned phi_n = (p-1)*(q-1);
        BigUnsigned e = 65537;
        //Test that e is relatively prime to phi of n
        testE(e, phi_n);
        std::cout << "e: " << e << '\n';
    
        //Compute public key d from e and phi of n
        BigUnsigned d = modinv(e, phi_n);
        std::cout << "d: " << d << '\n';
    
        //Store private and public keys
        writeToFile(e, n, "e_n.txt");
        writeToFile(d, n, "d_n.txt");
        
	return 0;
}

