import{Result,Options} from "compile-run";
import{ChildProcess, spawn} from "child_process";

interface ResponseMessage
{
status:
  'success' | 'error';
executionResult:
  Result;
error:
  any;
}

export function execute(cmd: string,folder:string,...args: any[]): Promise<Result> {
  let timeout = 3000;
  let stdin = "";
  let stdoutLimit = 1000;
  let stderrLimit = 1000;
  folder = `public/assignments/${folder}`;
  return new Promise((res, rej) => {
    let p: ChildProcess;
    let arr: string[] | undefined = undefined;
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
  let res = await execute(filePath, folder, options);
  if (res.signal === "SIGSEGV") {
    //probably seg fault and other memory/pagination issues
    res.errorType = "run-time";
  } else if (res.signal === "SIGTERM") {
    //probably timeout or killed by SO somehow
    res.errorType = "run-timeout";
  }
  return res;
}