import { Express } from "express";
import listEndpoints from "express-list-endpoints";
import OptimizeAPI from "./optimize";
import database from "../database";
import * as dotenv from "dotenv";
import Models from "../database";

dotenv.config();

export default async function generateRoutes(app: Express): Promise<void> {
  app.use("/api/optimizer", OptimizeAPI);

  const uri: any = process.env.MONGODB_URI;
  Models.mongoose.connect(uri).then(
    () => {
      console.log("Connected to MongoDB!");
    },
    (err: any) => {
      console.log(`Couldnt connect to MongoDB...${err}`);
    }
  );
  console.table(listEndpoints(app));
}
