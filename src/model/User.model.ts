
import mongoose from "mongoose";
import { BlogModel } from "./Blog.model";
const Schema = mongoose.Schema

const UserSchema:any = new Schema({    
    name:{
        type:String,
        required:true
    },
    email:{
        type:String,
        required:true,
        unique:true
    },
    password:{
        type:String,
        required:true,
        minlength:6,
    },
    blogs:[{
        type:mongoose.Types.ObjectId,
        ref:"blog",
        required:true
    }]
})

export const UserModel = mongoose.model("user" , UserSchema)

