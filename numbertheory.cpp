#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
/**
Adam Rosenberg
Important grading note: You must solve this problem without using any library methods that your programming language provides for greatest common divisor, modular exponentiation, modular multiplicative inverse, primality testing, or RSA key generation.

Each line of input poses a question from number theory; your program must print the answer, as detailed below.

Input
Each line of input consists of a category followed by one or more integers. All integers are non-negative and are less than 231231. The five types of input lines are:

gcd a b, where a>0a>0 and b>0b>0.
exp x y N, where N>1N>1.
inverse a N, where N>a>0N>a>0.
isprime p, where p>5p>5.
key p q, where pp and qq are prime and p≠qp≠q.
Output
For each line of input, your program should produce a line of output, depending on the category:

gcd a b: Print the greatest common divisor of aa and bb.
exp x y n: Print xymodNxymodN, which must be non-negative and less than NN.
inverse a N: Print a−1(modN)a−1(modN), which must be positive and less than NN. If the inverse does not exist, print “none”.
isprime p: Print “yes” if pp passes the Fermat test for a=2a=2, a=3a=3, and a=5a=5; print “no” otherwise.
key p q: Print the modulus, public exponent, and private exponent of the RSA key pair derived from pp and qq. The public exponent must be the smallest positive integer that works; qq must be positive and less than N

**/


using namespace std;

unsigned long mod(unsigned long l, unsigned long r){
    if(l > 0) return l%r;
    else return -((-l)%r);

}

//return gcd of l and r
//long gcd(long l, long r){
//    if(r == 0)return l;
//    else return gcd(r, mod(l, r));
//}

long gcd(long l, long r){
    long temp;
    while(r > 0){
        temp = l % r;
        l = r;
        r = temp;
    }
    return l;
}
unsigned long exponentiation(unsigned long a, unsigned long b, unsigned long c) {
    unsigned long res = 1;
    a = a % c;
    do{
        if (b & 1){
            res = (res*a) % c;
        }
        b = b>>1;
        a = (a*a) % c;
    }while(b > 0);
    return res;
}

//euclids method. return is needed for recursion.
long euclids(long z, long x, long* l, long* r){
    if(x != 0){
        long l2 = 0;
        long r2 = 0;
        long rez = euclids(x,mod(z,x),&l2,&r2);
        *r = (l2 - (z/x)*r2);
        *l = r2;
        return rez;
    }
    else{
        *l = 1;
        *r = 0;
        return  z;
    }
}

//void because iterative. printing in this method.
long inverse(long base, long N){
    long l;
    long r;
    unsigned long x = euclids(base,N,&l,&r);
    if(x == 1){
        long result = (l % N + N) % N;
        return result;
//        cout <<  mod(l,N) << endl;
    }else{
        return -1;
    }
}

//generates a key for the two primes p and q. printing in this method.
void key(long p, long q){
    long n = p*q;
    long phi = (p-1)*(q-1);
    long e;
    long d;
    //find e
    for(int i = 2; i<1000; i++){
        if(gcd(i, phi) == 1){
            e = i;
            i = n;
            break;
        }
    }

    d = inverse(e, phi);
    //find d
//    for(int i = e; i < n; i++){
//        int dx = e*i;
//        if(mod(dx,phi) == 1){
//            d = i;
//            i = n;
//            break;
//        }
//    }
    cout << n << " " << e << " " << d <<endl;
}
//1 ≤ a < p:   a^(p-1) ≡ 1  (mod p)
// Print “yes” if pp passes the Fermat test for a=2, a=3, and a=5; print “no” otherwise.
void prime(long N){
    //cout << N << " " ;
    long e = N-1;
    if((exponentiation(2, e, N) == 1)
       && (exponentiation(3, e, N) == 1)
            && (exponentiation(5, e, N) == 1)){
            cout<<"yes" << endl;
    }else{
            cout << "no" << endl;
    }
}

void handleline(string inst, vector<string> instruction){
    long first, second, third;
    char * endstring;
    if(inst == "gcd"){
        first = strtol(instruction[1].c_str(),&endstring,10);
        second = strtol(instruction[2].c_str(),&endstring,10);
        cout << gcd(first, second) << endl;
    }else if(inst == "exp"){
        unsigned long f,s,t;
        f = strtoul(instruction[1].c_str(),&endstring,10);
        s = strtoul(instruction[2].c_str(),&endstring,10);
        t = strtoul(instruction[3].c_str(),&endstring,10);
        cout << exponentiation(f, s, t) << endl;
    }
    else if(inst == "inverse"){
        first = strtol(instruction[1].c_str(),&endstring,10);
        second = strtol(instruction[2].c_str(),&endstring,10);
        long z = inverse(first, second);
        if(z == -1){
            cout << "none" << endl;
        }else{
            cout << z << endl;
        }

    }
    else if(inst == "isprime"){
        first = strtol(instruction[1].c_str(),&endstring,10);
        prime(first);
    }
    else if(inst == "key"){
        first = strtol(instruction[1].c_str(),&endstring,10);
        second = strtol(instruction[2].c_str(),&endstring,10);
        key(first, second);
    }
}
int main(int argc, char** argv){
    string parse;
    while(getline(cin,parse)){
        stringstream ss(parse);
        string token;

        vector<string> instruction;
        while(getline(ss,token,' ')){
            instruction.push_back(token);
        }
        int i;
        handleline(instruction[0], instruction);
    }
    return 0;
}
