import _ from "lodash";
import Models from "../database";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import {
  CharacterAttributes,
  CharacterEnemyRequest,
  EnemyAttributes,
} from "interface";
async function create(
  request: CharacterEnemyRequest
): Promise<OptimizeRequestAttributes> {
  const optimizeRequest = {
    character: _.get(request, "character") as CharacterAttributes,
    enemy: _.get(request, "enemy") as EnemyAttributes,
  } as OptimizeRequestAttributes;

  return Models.OptimizeRequest.create(optimizeRequest);
}

export default {
  create,
};
