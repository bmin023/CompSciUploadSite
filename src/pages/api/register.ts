import { NextApiRequest, NextApiResponse } from "next";
import nextConnect from "next-connect";

import { checkRegister } from "utils/userUtil";

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

apiRoute.post((req: NextApiRequest, res: NextApiResponse) => {
  const reg = checkRegister(req.body.username, req.body.password);
  return res.status(200).json(reg);
});

export default apiRoute;
