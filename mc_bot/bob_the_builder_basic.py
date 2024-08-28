# includes
from javascript import require, On, Once, AsyncTask, once, off
from simple_chalk import chalk
from utils.vec3_conv import vec3_to_str
import math
import time

# reqs
mineflayer = require("mineflayer")
vec3 = require("vec3")

# bot creation param
server_host = "localhost"
server_port = 55560

# auto reconnect
reconnect = True

# block faces
up_face = vec3(0,1,0)

class BOT:
    def __init__(self,name):
        self.bot_param = {"host": server_host, "port": server_port, "username": name, "hideErrors": True}
        self.reconnect = reconnect
        self.bot_name = name
        self.bot_init()

    def bot_init(self):
        self.bot = mineflayer.createBot(self.bot_param)
        # when logged in
        self.start_event_listeners()
        
    def start_event_listeners(self):
        # on login
        @On(self.bot,"login")
        def login(this):
            self.bot.chat("hello world")

        # when kicked
        @On(self.bot,"kicked")
        def kicked(this,reason,logged_in):
            if logged_in:
                print(f"kicked: {reason}")
            else:
                print(f"kicked while logging: {reason}")

        # self disconnect
        @On(self.bot,"messagestr")
        def messagestr(this,message,messagePosition,jsonMsg,sender,verified=None):
            if messagePosition == "chat" and "bp_at" in message:
                x, y, z = message.split(" ")[-3:]
                # look down to stack up
                self.bot.creative.flyTo(vec3(float(x)+0.5,float(y)+3.05,float(z)+0.5))
                pitch = -math.pi/2
                yaw = self.bot.entity.yaw
                self.bot.look(yaw,pitch,True)
                # pillar of 3
                for _ in range(3):
                    self.bot.waitForTicks(2)
                    block = self.bot.blockAtCursor()
                    # if looking at a block
                    if block:
                        self.bot.placeBlock(block,up_face)
                    # wait for no kick

        # disconnect
        @On(self.bot,"end")
        def end(this,reason):
            print(f"DC: {reason}")
            # turn off event listeners
            off(self.bot,"login",login)
            off(self.bot,"kicked",kicked)
            off(self.bot,"messagestr",messagestr)
            if self.reconnect:
                print("recon " + self.bot_name + "...")
                self.bot_init() # recursive starting bot
            off(self.bot,"end",end)

bot0 = BOT("BOB0")