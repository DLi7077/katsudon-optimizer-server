#include "Parser.cpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "{ Usage: " << argv[0] << " json input ";
    return 0;
  }
  std::string arg1 = argv[1];

  Json::JsonObject input(arg1);

  Json::JsonObject characterJson = input["character"];
  Json::JsonObject enemyJson = input["enemy"];

  Character character = Parser::CreateCharacter(characterJson);
  Enemy enemy = Parser::CreateEnemy(enemyJson);

  character = Optimize::optimize(character, enemy);

  Json::JsonObject bestJson = character.toJSON();
  LOG(bestJson);

  /**
   * TODO:
   * Parse input to unordered_map representing JSON
   * Pass unordered_map into optimizer
   * Optimizer returns a JSON representation of the result
   * Print out JSON result
   */

  return 0;
}