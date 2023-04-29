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

