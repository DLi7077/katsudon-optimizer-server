import express, { Router } from "express";
import { optimize } from "./resources";

const router: Router = express.Router();

router.get("/", optimize);

export default router;
