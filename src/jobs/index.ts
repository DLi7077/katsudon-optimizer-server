import cron from "node-cron";
import async, { AsyncFunction, AsyncResultCallback } from "async";
import _ from "lodash";
import OptimizeService from "../services/optimize-result";
import RequestService from "../services/optimize-requests";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import { ObjectId } from "mongoose";

// https://github.com/node-cron/node-cron
function schedule() {
  const secondInterval = 5;
  const everyThreeSeconds = `*/${secondInterval} * * * * *`;

  const PROCESS_LIMIT = 10;
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
            .catch(async (err) => {
              console.log(err);
              await RequestService.setRequestError(requestId);
              processCount -= 1;
              next();
            });
        }
    );
  }
  cron.schedule(everyThreeSeconds, () => {
    if (processCount === PROCESS_LIMIT) return;

    const remainingBandwidth = PROCESS_LIMIT - processCount;
    RequestService.getPendingRequests(remainingBandwidth).then(
      (requests: OptimizeRequestAttributes[]) => {
        processCount += requests.length;
        console.log(`running ${processCount} processes at`, new Date());
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
