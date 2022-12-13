import OptimizeAPI from "./optimize/index.js";

export default async function generateRoutes(app) {
  app.use("/api/optimizer", OptimizeAPI);
}
