import { IUser } from "./Models/User";

export type RegisterReturns = {
  good: boolean,
  username?: string,
  password?: string,
}

export function checkRegister(username:string,password:string):RegisterReturns {
  let returns : RegisterReturns = {
    good:true
  }
  if (!(password.length > 4)) {
    returns.password = "Pick a longer password.";
    returns.good = false;
  }
  else if (password.search('/^\s+$/') >= 0) {
    returns.password = "Can only be one word.";
    returns.good = false;
  }
  if (!(username.length > 2)) {
    returns.username = "Pick a longer username.";
    returns.good = false;
  } else if (username.search("/^s+$/") >= 0) {
    returns.password = "Can only be one word.";
    returns.good = false;
  }
  return returns;
}