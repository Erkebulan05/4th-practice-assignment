#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Function to calculate modular exponentiation
int modularExponentiation(int base, int exponent, int modulus)
{
    int result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Function to calculate greatest common divisor (GCD)
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to generate random prime number
int generatePrime()
{
    int num;
    bool isPrime = false;
    while (!isPrime)
    {
        num = rand() % 26 + 1;  // Generate a random number between 1 and 26
        isPrime = true;
        for (int i = 2; i <= sqrt(num); ++i)
        {
            if (num % i == 0)
            {
                isPrime = false;
                break;
            }
        }
    }
    return num;
}

// Function to generate RSA keys
void generateRSAKeys(int& e, int& d, int& n)
{
    srand(time(NULL));

    // Step 1: Generate two distinct prime numbers
    int p = generatePrime();
    int q = generatePrime();
    
    // Step 2: Calculate n
    n = p * q;

    // Step 3: Calculate the totient function
    int phi = (p - 1) * (q - 1);

    // Step 4: Find e such that 1 < e < phi and gcd(e, phi) = 1
    do {
        e = rand() % (phi - 2) + 2;
    } while (gcd(e, phi) != 1);

    // Step 5: Calculate d such that d ≡ e^(-1) (mod phi)
    d = modularExponentiation(e, phi - 1, phi);
}

// Function to encrypt a word using RSA
vector<int> encrypt(const string& word, int e, int n)
{
    vector<int> encrypted;
    for (char c : word)
    {
        int letter = c - 'a' + 1;  // Map each letter to its position in the alphabet (a=1, b=2, ..., z=26)
        int encryptedLetter = modularExponentiation(letter, e, n);
        encrypted.push_back(encryptedLetter);
    }
    return encrypted;
}

// Function to decrypt a word using RSA
string decrypt(const vector<int>& encrypted, int d, int n)
{
    string decrypted;
    for (int letter : encrypted)
    {
        int decryptedLetter = modularExponentiation(letter, d, n);
        char c = decryptedLetter - 1 + 'a';  // Map the decrypted position back to the corresponding letter
        decrypted.push_back(c);
    }
    return decrypted;
}

int main()
{
    int e, d, n;
    generateRSAKeys(e, d, n);
    
    string word;
    cout << "Enter a word to encrypt: ";
    cin >> word;
    
    vector<int> encrypted = encrypt(word, e, n);
    
    cout << "Encrypted: ";
    for (int letter : encrypted)
    {
        cout << letter << " ";
    }
    cout << endl;
    
    string decrypted = decrypt(encrypted, d, n);
    
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
