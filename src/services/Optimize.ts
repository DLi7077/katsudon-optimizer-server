import _ from "lodash";
import Models from "../database";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import {
  CharacterAttributes,
  CharacterEnemyRequest,
  EnemyAttributes,
} from "interface";
import { ObjectId } from "mongoose";
import { runOptimizer } from "../utils";
import { OptimizeResultAttributes } from "../database/models/OptimizeResult";
import { STATUS } from "../constants/ProcessingStatus";

import { NotFoundResponse } from "http-errors-response-ts/lib";

async function createRequest(
  request: CharacterEnemyRequest
): Promise<OptimizeRequestAttributes> {
  const optimizeRequest = {
    character: _.get(request, "character") as CharacterAttributes,
    enemy: _.get(request, "enemy") as EnemyAttributes,
  } as OptimizeRequestAttributes;

  return Models.OptimizeRequest.create(optimizeRequest);
}

async function requestExists(requestId: ObjectId): Promise<boolean> {
  const foundRequest: any = await Models.OptimizeRequest.exists({
    _id: requestId,
  });

  return !!foundRequest;
}

async function findRequestById(
  requestId: ObjectId
): Promise<OptimizeRequestAttributes | any> {
  const exists: boolean = await requestExists(requestId);
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  return Models.OptimizeRequest.findById(requestId);
}

async function findResultById(
  requestId: ObjectId
): Promise<OptimizeResultAttributes | any> {
  const exists: boolean = await requestExists(requestId);
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  return Models.OptimizeResult.findById(requestId);
}

async function setRequestProcessing(
  requestId: ObjectId
): Promise<OptimizeRequestAttributes | any> {
  const exists: boolean = await requestExists(requestId);
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  return await Models.OptimizeRequest.findOneAndUpdate(
    { _id: requestId },
    {
      status: STATUS.PROCESSING,
      processed_at: new Date(),
    },
    { upsert: true, new: true }
  );
}

async function setRequestComplete(
  requestId: ObjectId,
  resultId: ObjectId
): Promise<OptimizeRequestAttributes | any> {
  const exists: boolean = await requestExists(requestId);
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  return await Models.OptimizeRequest.findOneAndUpdate(
    { _id: requestId },
    {
      status: STATUS.COMPLETE,
      completed_at: new Date(),
      result_id: resultId,
    },
    { upsert: true, new: true }
  );
}

async function generateResult(
  requestId: ObjectId
): Promise<OptimizeResultAttributes> {
  const foundRequest = (await Models.OptimizeRequest.findById(
    requestId
  )) as OptimizeRequestAttributes;

  await setRequestProcessing(requestId);
  const computedResult: OptimizeResultAttributes = await runOptimizer(
    foundRequest
  );

  const generatedResult: OptimizeResultAttributes =
    await Models.OptimizeResult.create({
      ...computedResult,
      request_id: requestId,
    });

  await setRequestComplete(requestId, _.get(generatedResult, "_id"));

  return generatedResult;
}

export default {
  createRequest,
  findRequestById,
  findResultById,
  generateResult,
  setRequestProcessing,
  setRequestComplete,
};
