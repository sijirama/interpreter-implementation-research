#include <any>
#include <string>

using namespace std;

string substring(const string& str, int beginIndex, int endIndex);
string substring(const string& str, int beginIndex);

template <typename T> T castAny(std::any value);
