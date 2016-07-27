#include <sstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

long stringToLong(std::string s)
{
    std::istringstream is(s);
    long l = 0;
    is >> l;
    return l;
}

long stringToLongImproved1(string s, long fallBack = 60L)
{
    istringstream is(s);
    long l = 0;
    is >> l;

    // Nachprüfen: Ging die >>-Operation denn gut?
    if (is.fail()) return fallBack;

    return l;
}

long stringToLongImproved2(string s, long fallBack = 60L)
{
    try {
        auto l = stol(s);
        return l;
    }
    catch (...)
    {
        return fallBack;
    }
}

int main() {
    // Stream >>-Operator siehe: C++11-Standard (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf) Seite 1053
    // Dieser Wert stand z. B. so in der Datenbank und wurde mit stringToLong verarbeitet
    string s("31536000000");

    // 1. Versuch: bisherige Methode
    // MSVC++ liefert hier 0 als Ergebnis, während andere moderne Compiler - dem Standard folgend - je nach Situation den max. oder min. Wert von long liefern
    auto ergebnis = stringToLong(s);
    cout << "Ergebnis (eigen): " << ergebnis << endl;

    // 2. Versuch: bisherige Methode mit Fehlerbehandlung
    ergebnis = stringToLongImproved1(s);
    cout << "Ergebnis (eigen mit Fehlerbehandlung): " << ergebnis << endl;

    // 3. Versuch: stol mit Fallback
    ergebnis = stringToLongImproved2(s);
    cout << "Ergebnis (stol mit Fallback): " << ergebnis << endl;

    getchar();

    return 0;
}
