import { Router } from "express";
//import { UserModel } from "../model/User.model";
import * as BlogController from "../controllers/blog.controller"
const router = Router()

router.get("/" , BlogController.getAllBlogs )


export {router }




