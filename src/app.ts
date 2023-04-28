import Express from "express"
import { env } from "./config/environment"
const app = Express()
//const PORT = process.env.PORT || 5173




app.listen( env.PORT , () => {
    console.log("Server is now listening at port:", env.PORT)
})
