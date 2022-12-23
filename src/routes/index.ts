import { Express } from "express";
import listEndpoints from "express-list-endpoints";
import OptimizeAPI from "./optimize";

export default async function generateRoutes(app: Express): Promise<void> {
  app.use("/api/optimizer", OptimizeAPI);
  console.table(listEndpoints(app));
}
