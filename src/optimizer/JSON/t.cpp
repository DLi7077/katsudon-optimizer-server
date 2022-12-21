#include "JSONObject.cpp"
#define LOGTHING(x) cout << x << "\n";

int main() {
  Json::JsonObject x("{\"a\":\"b\"}");

  Json::JsonObject r("100");
  LOG_LINE(r);
  LOG_LINE(x);
  x["b"] = Json::JsonObject();
  LOG_LINE(x);
  x["a"] = Json::JsonObject(x);
  x["a"]["a"] = Json::JsonObject(x);
  LOG_LINE(x);
}