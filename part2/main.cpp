/***
compile and run (in linux):
g++ sha256.cpp main.cpp -o sha256_example && ./sha256_example
Output:
sha256('grape'): 0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

using std::string;
using std::cout;
using std::endl;

using namespace std;

void signFile(const char* file) {
    std::ifstream myfile (file, std::ios::binary);
    std::string data((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    if(data.empty()) {
        throw("Invalid file.");
    }
    myfile.close();

    string sha = sha256(data);
    cout << sha << endl;

    BigUnsigned sha_BigUnsigned = stringToBigUnsigned16(sha);
    cout << sha_BigUnsigned << endl;

    ifstream d_n;
    d_n.open("d_n.txt");
    string line;

    //get d from Private Key
    getline(d_n, line);
    string d = line;
    cout << "d: " << d << endl << endl;

    //get n from Private Key
    getline(d_n, line);
    string n = line;
    cout << "n: " << n << endl << endl;

    BigUnsigned d_BigUnsigned = stringToBigUnsigned10(d);
    BigUnsigned n_BigUnsigned = stringToBigUnsigned10(n);

    BigUnsigned M = modexp(sha_BigUnsigned, d_BigUnsigned, n_BigUnsigned);
    cout << "M: " << M << endl;

    ofstream M_file;
    M_file.open ("M_file.txt.signature");
    M_file << M << endl;
    M_file.close();
}

bool verifySig(const char* message, const char* signedFile) {
    std::ifstream file(message, std::ios::binary);
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if(data.empty()) {
        throw("invalid file");
    }
    file.close();
    
    string temp = sha256(data);
    cout << "temp: " << temp << endl;
    
    BigUnsigned temp_BigUnsigned = stringToBigUnsigned16(temp);
    cout << temp_BigUnsigned << endl;
    
    std::ifstream signedFileIn;
    signedFileIn.open(signedFile);
    
    string line;
    std::getline(signedFileIn, line);
    
    BigUnsigned sig_BigUnsigned = stringToBigUnsigned10(line);
    cout << "sig_BigUnsigned: " << sig_BigUnsigned << endl;
    signedFile.close();
    
    ifstream e_n;
    e_n.open("e_n.txt");
    
    //get e from Public Key
    getline(e_n, line);
    string e = line;
    cout << "e: " << e << endl << endl;
    
    //get n from Public Key
    getline(e_n, line);
    string n = line;
    cout << "n: " << n << endl << endl;
    
    BigUnsigned e_BigUnsigned = stringToBigUnsigned10(e);
    BigUnsigned n_BigUnsigned = stringToBigUnsigned10(n);
    
    e_n.close();
    
    sig_BigUnsigned decrypt = modexp(sig_BigUnsigned, e_BigUnsigned, n_BigUnsigned);
    cout << "decrypt: " << decrypt << endl;
    
    if(decrypt == temp_BigUnsigned) {
        return true;
    }
    else
        return false;
}

int numDigits(int number)
{
    int digits = 0;
    
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

BigInteger convertHash(string hash, int pos) {

    BigInteger b = BigInteger(0);
    
    for (int i=0;i<hash.length();i++) {
        int a = hash[i];
        //cout<< "a: " << a << endl;
        int len = numDigits(a);
        for(int i = 0; i<len; i++) {
            b = b*10;
        }
        string a_string = to_string(a);
        b.operator +=(stringToBigInteger(a_string));
        //cout << b << endl;
    }
    
    return b;
}
 
int main(int argc, char *argv[])
{
    
    try {
        if(*argv[1] == 's') {
            signFile(argv[2]);
        }
        
        else if(*argv[1] == 'v') {
            if(verifySig(argv[2], argv[3])) {
                cout << "***The file is valid.***" << endl;
            }
            else {
                cout << "***File has been modified!***" << endl;
            }
        }
        else {
            cout << "Please enter a valid action. 's' to sign or 'v' to verify." << endl;
        }
    }
    catch (string errorMessage) {
        cout << errorMessage << endl;
    }
    
    return 0;
}
