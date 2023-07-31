# brnfck
A small brainfuck interpreter/editor

editor+interpreter.c is dependent on lib.h and in beta

brnfck43.c and functions4.h form the alpha version, and interprets brnfck4, but is backwards compatible with brnfck3 and regular brainfuck

###########################################################################################

below info about debugged.c (brainfuck interpreter) and brnfck3.c (brnfck3 interpreter)

commandline options: filename

If a plaintext brainfuck program is given as arg, it will be interpreted

if not, user is prompted to input brainfuck commands

############################################################################################
on brainfuck dialects

brnfck3 works the exact same but has 3 more commands

brnfck4 allows certain commands to interpret the next entry as an argument unless it is an argument, based on brnfck3
