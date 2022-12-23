import mongoose from "mongoose";
import { Database } from "../types/db";
import Models from "./models";

const database: Database = {
  mongoose,
  OptimizeRequest: Models.OptimizeRequestModel,
};

export default database;
