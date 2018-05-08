import sys

if len(sys.argv) < 2:
    print("Usage: python3 make-class.py ClassName1 [ClassName2] ...")

for i in sys.argv[1:]:
    with open(i+".h", "w") as h:
        h.write("#pragma once\n\n")
        h.write("class " + i + " {\n")
        h.write("public:\nprivate:\n};")
    with open(i+".cpp", "w") as cpp:
        cpp.write("#include \"" + i + ".h\"\n\n")
