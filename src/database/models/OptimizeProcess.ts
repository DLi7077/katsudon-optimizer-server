import mongoose, { Schema, Model, ObjectId } from "mongoose";

export interface OptimizeProcessAttributes {
  _id: ObjectId;
  request_id: ObjectId;
  created_at: Date;
  deleted_at?: Date;
}

export type OptimizeProcessModelDefinition =
  Model<OptimizeProcessModelDefinition>;

export const OptimizeProcessSchema: Schema<OptimizeProcessAttributes> =
  new Schema({
    _id: {
      type: mongoose.Schema.Types.ObjectId,
      required: true,
      auto: true,
    },
    request_id: {
      type: mongoose.Schema.Types.ObjectId,
      required: true,
    },
    created_at: {
      type: Date,
      required: true,
      default: new Date(),
    },
    deleted_at: {
      type: Date,
      required: false,
    },
  });

const OptimizeProcessModel: Model<OptimizeProcessAttributes> = mongoose.model(
  "Optimize Processes",
  OptimizeProcessSchema
);

export default OptimizeProcessModel;
