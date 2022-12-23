import mongoose from "mongoose";
import { Database } from "../types/db";
import OptimizeRequestModel from "./models/OptimizeRequest";

const database: Database = {
  mongoose,
  OptimizeRequest: OptimizeRequestModel,
};

export default database;
