import dotenv from "dotenv"
dotenv.config()

export const env = {
    Hello:process.env.HELLO,
    PORT: process.env.PORT || 5174,
    MongoUri : process.env.MONGO_URI,
    BcryptSalt: Number(process.env.BCRYPT_SALT)
}

