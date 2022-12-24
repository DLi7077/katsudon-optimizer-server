import _ from "lodash";
import Models from "../database";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import { ObjectId } from "mongoose";
import { runOptimizer } from "../utils";
import { OptimizeResultAttributes } from "../database/models/OptimizeResult";
import { NotFoundResponse } from "http-errors-response-ts/lib";

import RequestService from "./optimize-requests";

/**
 * @description returns a request document
 * @param {ObjectId} resultId - the result_id to check for
 * @returns {Promise<OptimizeResultAttributes>} Promise of the fetched result
 */
async function findResultById(
  resultId: ObjectId
): Promise<OptimizeResultAttributes | any> {
  const exists = await Models.OptimizeResult.exists({ _id: resultId });
  if (!exists) {
    const error = new NotFoundResponse("No Object Id found");
    return error;
  }

  return Models.OptimizeResult.findById(resultId);
}

/**
 * @description runs the optimizer algorithm script on the request
 * creates a result document after successful computation
 * @param {ObjectId} requestId - the request_id document to compute
 * @returns {Promise<OptimizeResultAttributes>} Promise of a created result document
 */
async function generateResult(
  requestId: ObjectId
): Promise<OptimizeResultAttributes> {
  const foundRequest = (await Models.OptimizeRequest.findById(
    requestId
  )) as OptimizeRequestAttributes;

  await RequestService.setRequestProcessing(requestId);
  const computedResult: OptimizeResultAttributes = await runOptimizer(
    foundRequest
  );

  const generatedResult: OptimizeResultAttributes =
    await Models.OptimizeResult.create({
      ...computedResult,
      request: requestId,
      created_at: new Date(),
    });

  await RequestService.setRequestComplete(
    requestId,
    _.get(generatedResult, "_id")
  );

  return generatedResult;
}

export default {
  findResultById,
  generateResult,
};
