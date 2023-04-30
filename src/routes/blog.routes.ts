import { Router } from "express";
//import { UserModel } from "../model/User.model";
import * as BlogController from "../controllers/blog.controller"
const router = Router()

router.get("/:id" , BlogController.getBlog )
router.delete("/:id" , BlogController.deleteBlog )
router.get("/" , BlogController.getAllBlogs )
router.post("/addblog" , BlogController.addBlog )
router.put("/updateblog/:id" , BlogController.updateblog )
router.get("/user/:id" , BlogController.getUserblog )


export {router }




