#include <sstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

/**
 * Das ist die Methode, wie sie bisher bei uns implementiert ist.
 * Problem dabei: Parsing-Fehler - insbesondere wenn der zu parsende Wert zu groß ist - werden nicht erkannt. 
 * Der C++-Standard (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf) 
 * sieht für diesen Fall vor (im Beispiel auf Seite 1053), dass in l der maximale oder minimale (je nach Ausgangswert) Wert
 * des definierten Typs steht.
 * Microsoft weicht davon ab und belässt entweder den von uns vorher gesetzten Wert in der Variablen oder aber sie setzen ihn
 * explizit auf 0 (ich habe es nicht genauer geprüft).
 */ 
long stringToLong(std::string s)
{
    std::istringstream is(s);
    long l = 0;
    is >> l;
    return l;
}

/**
 * In dieser ersten verbesserten Version wird nach dem Lesen aus dem Stream überprüft, ob es dabei zu einem Fehler kam und - falls
 * das der Fall ist - wird der Fallback-Wert zurückgegeben.
 */ 
long stringToLongImproved1(string s, long fallBack = 60L)
{
    istringstream is(s);
    long l = 0;
    is >> l;

    // Nachprüfen: Ging die >>-Operation denn gut?
    if (is.fail()) return fallBack;

    return l;
}

/**
 * In dieser zweiten verbesserten Version wird die in neueren C++-Versionen definierte Methode stol zum Paresen verwendet.
 * Diese wirft eine Exception, wenn der gelesene Wert nicht in der Variablen (bzw. deren Typ) untergebracht werden kann, woraufhin
 * wir wieder den Fallback-Wert zurückgeben.
 */ 
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
