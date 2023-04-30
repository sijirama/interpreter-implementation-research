import mongoose from "mongoose";
const Schema = mongoose.Schema

const BlogSchema = new Schema({    
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
    }
})

export const BlogModel = mongoose.model("blog" , BlogSchema)

