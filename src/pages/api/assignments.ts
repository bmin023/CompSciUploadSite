import { NextApiRequest, NextApiResponse } from "next";
import nextConnect from "next-connect";

import { getAssignments } from "utils/assignmentUtils";

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

apiRoute.get((req: NextApiRequest, res) => {
  res.status(200).json({ assignments: getAssignments() });
});

export default apiRoute;
