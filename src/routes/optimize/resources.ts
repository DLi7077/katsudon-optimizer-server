import _ from "lodash";
import { Request, Response } from "express";
import {
  DEFAULT_CHARACTER_STATS,
  DEFAULT_ENEMY_STATS,
  DEFAULT_STAT_PREF,
} from "../../constants/optimize";
import { runOptimizer } from "../../utils";

export async function optimize(req: Request, res: Response) {
  const characterStats = {
    ...DEFAULT_CHARACTER_STATS,
    ..._.get(req.body, "character"),
  };
  const enemyStats = {
    ...DEFAULT_ENEMY_STATS,
    ..._.get(req.body, "enemy"),
  };
  const statPreferences = {
    ...DEFAULT_STAT_PREF,
    ...(_.get(req.body, "stat_preferences") ?? {}),
  };

  const variables = {
    character: characterStats,
    enemy: enemyStats,
    stat_preferences: statPreferences,
  };
  const result = await runOptimizer(JSON.stringify(variables));

  console.log(result);

  res.status(200);
  res.json(result);
}
