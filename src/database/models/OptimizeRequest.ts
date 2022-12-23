import mongoose, { Schema, Model, ObjectId } from "mongoose";
import { CharacterAttributes, EnemyAttributes } from "interface";
import { STATUS, Status } from "../../constants/ProcessingStatus";

export interface OptimizeRequestAttributes {
  _id: ObjectId;
  character: CharacterAttributes;
  enemy: EnemyAttributes;
  status: Status;
  created_at: Date;
  processed_at?: Date;
  completed_at?: Date;
}

export type OptimizeRequestModelDefinition =
  Model<OptimizeRequestModelDefinition>;

export const OptimizeRequestSchema: Schema<OptimizeRequestAttributes> =
  new Schema({
    _id: {
      type: mongoose.Schema.Types.ObjectId,
      required: true,
      auto: true,
    },
    character: {
      type: Object,
      required: true,
    },
    enemy: {
      type: Object,
      required: true,
    },
    status: {
      type: String,
      enum: STATUS,
      required: true,
      default: STATUS.PENDING,
    },
    created_at: {
      type: Date,
      required: true,
      default: new Date(),
    },
    processed_at: {
      type: Date,
      required: false,
    },
    completed_at: {
      type: Date,
      required: false,
    },
  });

const OptimizeRequestModel: Model<OptimizeRequestAttributes> = mongoose.model(
  "Optimize Requests",
  OptimizeRequestSchema
);

export default OptimizeRequestModel;
