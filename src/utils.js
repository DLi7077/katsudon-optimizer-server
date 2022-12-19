import { spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

export async function runOptimizer(jsonString) {
  console.log("working");

  const compile = "g++ -g -std=c++17 -Wall .JSONParser.cpp -o parser";

  const result = await ExecuteScript("./src/scripts/JSONParser/parser.exe", [
    jsonString,
  ]);

  return JSON.parse(result);
}

async function ExecuteScript(scriptPath, args) {
  return new Promise((resolve, reject) => {
    const script = scriptPath;
    const optimize = spawn(script, args);
    optimize.stdout.on("data", (data) => {
      resolve(data.toString());
    });
  });
}
