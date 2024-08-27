from javascript import require, On, Once, AsyncTask, once, off

mineflayer = require("mineflayer")

bot = mineflayer.createBot(
    {"username": "bot", "host": "localhost", "port": 64657, "version": "1.19", "hideErrors": True}
)

@On(bot, "login")
def login(this):
    bot.chat("hello world")
    for i in range(1,1000):
        bot.chat("i can count to " + str(i))
