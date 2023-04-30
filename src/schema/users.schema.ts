import {object , string  } from "zod"

export const createUserSchema =object({
    body:object({
        name:string({required_error:"Name is not defined"}),
        email:string({required_error:"Email is not defined"}).email("Not a valid Email address"),
        password:string({required_error:"Password is required"}).min(7 , "Password is too short, should he at least 6 charactes.")
    })
})



export const LogUserInSchema =object({
    body:object({
        email:string({required_error:"Email is not defined"}).email("Not a valid Email address"),
        password:string({required_error:"Password is required"}).min(7 , "Password is too short, should he at least 6 charactes.")
    })
})
