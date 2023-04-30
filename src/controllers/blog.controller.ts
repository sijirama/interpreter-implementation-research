import {BlogModel } from "../model/Blog.model";
import { Request , Response  } from "express";
import { env } from "../config/environment";

//NOTE: samples
//export async function {name} (request:Request , response:Response){
// return response.status().json({})

export async function getBlog (request:Request , response:Response){
    const id = request.params.id
    let blog
    try {
        blog = await BlogModel.findById(id).exec()
        console.log(blog)
    } catch (error) {
        return response.status(500).json({message:"Error fetching Blog"})
    }
    if(!blog){
        return response.status(404).json({message:"Error fetching blog"})
    }
    return response.status(200).json({message:"Sucess" , data:blog})
}


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
       await blog.save() 
    } catch (error) {
        return response.status(500).json({message:"Error saving blog"})
    }

    return response.status(200).json({message:"Sucess" , data:blog})
}
 
export async function updateblog (request:Request , response:Response){
    const id = request.params.id
    const {title , description , image} = request.body
    let blog
    try {
       blog = await BlogModel.findByIdAndUpdate(id , {title , description , image}) 
    } catch (error) {
        return response.status(500).json({message:"Error Updating blog"})
    }
    return response.status(200).json({message:"Sucessfully update blog" })
}
