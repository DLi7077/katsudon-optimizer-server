import { exec, spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();
import { OptimizeResultAttributes } from "./database/models/OptimizeResult";
import { CharacterEnemyRequest } from "interface";

export async function runOptimizer(
  optimizeRequest: CharacterEnemyRequest
): Promise<OptimizeResultAttributes> {
  const run = `./src/optimizer/driver.${process.env.FILE_TYPE ?? "out"}`;
  const optimizeRequestString: string = JSON.stringify(optimizeRequest);

  const result: OptimizeResultAttributes | any = await ExecuteScript(`${run}`, [
    optimizeRequestString,
  ]).then((res: any) => {
    if (!isJsonString(res)) return { error: res };
    return JSON.parse(res);
  });

  return result;
}

// https://nodejs.org/api/child_process.html#event-spawn
async function ExecuteScript(
  scriptPath: string,
  args: string[]
): Promise<string> {
  return new Promise((resolve, reject) => {
    const script = scriptPath;
    const optimize = spawn(script, args);
    let output = "";
    optimize.stdout.on("data", (data: string) => {
      output += data.toString();
    });

    optimize.stderr.on("data", (error: string) => {
      reject(error);
    });

    optimize.on("close", (error_code) => {
      if (error_code != 0) reject(`{error: "ended with code ${error_code}"}`);
      resolve(output);
    });
  });
}

async function Compile(command: string): Promise<string> {
  return new Promise((resolve, reject) => {
    exec(command, (err, stdout, stderr) => {
      if (err) {
        console.log("problem");
        reject(err);
      }
      console.log("ok");
      resolve(stdout ?? stderr);
    });
  });
}

function isJsonString(text: string): boolean {
  try {
    JSON.parse(text);
  } catch (e: any) {
    return false;
  }
  return true;
}
