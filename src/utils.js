import { spawn } from "child_process";

export async function runOptimizer() {
  console.log("working");
  return new Promise((resolve, reject) => {
    const optimize = spawn("./src/a.exe", ["input.txt", "output.txt"]);
    optimize.stdout.on("data", (data) => {
      console.log(data.toString());
    });

    resolve("success");
  });
}
