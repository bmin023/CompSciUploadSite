import { connect } from "mongoose";
let MONGO_URI = process.env.MONGO_URI;
if (!MONGO_URI) {
  throw new Error("Set MONGO_URI in your env.");
  
}

console.log(MONGO_URI);

export const connectToDatabase = () => connect(MONGO_URI as string);
