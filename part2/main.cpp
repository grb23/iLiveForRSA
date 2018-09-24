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
    /*
    string input = "grape    sha256('grape'):0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496";
    string output1 = sha256(input);
 
    cout << "sha256('"<< input << "'):" << output1 << endl;
    
    while(output1.empty() != 0) {
        string sub1 = output1.substr(16);
        cout << sub1 << '\n';
        BigInteger ;
        bint += stringToBigInteger(sub1);
     }*/
    
    ifstream message;
    message.open("message.txt");
    
    /*
    stringstream ss;
    ss << message.rdbuf();
    string s = ss.str();
    cout << s << '\n' << '\n';
     */
    
    string line_m;
    getline(message, line_m);
    string s = line_m;
    cout << "message: " << s << '\n' << '\n';
    
    string sha = sha256(s);
    cout << "hash: " << sha << '\n' << '\n';
    
    ifstream d_n;
    d_n.open("d_n.txt");
    
    //get d from Private Key
    string line;
    getline(d_n, line);
    string d = line;
    cout << "d: " << d << endl << endl;
    
    //get n from Private Key
    getline(d_n, line);
    string n = line;
    cout << "n: " << n << endl << endl;
    
    ifstream e_n;
    e_n.open("e_n.txt");
    
    //get e from Private Key
    getline(e_n, line);
    string e = line;
    cout << "e: " << e << endl << endl;
    
    ifstream p_q;
    p_q.open("p_q.txt");
    
    //get p from Public Key
    getline(p_q, line);
    string p = line;
    cout << "p: " << p << endl << endl;
    
    //get q from Public Key
    getline(p_q, line);
    string q = line;
    cout << "q: " << q << endl << endl;
    
    BigUnsigned d_BigUnsigned = stringToBigUnsigned(d);
    BigUnsigned e_BigUnsigned = stringToBigUnsigned(e);
    BigUnsigned n_BigUnsigned = stringToBigUnsigned(n);
    
    BigUnsigned p_BigUnsigned = stringToBigUnsigned(p);
    BigUnsigned q_BigUnsigned = stringToBigUnsigned(q);

    BigInteger sha_BigInteger = convertHash(sha, 0);
    cout << "sha big integer: " << sha_BigInteger << endl << endl;
    
    //decrypt message
    BigUnsigned M = modexp(sha_BigInteger, d_BigUnsigned, n_BigUnsigned);
    
    string M_string = bigUnsignedToString(M);
    
    ofstream M_file;
    M_file.open ("M_file.txt");
    M_file << M_string;
    M_file.close();
    
    cout << "M: " << M << endl << endl;
    cout << "M string: " << M_string << endl << endl;
    
   std::string filename = "M_file.txt";
   std::ifstream myfile (filename.c_str(), std::ios::binary);
   std::streampos begin,end;
   begin = myfile.tellg();
   myfile.seekg (0, std::ios::end);
   end = myfile.tellg();
   std::streampos size = end-begin; //size of the file in bytes   
   myfile.seekg (0, std::ios::beg);
   
   char * memblock = new char[size];
   myfile.read (memblock, size); //read the entire file
   memblock[size]='\0'; //add a terminator
   myfile.close();
   
   //check what's in the block
   string str(memblock);
   std::cout << str; 
   std::cout << "\nthe content " << endl << endl;
   
   //----------------------- add signature to the content and save
   std::string filename2 = filename+".signed";
   std::ofstream myfile2 (filename2.c_str(), std::ios::binary);
   myfile2.write (memblock, size);
   int sigLength = 1024;
   char * signature = new char[sigLength];
   string sig = "Gwendolyn";
   strcpy(signature, sig.c_str());
   myfile2.write (signature, sigLength); //write sig in a block of 1024 bytes
   
  //char oldname[] ="M_file.txt.signed";
  //char newname[] ="M_file_signed.txt";
  //myfile2 = rename(oldname , newname);
   
   string m_line;
   ifstream m_file_signed;
   
   ofstream outfile("M_file_signed.txt");
   outfile << myfile2;
   
   m_file_signed.open("M_file_signed.txt");
   
   getline(m_file_signed, m_line);
   string encrypted = m_line;
   
   cout << "encrypted: " << encrypted << endl << endl;

    std::cout << "signed at the end of the doc!\n \n";
    
    BigInteger encrypted_BigInteger = stringToBigInteger(encrypted);
    
    //"encrypt" saved hash value (signature) using the public key stored in e_n.txt
    BigUnsigned encrypted_sig =  modexp(encrypted_BigInteger, e_BigUnsigned, n_BigUnsigned);
    
    string encrypted_sig_string = bigIntegerToString(encrypted_sig);
    cout << "encrypted sig: " << encrypted_sig_string << endl << endl;
    
    //Compare the SHA-256 hash value and the “encrypted” signature
    if(sha != encrypted_sig_string) {
        cout << "The document has been modified!" << endl;
    }
    else
        cout << "The document is authentic!" << endl;
    
    M_file.close();
    d_n.close();
    e_n.close();
    p_q.close();
    myfile.close();
    
    
    return 0;
}
