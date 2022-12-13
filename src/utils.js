import { spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

export async function runOptimizer() {
  console.log("working");
  return new Promise((resolve, reject) => {
    const script = process.env.SCRIPT ?? "./src/scripts/a.out";
    const optimize = spawn(script, ["input.txt", "output.txt"]);
    optimize.stdout.on("data", (data) => {
      console.log(data.toString());
    });

    resolve("success");
  });
}
