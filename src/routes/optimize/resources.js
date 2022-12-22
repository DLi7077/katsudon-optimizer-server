import _ from "lodash";
import {
  DEFAULT_CHARACTER_STATS,
  DEFAULT_ENEMY_STATS,
} from "../../constants/optimize.js";
import { runOptimizer } from "../../utils.js";

export async function optimize(req, res) {
  const characterStats = {
    ...DEFAULT_CHARACTER_STATS,
    ..._.get(req.body, "character"),
  };
  const enemyStats = {
    ...DEFAULT_ENEMY_STATS,
    ..._.get(req.body, "enemy"),
  };

  const variables = {
    character: characterStats,
    enemy: enemyStats,
  };
  const result = await runOptimizer(JSON.stringify(variables)).then((result) =>
    JSON.parse(result)
  );

  console.log(result);

  res.status(200);
  res.json(result);
}
