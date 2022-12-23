import { exec, spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

export async function runOptimizer(jsonString: string): Promise<string> {
  const run = `./src/optimizer/driver.${process.env.FILE_TYPE ?? "out"}`;
  const result: string = await ExecuteScript(`${run}`, [jsonString])
    .then((res: any) => {
      if (!isJsonString(res)) return { error: res };

      return JSON.parse(res);
    })
    .catch((err) => `{error: ${err}}`);

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
    optimize.stdout.on("data", (data: string) => {
      resolve(data.toString());
    });

    optimize.stderr.on("data", (error: string) => {
      reject(error);
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
