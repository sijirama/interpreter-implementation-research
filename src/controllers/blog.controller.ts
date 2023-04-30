import {BlogModel } from "../model/Blog.model";
import { Request , Response  } from "express";
import { env } from "../config/environment";
import { UserModel } from "../model/User.model";
import mongoose from "mongoose";
import { Session } from "inspector";

//NOTE: samples
//export async function {name} (request:Request , response:Response){
// return response.status().json({})

export async function getBlog (request:Request , response:Response){
    const id = request.params.id
    let blog
    try {
        blog = await BlogModel.findById(id).exec()
    } catch (error) {
        return response.status(500).json({message:"Error fetching Blog"})
    }
    if(!blog){
        return response.status(404).json({message:"Error fetching blog"})
    }
    return response.status(200).json({message:"Sucess" , data:blog})
}

export async function deleteBlog (request:Request , response:Response){
    const id = request.params.id
    let blog:any
    try {
        blog = await BlogModel.findByIdAndDelete(id).populate("user").exec()
        await blog.user.blogs.pull(blog)
        await blog.user.save()
        console.log("Deleted blog")
    } catch (error) {
        console.log(error)
        return response.status(500).json({message:"Error fetching Blog"})
    }
    if(!blog){
        return response.status(404).json({message:"Error fetching blog"})
    }
    return response.status(200).json({message:"Sucess deleting blog" , data:blog})
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

    //NOTE: identify user
    //WARN: this method isnt really the best, we can use jwts and identify the user and send it to the route body as req.user instead of re.body.user

    let existingUser:Partial<mongoose.Document> | any
    //let existingUser

    try {
        existingUser= await UserModel.findById(user).exec()
    } catch (error) {
        return response.status(500).json({message:"Error: Server error "})
    }

    if(!existingUser){
        return response.status(404).json({message:"Unable to identify user"})
    }

    const blog = new BlogModel({
        title,
        description,
        image,
        user
    })
    
    let session

    try {
        
        session = await mongoose.startSession()
        session.startTransaction()
        await blog.save({session})
        existingUser.blogs.push(blog)
        await existingUser.save!({session})
        await session.commitTransaction()

    } catch (error) {
        console.log(error)
        await session?.abortTransaction()
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


export async function getUserblog (request:Request , response:Response){
    const id = request.params.id
    
    
    let userBlogs

    try {
        userBlogs = await UserModel.findById(id).populate("blogs").exec()
        console.log(userBlogs)
    } catch (error) {
        console.log(error)
        return response.status(500).json({message:"Error Fetching user blogs"})
    }

    if(!userBlogs){
        return response.status(400).json({message:"No blogs to fetch here"})
    }

    return response.status(200).json({message:"Sucessfully update blog", blogs:userBlogs })
}
