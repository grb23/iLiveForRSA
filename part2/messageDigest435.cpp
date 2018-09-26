/***
 prepared for CS435 Project 1 part 2
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
    std::string messageContent((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    if(messageContent.empty()) {
        //don't attempt to encrypt empty files
        throw("Invalid file.");
    }
    myfile.close();
    
    string sha = sha256(messageContent);
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
    M_file.open ("M_file.txt.signed");
    M_file << M << endl;
    M_file.close();
}

bool verifySig(const char* message, const char* signedFile) {
    std::ifstream file(message, std::ios::binary);
    std::string messageContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if(messageContent.empty()) {
        throw("invalid file");
    }
    file.close();
    
    string messageContentHash = sha256(messageContent);
    cout << "messageContentHash: " << messageContentHash << endl;
    
    BigUnsigned messageContentHash_BigUnsigned = stringToBigUnsigned16(messageContentHash);
    cout << "messageContentHash_BigUnsigned: " << messageContentHash_BigUnsigned << endl;
    
    std::ifstream signedFileIn;
    signedFileIn.open(signedFile);
    
    string line;
    std::getline(signedFileIn, line);
    
    BigUnsigned sig_BigUnsigned = stringToBigUnsigned10(line);
    cout << "sig_BigUnsigned: " << sig_BigUnsigned << endl;
    signedFileIn.close();
    
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
    
    BigUnsigned decrypt = modexp(sig_BigUnsigned, e_BigUnsigned, n_BigUnsigned);
    cout << "decrypt: " << decrypt << endl;
    
    if(decrypt == messageContentHash_BigUnsigned) {
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
    /*
     //demonstrating how sha256 works
     std::string input = "testing";
     std::string output1 = sha256(input);
     std::cout << "sha256('"<< input << "'):" << output1 << "\n";
     
     //demo bigInt works here
     BigUnsigned a = stringToBigUnsigned("124338907642982722929222542626327282");
     BigUnsigned b = stringToBigUnsigned("124338907642977775546469426263278643");
     std::cout << "big a = " <<a<<"\n";
     std::cout << "big b = " <<b<<"\n";
     std::cout << "big a*b = " <<a*b<<"\n";
     
     //Second part of your project starts here
     if (argc != 3 || (argv[1][0]!='s' && argv[1][0]!='v'))
     std::cout << "wrong format! should be \"a.exe s filename\"";
     else {
     std::string filename = argv[2];
     
     
     //read the file
     std::streampos begin,end;
     std::ifstream myfile (filename.c_str(), std::ios::binary);
     begin = myfile.tellg();
     myfile.seekg (0, std::ios::end);
     end = myfile.tellg();
     std::streampos size = end-begin;
     //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
     
     myfile.seekg (0, std::ios::beg);
     char * memblock = new char[size];
     myfile.read (memblock, size); //read file; it's saved in the char array memblock
     myfile.close();
     
     std::string copyOFfile = filename+".Copy";
     std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
     myfile2.write (memblock, size); //write to a file
     myfile2.close();
     
     //std::cout<<memblock;
     
     if (argv[1][0]=='s') {
     std::cout << "\n"<<"Need to sign the doc.\n";
     //.....
     
     }
     else {
     std::cout << "\n"<<"Need to verify the doc.\n";
     //.....
     
     }
     delete[] memblock;
     }
     */
    
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
