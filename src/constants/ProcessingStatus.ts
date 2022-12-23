export enum STATUS {
  PENDING = "pending",
  IN_PROGRESS = "in progress",
  COMPLETE = "complete",
}

export type Status = STATUS.PENDING | STATUS.IN_PROGRESS | STATUS.COMPLETE;
