import { Model, Mongoose } from "mongoose";
import { OptimizeRequestAttributes } from "../database/models/OptimizeRequest";
import { OptimizeResultAttributes } from "../database/models/OptimizeResult";

export interface DatabaseModels {
  [key: string]: Model<any>;
}

export interface Database {
  mongoose: Mongoose;
  OptimizeRequest: Model<OptimizeRequestAttributes>;
  OptimizeResult: Model<OptimizeResultAttributes>;
}
