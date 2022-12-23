import express, { Router } from "express";
import { optimize } from "./resources";

const router: Router = express.Router();

router.post("/", optimize);

export default router;
