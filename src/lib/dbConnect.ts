import { connect } from "mongoose";

const { MONGO_URI } = process.env;

if (!MONGO_URI) {
  throw new Error("Set MONGO_URI in your env.");
}

const connectToDatabase = () => connect(MONGO_URI as string);

export default connectToDatabase();
