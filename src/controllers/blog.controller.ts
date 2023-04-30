import {BlogModel } from "../model/Blog.model";
import { Request , Response  } from "express";
import { env } from "../config/environment";

//NOTE: samples
//export async function {name} (request:Request , response:Response){
// return response.status().json({})

export async function getAllBlogs (request:Request , response:Response){
    let blogs 
    try {
       blogs = await BlogModel.find() 
    } catch (error) {
        return response.status(500).json({message:"Error fetching Blogs"})
    }
    if(!blogs){
        return response.status(404).json({message:"Error fetching blogs"})
    }
    return response.status(200).json({message:"Sucess" , data:blogs})
}

export async function addBlog (request:Request , response:Response){
    const {title, description , image , user} = request.body

    const blog = new BlogModel({
        title,
        description,
        image,
        user
    })

    try {
       blog.save() 
    } catch (error) {
        return response.status(500).json({message:"Error saving blog"})
    }

    return response.status(200).json({message:"Sucess" , data:blog})
}
 
