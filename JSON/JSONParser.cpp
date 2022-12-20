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

  JSON::Object obj(std::move(jsonString));

  // string test = obj["test"];

  JSON::Object test(obj["test"]);
  JSON::Object test1(test[0]);
  LOG(test1 << test1.getType());
  JSON::Object mom(test1["mom"]);

  LOG(mom << mom.getType());
  JSON::Object emptyMom(mom[0]);
  LOG(emptyMom << emptyMom.getType());
}