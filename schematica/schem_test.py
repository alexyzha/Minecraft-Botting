import mcschematic

schem = mcschematic.MCSchematic()
schem.setBlock((0,0,0),"minecraft:stone")
schem.save("schem_saves","TEST_1",mcschematic.Version.JE_1_18_2)