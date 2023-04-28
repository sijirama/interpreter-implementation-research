import mongoose from "mongoose"; 
import { env } from "./environment";

const mongoUri = env.MongoUri!

export async function connectDatabase () {
    try {
       const connect = await mongoose.connect(mongoUri) 
    } catch (error) {
        console.log("Failed to connect to database.")
    }
}
