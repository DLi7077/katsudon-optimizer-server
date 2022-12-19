#include <fstream>
#include <iostream>
#include <string>

#include "./JSONObject.h"
#define LOG(x) cout << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) cout << v << "\n";

using namespace std;
int main() {
  fstream jsonReader("./t.txt");
  unordered_map<string, string> object;
  string phrase;
  string jsonString;
  while (getline(jsonReader, phrase)) {
    jsonString += phrase;
  }

  JSONObject obj(std::move(jsonString));

  LOG(obj);

}