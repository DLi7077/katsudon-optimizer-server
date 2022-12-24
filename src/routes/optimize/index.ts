import express, { Router } from "express";
import { createRequest, getRequest, getResult } from "./resources";

const router: Router = express.Router();

router.post("/request/create", createRequest);
router.get("/request", getRequest);
router.get("/result", getResult);

export default router;
