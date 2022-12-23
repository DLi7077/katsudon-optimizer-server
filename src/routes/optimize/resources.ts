import _ from "lodash";
import { Request, Response } from "express";
import {
  DEFAULT_CHARACTER_STATS,
  DEFAULT_STAT_PREF,
  DEFAULT_TALENT_SCALING,
  DEFAULT_BONUS_STAT_GAINS,
  DEFAULT_ENEMY_STATS,
} from "../../constants/optimize";
import { runOptimizer } from "../../utils";
import {
  BonusStatGain,
  CharacterStats,
  EnemyAttributes,
  StatPreference,
  TalentScaling,
} from "interface";

export async function optimize(req: Request, res: Response) {
  const characterStats: CharacterStats = {
    ...DEFAULT_CHARACTER_STATS,
    ..._.get(req.body, "character.stats"),
  };

  const characterTalents: TalentScaling[] = _.get(
    req.body,
    "character.talent_scalings"
  );

  const bonusStatGains: BonusStatGain[] = _.get(
    req.body,
    "character.bonus_stat_gain"
  );

  const enemyStats: EnemyAttributes = {
    ...DEFAULT_ENEMY_STATS,
    ..._.get(req.body, "enemy"),
  };

  const statPreferences: StatPreference = {
    ...DEFAULT_STAT_PREF,
    ...(_.get(req.body, "stat_preferences") ?? {}),
  };

  const variables = {
    character: {
      stats: characterStats,
      talent_scalings: characterTalents,
      bonus_stat_gain: bonusStatGains,
    },
    enemy: enemyStats,
    stat_preferences: statPreferences,
  };

  console.log(variables);
  const result = await runOptimizer(JSON.stringify(variables));

  console.log(result);

  res.status(200);
  res.json(result);
}
