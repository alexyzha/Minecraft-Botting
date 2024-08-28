import mcschematic
import os

# create schem
schem = mcschematic.MCSchematic()

# load maze
fileloc = "test_origin/10_0.txt"
# read in file
with open(fileloc,'r') as file:
    lines = file.readlines()
# process lines
cur_maze = []
for line in lines:
    cur_maze_row = list(line.strip())
    cur_maze.append(cur_maze_row)

# set schem
for i in range(len(cur_maze)):
    for j in range(len(cur_maze[i])):
        if cur_maze[i][j] == "0":
            for _ in range(3):
                schem.setBlock((i,_,j),"minecraft:stone")

# save schem
schem.save("schem_saves","maze_test_1",mcschematic.Version.JE_1_19)