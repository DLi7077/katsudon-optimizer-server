#include <fstream>
#include <iostream>
#include <string>

#include "./JSONObject.cpp"
#define LOG(x) cout << x << "\n";
#define LOG_LIST(x) \
  for (auto v : x) cout << v << "\n";

using namespace std;
int main() {
  fstream jsonReader("./t.txt");
  string phrase;
  string jsonString;
  while (getline(jsonReader, phrase)) {
    jsonString += phrase;
  }

  // LOG(jsonString);

  // JsonObject obj(std::move(jsonString));
  // LOG(obj)

  JsonObject* nestedObject = new JsonObject(jsonString);
  // JsonObject* nestedObject = new JsonObject("\"b\"");
  LOG(*nestedObject);
  // JsonObject test(obj["test"]);
  // LOG(test << test.getType());

  // JsonObject t = test[0];
  // LOG(t);

  LOG("terminated");

  return 0;
}