import Express from "express"
import { env } from "./config/environment"
import mongoose from "mongoose"
import { connectDatabase } from "./config/connectDB"
connectDatabase()
const app = Express()



mongoose.connection.once("open" , () => {
    app.listen( env.PORT , () => {
        console.clear()
        console.log("Server is now listening at port:", env.PORT)
    })
})
