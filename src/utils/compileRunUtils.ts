/*
All this was derived from vibhor1997a's repository compile-run. There was just some lines
that had to change for it to work in my enviornment but all credit goes to him.
*/

import { ChildProcess, spawn } from "child_process";
import { Result, Options } from "compile-run";
import path from "path";
import os from 'os';

interface ResponseMessage {
  status: "success" | "error";
  executionResult: Result;
  error: any;
}

export function execute(
  cmd: string,
  folder: string,
  ...args: any[]
): Promise<Result> {
  let timeout = 3000;
  let stdin = "";
  let stdoutLimit = 1000;
  let stderrLimit = 1000;
  folder = `public/assignments/${folder}`;
  return new Promise((res, rej) => {
    let p: ChildProcess;
    let arr: string[] | undefined;
    if (args[0] && args[0] instanceof Array) {
      arr = args[0];
      if (args[1] && typeof args[1] === "object") {
        timeout = (args[1] && args[1].timeout) || timeout;
        stdin = (args[1] && args[1].stdin) || stdin;
        stderrLimit = (args[1] && args[1].stderrLimit) || stderrLimit;
        stdoutLimit = (args[1] && args[1].stdoutLimit) || stdoutLimit;
      }
    } else if (args[0] && typeof args[0] === "object") {
      timeout = (args[0] && args[0].timeout) || timeout;
      stdin = (args[0] && args[0].stdin) || stdin;
      stderrLimit = (args[0] && args[0].stderrLimit) || stderrLimit;
      stdoutLimit = (args[0] && args[0].stdoutLimit) || stdoutLimit;
    }
    p = spawn("node", ["box"], {
      stdio: ["inherit", "inherit", "inherit", "ipc"],
    });
    p.send({
      cmd,
      timeout,
      stdin,
      stderrLimit,
      stdoutLimit,
      folder,
      arguments: arr,
    });
    p.on("message", (msg: ResponseMessage) => {
      if (msg.status == "success") {
        res(msg.executionResult);
      } else {
        rej(msg.error);
      }
      p.kill();
    });
  });
}

export async function runExecutable(
  filePath: string,
  folder: string,
  options?: Options
): Promise<Result> {
  const res = await execute(filePath, folder, options);
  if (res.signal === "SIGSEGV") {
    // probably seg fault and other memory/pagination issues
    res.errorType = "run-time";
  } else if (res.signal === "SIGTERM") {
    // probably timeout or killed by SO somehow
    res.errorType = "run-timeout";
  }
  return res;
}

export async function compileCpp(
  filePath: string,
  folder: string,
  options?: Options
): Promise<string> {
  let compileTimeout = (options && options.compileTimeout) || 3000;
  let executableExt;
  if (os.type() === "Windows_NT") {
    executableExt = "exe";
  } else {
    executableExt = "out";
  }
  const compilationPath: string = (options && options.compilationPath) || "gcc";
  let executablePath = path.join(process.cwd(), "public","assignments",folder,`upload.exe`);
  let res = await execute(
    compilationPath,
    folder,
    [filePath, "-o", executablePath, "-lstdc++"],
    { timeout: compileTimeout }
  );
  if (res.exitCode !== 0) {
    res.errorType = "compile-time";
    throw res;
  }
  return executablePath;
}