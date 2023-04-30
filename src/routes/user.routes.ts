
import { Router } from "express";
//import { UserModel } from "../model/User.model";
import * as UserController from "../controllers/user.controller"
import { validateSchema } from "../middleware/ValidateResource";
import { LogUserInSchema, createUserSchema } from "../schema/users.schema";
const router = Router()

router.get("/"  ,UserController.getAllUsers)
router.post("/signup" ,validateSchema(createUserSchema), UserController.signup)
router.post("/signin" ,validateSchema(LogUserInSchema) ,  UserController.signin)


export {router }



