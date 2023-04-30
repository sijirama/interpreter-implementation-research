import Express, { urlencoded } from "express"
import { env } from "./config/environment"
import mongoose from "mongoose"
import { connectDatabase } from "./config/connectDB"
import { router as UserRouter } from "./routes/user.routes"
import { router as BlogRouter } from "./routes/blog.routes"
connectDatabase()
const app = Express()

//NOTE: Middleware /////////////////////////////////////////////////////
app.use(Express.json())
app.use(urlencoded({extended:false}))

//NOTE: Routes Middleware /////////////////////////////////////////////////////
app.use("/api/user" , UserRouter)
app.use("/api/blog" , BlogRouter)

mongoose.connection.once("open" , () => {
    app.listen( env.PORT , () => {
        console.clear()
        console.log("Server is now listening at port:", env.PORT)
    })
})
