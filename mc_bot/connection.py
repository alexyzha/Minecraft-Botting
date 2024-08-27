# includes
from javascript import require, On, Once, AsyncTask, once, off
mineflayer = require("mineflayer")

# bot creation param
bot_param = {"username": "bot", "host": "localhost", "port": 64657, "version": "1.19", "hideErrors": True}

# auto reconnect
reconnect = True

def bot_init():
    bot = mineflayer.createBot(bot_param)
    # when logged in
    @On(bot,"login")
    def login(this):
        bot.chat("hello world")

    # when kicked
    @On(bot,"kicked")
    def kicked(this,reason,logged_in):
        if logged_in:
            print(f"kicked: {reason}")
        else:
            print(f"kicked while logging: {reason}")

    # self disconnect
    @On(bot,"messagestr")
    def messagestr(this,message,messagePosition,jsonMsg,sender,verified):
        if messagePosition == "chat" and "bot_quit_1234" in message:
            global reconnect
            reconnect = False
            this.quit()

    # disconnect
    @On(bot,"end")
    def end(this,reason):
        print(f"DC: {reason}")
        # turn off event listeners
        off(bot,"login",login)
        off(bot,"kicked",kicked)
        off(bot,"messagestr",messagestr)
        if reconnect:
            print("recon...")
            bot_init() # recursive starting bot
        off(bot,"end",end)

# initial instance
bot_init()