import { exec, spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

export async function runOptimizer(jsonString: string): Promise<string> {
  const run = `./src/optimizer/driver.${process.env.FILE_TYPE ?? "out"}`;
  const result: string = await ExecuteScript(`${run}`, [jsonString]).catch(
    () => "{error: no good}"
  );

  return result;
}

async function ExecuteScript(
  scriptPath: string,
  args: string[]
): Promise<string> {
  return new Promise((resolve, reject) => {
    const script = scriptPath;
    const optimize = spawn(script, args);
    optimize.stdout.on("data", (data) => {
      resolve(data.toString());
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
