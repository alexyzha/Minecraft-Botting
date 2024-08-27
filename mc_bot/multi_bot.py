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
server_port = 64657

# auto reconnect
reconnect = True

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
            if messagePosition == "chat":
                # indiv + multi quit
                if ("quit_" + self.bot_name in message) or ("bot_quit_all_1234" in message):
                    self.reconnect = False
                    this.quit()
                # look at player + twerk (movement later)
                elif "twerk" in message:
                    # get all local players
                    l_players = self.bot.players
                    # get target player
                    for p in l_players:
                        player_data = l_players[p]
                        if player_data["uuid"] == sender:
                            vec3_ploc = l_players[p].entity.position
                            true_ploc = vec3(
                                vec3_ploc["x"],
                                vec3_ploc["y"] + 1,
                                vec3_ploc["z"]
                            )
                    # look if found
                    if true_ploc:
                        self.bot.lookAt(true_ploc)
                        yaw = self.bot.entity.yaw + math.pi
                        pitch = self.bot.entity.pitch
                        self.bot.look(yaw, pitch, True)
                        for _ in range(10):
                            self.bot.setControlState("sneak",True)
                            time.sleep(0.5)  # wait half a second
                            self.bot.setControlState("sneak",False)
                            time.sleep(0.5)  # wait half a second
                # look at specific coords
                elif "look at coords" in message:
                    x, y, z = message.split(" ")[-3:]
                    vec3_bloc = vec3(x, y, z)
                    self.bot.lookAt(vec3_bloc, True)
                # look in a direction
                elif "look" in message:
                    direction = message.split()[-1]
                    # calc
                    yaw, pitch = 0, 0
                    if direction == "up":
                        pitch = math.pi / 2
                        yaw = self.bot.entity.yaw
                    elif direction == "down":
                        pitch = -math.pi / 2
                        yaw = self.bot.entity.yaw
                    elif direction == "east":
                        yaw = math.pi * 3 / 2
                    elif direction == "south":
                        yaw = math.pi
                    elif direction == "west":
                        yaw = math.pi / 2
                    elif direction == "north":
                        pass
                    elif direction == "left":
                        yaw = self.bot.entity.yaw + math.pi / 2
                    elif direction == "right":
                        yaw = self.bot.entity.yaw - math.pi / 2
                    elif direction == "back":
                        yaw = self.bot.entity.yaw + math.pi
                        pitch = self.bot.entity.pitch
                    # look
                    self.bot.look(yaw, pitch, True)
                # target block
                elif "what do you see" in message:
                    block = self.bot.blockAtCursor()
                    if block:
                        self.bot.chat(f"{block.displayName}")
                    else:
                        self.bot.chat("Air")
                # stack up (creative)
                elif "stack" in message:
                    blocks = int(message.split()[-1])
                    pitch = -math.pi / 2
                    yaw = self.bot.entity.yaw
                    self.bot.look(yaw, pitch, True)
                    for _ in range(blocks):
                        self.bot.setControlState("jump",True)
                        self.bot.setControlState("jump",False)
                        self.bot.clickWindow(0,1,0)
                        time.sleep(0.5)  # wait half a second

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

# initial instance
bot0 = BOT("bot_0")
bot1 = BOT("bot_1")
bot2 = BOT("bot_2")
bot3 = BOT("bot_3")
bot4 = BOT("bot_4")