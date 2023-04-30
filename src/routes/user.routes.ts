
import { Router } from "express";
import { UserModel } from "../model/User.model";
import * as UserController from "../controllers/user.controller"
const router = Router()

router.get("/" , UserController.getAllUsers)
router.post("/signup" , UserController.signup)
router.post("/signin" , UserController.signin)


export {router }



