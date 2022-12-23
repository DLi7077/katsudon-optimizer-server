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

  // std::array<std::string, SUBSTAT_COUNT> substats = {
  //     ENERGY_RECHARGE,
  //     ENERGY_RECHARGE,
  //     ENERGY_RECHARGE,
  //     ENERGY_RECHARGE,
  // };

  // Artifact test(substats, ATK_PERCENT);

  // character.addArtifact(test);

  Character best = Optimize::optimize(character, enemy);

  Json::JsonObject result = Calculator::toJson(best, enemy);
  LOG(result);

  // Json::JsonObject result = Calculator::toJson(character, enemy);
  // LOG(result);

  /**
   * TODO:
   * Parse input to unordered_map representing JSON
   * Pass unordered_map into optimizer
   * Optimizer returns a JSON representation of the result
   * Print out JSON result
   */

  return 0;
}