import nextConnect from "next-connect";
import formidable from 'formidable';
import fs from "fs";
import { NextApiRequest, NextApiResponse } from "next";
import { checkIfGood, CodeReturn, getAssignments, getFolders, getReturns } from "utils/assignmentUtils";


const apiRoute = nextConnect({
  onError(error, req, res : NextApiResponse) {
    res
      .status(501)
      .json({ error: `Sorry something Happened! ${error.message}` });
  },
  onNoMatch(req, res) {
    res.status(405).json({ error: `Method '${req.method}' Not Allowed` });
  },
});

export type UploadPostRes = {
  returns: CodeReturn;
}

apiRoute.post((req : NextApiRequest, res) => {
  const form = new formidable.IncomingForm();
  form.parse(req, async function (err, fields, files) {
    await saveFile(files.file as unknown as formidable.File, fields.dest as string);
    let returns = await getReturns(fields.dest as string);
    return res.status(200).json({returns});
  });
});

const saveFile = async (file: formidable.File,dest:string) => {
  const data = fs.readFileSync(file.path);
  fs.writeFileSync(`./public/assignments/${dest}/upload.cpp`, data);
  await fs.unlinkSync(file.path);
  return;
};

export default apiRoute;

export const config = {
  api: {
    bodyParser: false, // Disallow body parsing, consume as stream
  },
};
