import formidable from "formidable";
import fs from "fs";
import { NextApiRequest, NextApiResponse } from "next";
import nextConnect from "next-connect";

import { CodeReturn, getReturns } from "utils/assignmentUtils";

const apiRoute = nextConnect({
  onError(error, req, res: NextApiResponse) {
    res
      .status(501)
      .json({ error: `Sorry something Happened! ${error.message}` });
  },
  onNoMatch(req, res) {
    res.status(405).json({ error: `Method '${req.method}' Not Allowed` });
  },
});

const saveFile = async (file: formidable.File, dest: string) => {
  const data = fs.readFileSync(file.path);
  fs.writeFileSync(`./public/assignments/${dest}/upload.cpp`, data);
  fs.unlinkSync(file.path);
};

export type UploadPostRes = {
  returns: CodeReturn;
};

apiRoute.post((req: NextApiRequest, res) => {
  const form = new formidable.IncomingForm();
  form.parse(req, async (err, fields, files) => {
    await saveFile(
      files.file as unknown as formidable.File,
      fields.dest as string
    );
    const returns = await getReturns(fields.dest as string);
    res.status(200).json({ returns });
  });
});

export default apiRoute;

export const config = {
  api: {
    bodyParser: false, // Disallow body parsing, consume as stream
  },
};
