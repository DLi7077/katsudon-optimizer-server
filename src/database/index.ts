import mongoose from "mongoose";
import { Database } from "../types/db";
import Models from "./models";

const database: Database = {
  mongoose,
  OptimizeRequest: Models.OptimizeRequestModel,
  OptimizeResult: Models.OptimizeResultModel,
  OptimizeProcess: Models.OptimizeProcessModel,
};

export default database;
