import { UserModel } from "../model/User.model";
import { Request , Response  } from "express";

//NOTE: samples
//export async function {name} (request:Request , response:Response){
// return response.status().json({})

export async function getAllUsers (request:Request , response:Response){
    let users

    try {
       users = await UserModel.find() 
    } catch (error) {
        return response.status(500).json({message:"Error fetching Users"})
    }

    if(!users){
        return response.status(404).json({message:"Error fetching Users"})
    }

    return response.status(200).json({message:"Sucess" , data:users})
}

export async function signup (request:Request , response:Response){
    const {name  , email , password} = request.body

    let existingUser

    try {
       existingUser = await UserModel.find({email}) 
    } catch (error) {
        return response.status(500).json({message:"Error creating new account"})
    }

    if(existingUser){
        return response.status(400).json({message:"User already exists"})
    }

    const user = new UserModel({
        name,
        email,
        password
    })

    try {
        user.save()
        return response.status(200).json({message:"User created successfully"})
    } catch (error) {
        return response.status(500).json({message:"Error creating new account"})
    }
}
