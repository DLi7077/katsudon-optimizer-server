import { runOptimizer } from "./utils.js";
import generateRoutes from "./routes/index.js";

import express from "express";
import cors from "cors";
import bodyParser from "body-parser";

const app = express();
app.use(cors({ origin: "*" }));
app.use(bodyParser.json());

const port = process.env.PORT || 5000;

app.listen(port, async () => {
  console.log(`Express listening at port ${port}`);
  console.log(`Test apis with http://localhost:${port}/api`);
});

generateRoutes(app)

// setInterval(() => {
//   runOptimizer();
// }, 1000);
