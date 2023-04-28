import dotenv from "dotenv"
dotenv.config()

export const env = {
    Hello:process.env.HELLO,
    PORT: process.env.PORT || 5174
}

