#include "Parser.cpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "{ Usage: " << argv[0] << " json input ";
    return 0;
  }
  Json::JsonObject input(std::move(argv[1]));
  Json::JsonObject characterJson = input["character"];
  Json::JsonObject enemyJson = input["enemy"];

  Character character = Parser::CreateCharacter(characterJson);
  Enemy enemy = Parser::CreateEnemy(enemyJson);

  Character best = Optimize::optimize(character, enemy, 50);
  Json::JsonObject result = Calculator::toJson(best, enemy);
  LOG(result);

  return 0;
}