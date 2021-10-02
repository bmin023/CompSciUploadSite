import { Options } from "compile-run";
import { compileCpp } from "compile-run/dist/lib/cpp/compile-file";
import fs from "fs";
import readline from "readline";
import {join} from 'path'
import { runExecutable } from "./compileRunUtils";

export function getFolders(filePath: fs.PathLike): string[] {
  const filenames = fs.readdirSync(filePath);
  return filenames.filter((value) => {
    return !value.includes(".");
  });
}

function getConfig(folder: fs.PathLike): JSONConfig {
  const buffer = fs.readFileSync(join(__dirname,`assignments/${folder}/config.json`));
  return JSON.parse(buffer as unknown as string) as JSONConfig;
}

export type JSONConfig = {
  name: string;
  desc: string;
  visible: boolean;
  input?: string[];
  order: number;
};

export type Assignment = {
  name: string;
  desc: string;
  folder: string;
  order: number;
};

export function getAssignments(): Assignment[] {
  const assignments = [] as Assignment[];
  getFolders(join(__dirname,"assignments")).forEach((folder) => {
    const config = getConfig(folder);
    if (config.visible) {
      assignments.push({
        name: config.name,
        desc: config.desc,
        order: config.order,
        folder,
      });
    }
  });
  return assignments.sort((a, b) => {
    return b.order - a.order;
  });
}

export type CodeReturn = {
  solution: string[];
  student: string[];
  isCorrect: boolean;
  warnings: string[];
};

async function getWarnings(filepath: string) {
  const warnings: string[] = [];
  const fileStream = fs.createReadStream(filepath);

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity,
  });

  // Author, Assignment Title, Assignment Description, Due Date, Date Created, Date Last Modified,
  // Data Abstraction, Input, Process, Output, Assumptions
  const headers: boolean[] = [
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
  ];

  let files = 0;
  let indent = 0;
  let minSpace = 2;
  let foundTrueMinSpace = false;
  let count = 0;

  let comment = false;
  for await (const line of rl) {
    count++;
    let singleComment = false;
    const lower = line.toLowerCase();
    if (!headers[0] && lower.includes("author:")) headers[0] = true;
    if (!headers[1] && lower.includes("assignment title:")) headers[1] = true;
    if (!headers[2] && lower.includes("assignment description:"))
      headers[2] = true;
    if (!headers[3] && lower.includes("due date:")) headers[3] = true;
    if (!headers[4] && lower.includes("date created:")) headers[4] = true;
    if (!headers[5] && lower.includes("date last modified:")) headers[5] = true;
    if (!headers[6] && lower.includes("data abstraction:")) headers[6] = true;
    if (!headers[7] && lower.includes("input:")) headers[7] = true;
    if (!headers[8] && lower.includes("process:")) headers[8] = true;
    if (!headers[9] && lower.includes("output:")) headers[9] = true;
    if (!headers[10] && lower.includes("assumptions:")) headers[10] = true;

    if (lower.indexOf("//") > -1) {
      comment = true;
      singleComment = true;
    }

    if (line.length > 80) {
      warnings.push(`Line ${count} is too long.`);
    }

    if (lower.includes("/*")) comment = true;
    else if (lower.includes("*/")) comment = false;
    if (!comment) {
      // Lower Indent before checking indent.
      if (lower.includes("}")) indent--;

      let first = lower.search(/\S/);
      if (first > 0) {
        if (!foundTrueMinSpace && indent == 1) {
          minSpace = first;
          foundTrueMinSpace = true;
        }
        if (indent > 0) {
          lower.replace("\t", " ".repeat(minSpace));
          first = lower.search(/\S/);
          if (first != minSpace * indent) {
            warnings.push(`Indentation Error on Line ${count}`);
          }
        }
      }

      if (lower.includes("{")) indent++;

      if (lower.includes(".open(")) files++;
      if (lower.includes(".close(")) files--;
    }

    if (singleComment) {
      singleComment = false;
      comment = false;
    }
  }

  if (!headers[0]) warnings.push("Forgot 'Author' Header");
  if (!headers[1]) warnings.push("Forgot 'Assignment Title' Header");
  if (!headers[2]) warnings.push("Forgot 'Assignment Description' Header");
  if (!headers[3]) warnings.push("Forgot 'Due Date' Header");
  if (!headers[4]) warnings.push("Forgot 'Date Created' Header");
  if (!headers[5]) warnings.push("Forgot 'Date Last Modified' Header");
  if (!headers[6]) warnings.push("Forgot 'Date Abstraction' Header");
  if (!headers[7]) warnings.push("Forgot 'Input' Header");
  if (!headers[8]) warnings.push("Forgot 'Process' Header");
  if (!headers[9]) warnings.push("Forgot 'Output' Header");
  if (!headers[10]) warnings.push("Forgot 'Assumptions' Header");

  if (files != 0) warnings.push("A file wasn't closed.");

  console.timeLog("Timer", "-Warnings");

  return warnings;
}

export function getReturns(folder: string): Promise<CodeReturn> {
  const config = getConfig(folder);
  let promise: Promise<CodeReturn>;
  promise = new Promise(async (res, rej) => {
    console.group(folder);
    console.time("Timer");

    const returns: CodeReturn = {
      solution: [],
      student: [],
      isCorrect: true,
      warnings: await getWarnings(`./public/assignments/${folder}/upload.cpp`),
    };
    let count = 0;
    const solutionexec = await compileCpp(
      `./public/assignments/${folder}/solution.cpp`
    );
    const studentexec = await compileCpp(
      `./public/assignments/${folder}/upload.cpp`
    );
    console.timeLog("Timer", "-Compiled");
    for (let i = 0; i < (config.input ? config.input.length : 1); i++) {
      const options: Options = {
        stdin: config.input ? config.input[i] : undefined,
        compileTimeout: 1000,
      };
      runExecutable(solutionexec, folder, options)
        .then((solution) => {
          runExecutable(studentexec, folder, options)
            .then((student) => {
              count++;
              returns.solution.push(solution.stdout);
              returns.student.push(student.stdout);
              if (
                solution.stdout.replace(/\s+/g, "") !==
                student.stdout.replace(/\s+/g, "")
              ) {
                // Bad Solution
                returns.isCorrect = false;
              }
              if (count == (config.input ? config.input.length : 1)) {
                // All inputs run through.
                res(returns);
                console.timeLog("Timer", "-Tests Run");
                console.timeEnd("Timer");
                console.groupEnd();
              }
            })
            .catch((solerr) => {
              res({
                isCorrect: false,
                student: ["Something went wrong."],
                solution: ["I don't know what."],
                warnings: [],
              });
            });
        })
        .catch((solerr) => {
          res({
            isCorrect: false,
            solution: ["Something went wrong."],
            student: ["I don't know what."],
            warnings: [],
          });
        });
    }
  });
  return promise;
}
