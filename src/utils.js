import { exec, spawn } from "child_process";
import * as dotenv from "dotenv";
dotenv.config();

export async function runOptimizer(jsonString) {
  const run = `./src/scripts/driver.${process.env.FILE_TYPE ?? "exe"}`;

  const r = Math.floor(Math.random() * 300);
  const result = await ExecuteScript(`${run}`, [jsonString, r])
    // .then((res) => JSON.parse(res))
    .catch(console.error);

  // const result = await ExecuteScript(`${compile}; ${run}`, [jsonString]);

  return result;
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

async function Compile(command) {
  return new Promise((resolve, reject) => {
    exec(command, (err, stdout, stderr) => {
      if (err) {
        reject(err);
      }
      resolve(stdout ?? stderr);
    });
  });
}
