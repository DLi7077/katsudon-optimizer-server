import _ from "lodash";
import { Request, Response } from "express";
import { runOptimizer } from "../../utils";
import {
  BonusStatGain,
  CharacterStats,
  EnemyAttributes,
  StatPreference,
  TalentScaling,
  CharacterAttributes,
  CharacterEnemyRequest,
} from "interface";
import {
  DEFAULT_CHARACTER_STATS,
  DEFAULT_STAT_PREF,
  DEFAULT_ENEMY_STATS,
} from "../../constants/optimize";
import OptimizeService from "../../services/Optimize";

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
    ..._.get(req.body, "stat_preferences"),
  };

  const optimizeRequest: CharacterEnemyRequest = {
    character: {
      stats: characterStats,
      talent_scalings: characterTalents,
      bonus_stat_gain: bonusStatGains,
      stat_preferences: statPreferences,
    } as CharacterAttributes,
    enemy: enemyStats as EnemyAttributes,
  };

  await OptimizeService.create(optimizeRequest).then((created) => {
    res.status(200);
    res.json(created);
  });

  // console.log(optimizeRequest);
  // const result = await runOptimizer(JSON.stringify(optimizeRequest));

  // console.log(result);

  // res.status(200);
  // res.json(result);
}
