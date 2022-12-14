#include "Parser.cpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "{ Usage: " << argv[0] << " json input ";
    return 0;
  }

  Json::JsonObject input(std::move(argv[1]));
  Json::JsonObject characterJson = input["character"];
  Json::JsonObject preferenceJson = characterJson["stat_preferences"];
  Json::JsonObject enemyJson = input["enemy"];
  double optimizeFilter = input["optimize_filter"].double_value();

  Character character = Parser::CreateCharacter(characterJson);
  Enemy enemy = Parser::CreateEnemy(enemyJson);
  Initial::StatPreference preference = Parser::CreateStatPreferences(preferenceJson);
  std::vector<std::vector<Artifact>> artifactPool = Initial::generateArtifactPool(preference);

  Character best = Optimize::optimize(character, enemy, artifactPool, optimizeFilter);
  Json::JsonObject result = Calculator::toJson(best, enemy);
  result["optimize_filter"] = Json::JsonObject(optimizeFilter);
  LOG(result);

  return 0;
}