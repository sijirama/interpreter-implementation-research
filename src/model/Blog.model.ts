import mongoose from "mongoose";
import { UserModel } from "./User.model";
const Schema = mongoose.Schema

const BlogSchema = new Schema({    
    title:{
        type:String,
        required:true
    },
    description:{
        type:String,
        required:true,
    },
    image:{
        type:String,
        required:true,
    },
    user:{
        type:mongoose.Types.ObjectId,
        ref:"user",
        required:true,
    }
})

export const BlogModel = mongoose.model("blog" , BlogSchema)

