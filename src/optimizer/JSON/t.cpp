#include "JSONObject.cpp"

int main() {
  Json::JsonObject x("{\"a\":\"b\"}");
  Json::JsonObject r("100");
  LOG_LINE(r);
  LOG_LINE(x);

  LOG_LINE("assigning x[a] as " << r);

  LOG_LINE(x["a"]);
  x["a"] = std::move(r);
  LOG_LINE(x);
}