import {Request , Response , NextFunction} from "express"
import {AnyZodObject} from "zod"

//NOTE: currying function and parses and validates the schema, the forwards if true or exits if false
//NOTE: it is a middleware im only using for important routes

export const validateSchema = (schema:AnyZodObject) => (request:Request , response:Response , next:NextFunction) => {
    try {
        schema.parse({
            body:request.body,
            query:request.query,
            params:request.params
        })
        next()
    } catch (error) {
        return response.status(400).json({message:"failed" , data:"Schema validation failed" , details:error })
    }
}
