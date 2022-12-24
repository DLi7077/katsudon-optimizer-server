import _ from "lodash";
import { Request, Response } from "express";
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
import OptimizeService from "../../services/optimize-result";
import RequestService from "../../services/optimize-requests";
import { ObjectId } from "mongoose";

export async function createRequest(
  req: Request,
  res: Response
): Promise<void> {
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

  await RequestService.createRequest(optimizeRequest).then((created) => {
    res.status(200);
    res.json(created);
  });
}

export async function getRequest(req: Request, res: Response): Promise<void> {
  const requestId: any | ObjectId = _.get(req.query, "id");
  await RequestService.findRequestById(requestId).then((request) => {
    res.status(200);
    res.json(request);
  });
}

export async function getResult(req: Request, res: Response): Promise<void> {
  const resultId: any | ObjectId = _.get(req.query, "id");
  await OptimizeService.findResultById(resultId).then((result) => {
    res.status(200);
    res.json(result);
  });
}
