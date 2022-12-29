export enum STATUS {
  PENDING = "pending",
  PROCESSING = "processing",
  COMPLETE = "complete",
  ERROR = "error",
}

export type Status =
  | STATUS.PENDING
  | STATUS.PROCESSING
  | STATUS.COMPLETE
  | STATUS.ERROR;
