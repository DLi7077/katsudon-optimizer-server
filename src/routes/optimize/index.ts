import express, { Router } from "express";
import { createRequest, getRequest } from "./resources";

const router: Router = express.Router();

router.post("/", createRequest);
router.get("/", getRequest);

export default router;
