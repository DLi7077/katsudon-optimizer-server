import cron from "node-cron";
import async, { AsyncFunction, AsyncResultCallback } from "async";
import _ from "lodash";
import OptimizeService from "../services/optimize-result";
import RequestService from "../services/optimize-requests";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import { ObjectId } from "mongoose";

const PROCESS_LIMIT = 20;
let processCount = 0;

function createGenerateResultTasks(
  requestIds: ObjectId[]
): AsyncFunction<any>[] {
  return _.map(
    requestIds,
    (requestId: ObjectId) =>
      async function (next: AsyncResultCallback<any>) {
        await OptimizeService.generateResult(requestId)
          .then(() => {
            processCount -= 1;
          })
          .catch(next);
      }
  );
}

// https://github.com/node-cron/node-cron
function schedule() {
  const secondInterval = 5;
  const everyThreeSeconds = `*/${secondInterval} * * * * *`;
  cron.schedule(everyThreeSeconds, () => {
    console.log(`running ${processCount} processes at`, new Date());
    if (processCount == PROCESS_LIMIT) return;

    const remainingBandwidth = PROCESS_LIMIT - processCount;
    RequestService.getPendingRequests(remainingBandwidth).then(
      (requests: OptimizeRequestAttributes[]) => {
        processCount += requests.length;
        const requestIds = _.map(
          requests,
          (request: OptimizeRequestAttributes) => _.get(request, "_id")
        );

        const completeRequestTasks = createGenerateResultTasks(requestIds);
        async.parallelLimit(completeRequestTasks, 5);
      }
    );
  });
}

const jobs = {
  schedule,
};
export default jobs;
