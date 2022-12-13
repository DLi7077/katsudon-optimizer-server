import express from "express";
import { optimize } from "./resources.js";

const router = express.Router();

router.get("/", optimize);

export default router;
