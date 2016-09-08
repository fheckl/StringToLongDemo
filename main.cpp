#include <sstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

/**
 * \brief The original implementation as we currently have it. The problem here is that parsing errors - e.g. when the value does not fit
 * into the desired type - are not detected.
 * The C++-11 standard (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf) falls back to storing the min or max value for the type
 * (depending on the parsed value) as can be seen in the example on page 1053.
 * Microsoft does not seem to follow the standard there since they leave the value untouched instead.
 * \param s the string to be parsed
 * \return the parsed value as determined by istringstream's >> operator
 */
long stringToLong(std::string s)
{
    std::istringstream is(s);
    long l = 0;
    is >> l;
    return l;
}

/**
 * \brief In this first improved version we test for errors after the stream operation. In case of errors the fallback value is returned.
 * \param s the string to be parsed
 * \param fallBack the value to be used in case of parsing errors
 * \return the parsed value as determined by istringstream's >> operator if it succeeds, the fallback value otherwise
 */
long stringToLongImproved1(string s, long fallBack = 60L)
{
    istringstream is(s);
    long l = 0;
    is >> l;

    // Check: Was the >> operation successful?
    if (is.fail()) return fallBack;

    return l;
}

/**
 * \brief The second improved version uses the method stol as present in more recent C++ standard libraries. stol throws an exception in case
 * of parsing errors so we can use this to return our fallback value.
 * \param s the string to be parsed
 * \param fallBack the value to be used in case of parsing errors
 * \return the parsed value as determined by stol if it succeeds, the fallback value otherwise
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
    // This is our test value which is too large to fit into a long variable
    string s("31536000000");

    // 1st try using our current function
    // MSVC++ returns 0 as the result while other modern compilers (g++, clang) adhere to standard and return the max long value
    auto result = stringToLong(s);
    cout << "Result (current function): " << result << endl;

    // 2nd try using the first improved version
    result = stringToLongImproved1(s);
    cout << "Result (improved v1): " << result << endl;

    // 3rd try using the second improved version
    result = stringToLongImproved2(s);
    cout << "Result (improved v2): " << result << endl;

    getchar();

    return 0;
}
