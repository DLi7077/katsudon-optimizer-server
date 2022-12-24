export enum STATUS {
  PENDING = "pending",
  PROCESSING = "processing",
  COMPLETE = "complete",
}

export type Status = STATUS.PENDING | STATUS.PROCESSING | STATUS.COMPLETE;
