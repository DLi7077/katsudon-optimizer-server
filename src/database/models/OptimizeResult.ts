import mongoose, { Schema, Model, ObjectId } from "mongoose";
import { OptimizedCharacterResult, Analysis } from "interface";

export interface OptimizeResultAttributes {
  _id: ObjectId;
  character: OptimizedCharacterResult;
  analysis: Analysis;
  created_at: Date;
  request_id: ObjectId;
}

export type OptimizeResultModelDefinition =
  Model<OptimizeResultModelDefinition>;

export const OptimizeResultSchema: Schema<OptimizeResultAttributes> =
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
    analysis: {
      type: Object,
      required: true,
    },
    created_at: {
      type: Date,
      required: true,
      default: new Date(),
    },
    request_id: {
      type: mongoose.Schema.Types.ObjectId,
      required: true,
    },
  });

const OptimizeResultModel: Model<OptimizeResultAttributes> = mongoose.model(
  "Optimize Results",
  OptimizeResultSchema
);

export default OptimizeResultModel;
