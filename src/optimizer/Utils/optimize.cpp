#include "../Constants/constants.h"
#include "../Game/Character/Character.h"
#include "../Game/DamageCalculator.cpp"
#include "./initializer.cpp"

namespace Optimize {

Character optimize(
    Character& character,
    Enemy& enemy,
    std::vector<std::vector<Artifact>>& artifactPool,
    size_t optimizeFilter = 20) {

  // permit to refer to variables in external scope
  // https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
  auto DamageComparator = [&](Character a, Character b) {
    double damageA = Calculator::damageOutput(a, enemy);
    double damageB = Calculator::damageOutput(b, enemy);
    return damageA > damageB;
  };

  const size_t limit = optimizeFilter;
  std::vector<Character> population = {character};

  // https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
  std::priority_queue<
      Character,
      std::vector<Character>,
      decltype(DamageComparator)>
      minHeap(DamageComparator);

  for (std::vector<Artifact>& artifactPiece : artifactPool) {
    for (Character& character : population) {
      for (Artifact& artifact : artifactPiece) {
        Character curr = character;
        curr.addArtifact(artifact);
        minHeap.push(curr);

        if (minHeap.size() > limit) {
          minHeap.pop();
        }
      }
    }

    // natural selection, top damage characters go to next stage
    population.clear();
    while (minHeap.size()) {
      population.push_back(minHeap.top());
      minHeap.pop();
    }
  }

  Character best = population.back();

  return best;
}
}  // namespace Optimize