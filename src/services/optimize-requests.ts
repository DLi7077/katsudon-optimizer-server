import _ from "lodash";
import Models from "../database";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import {
  CharacterAttributes,
  CharacterEnemyRequest,
  EnemyAttributes,
} from "interface";
import { ObjectId, SortOrder } from "mongoose";
import { STATUS } from "../constants/ProcessingStatus";

import { NotFoundResponse } from "http-errors-response-ts/lib";

/**
 * @description creates a request
 * @param {OptimizeRequestAttributes} request - the request to create
 * @returns {Promise<OptimizeRequestAttributes>} Promise of created request
 */
async function createRequest(
  request: CharacterEnemyRequest
): Promise<OptimizeRequestAttributes> {
  const optimizeRequest = {
    character: _.get(request, "character") as CharacterAttributes,
    enemy: _.get(request, "enemy") as EnemyAttributes,
  } as OptimizeRequestAttributes;

  return Models.OptimizeRequest.create({
    ...optimizeRequest,
    created_at: new Date(),
  });
}

/**
 * @description checks if requestId exists
 * @param {ObjectId} requestId - the request_id to check for
 * @returns {Promise<boolean>} Promise of id existing
 */
async function requestExists(requestId: ObjectId): Promise<boolean> {
  const foundRequest: any = await Models.OptimizeRequest.exists({
    _id: requestId,
  });

  return !!foundRequest;
}

/**
 * @description returns a request document
 * @param {ObjectId} requestId - the request_id to check for
 * @returns {Promise<OptimizeRequestAttributes>} Promise of the fetched request
 */
async function findRequestById(
  requestId: ObjectId
): Promise<OptimizeRequestAttributes | any> {
  const exists: boolean = await requestExists(requestId);
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  const foundRequest = await Models.OptimizeRequest.findById(
    requestId
  ).populate("result");

  return foundRequest;
}

/**
 * @description returns a list of pending requests
 * @param {number} limit - the max amount of requests to query for, defaults to 20
 * @returns {Promise<OptimizeRequestAttributes[]>} Promise of a list of pending requests
 */
async function getPendingRequests(
  limit: number = 20
): Promise<OptimizeRequestAttributes[]> {
  const ASCENDING: SortOrder = 1;
  const pendingRequests: OptimizeRequestAttributes[] =
    await Models.OptimizeRequest.find({
      status: STATUS.PENDING,
    })
      .sort({ created_at: ASCENDING })
      .limit(limit);

  return pendingRequests;
}

/**
 * @description Sets a request's computation status to complete
 * deletes the request from the process table
 * @param {ObjectId} requestId - id of the completed request
 * @returns {Promise<OptimizeResultAttributes>} Promise of the updated request
 */
async function setRequestError(
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
      status: STATUS.ERROR,
      processed_at: new Date(),
    },
    { upsert: true, new: true }
  );
}

/**
 * @description Sets a request's computation status to complete
 * deletes the request from the process table
 * @param {ObjectId} requestId - id of the completed request
 * @returns {Promise<OptimizeResultAttributes>} Promise of the updated request
 */
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

/**
 * @description Sets a request's computation status to complete
 * deletes the request from the process table
 * @param {ObjectId} requestId - id of the completed request
 * @param {ObjectId} resultId - id of the completed result
 * @returns {Promise<OptimizeResultAttributes>} Promise of the updated request
 */
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
      result: resultId,
    },
    { upsert: true, new: true }
  );
}

export default {
  createRequest,
  findRequestById,
  setRequestProcessing,
  setRequestComplete,
  setRequestError,
  getPendingRequests,
};
