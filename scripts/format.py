import os

res = ' '.join(["gcc", "-v"])
print(res)

# header
for item in os.walk("./include"):
    dir = item[0] + "/"
    for file in item[2]:
        suffix = file.split(".")[1]
        if suffix == "h":
            cmd = ' '.join(["clang-format", "-style=Microsoft", "-i", dir + file])
            os.system(cmd)
for item in os.walk("./src"):
    dir = item[0] + "/"
    for file in item[2]:
        suffix = file.split(".")[1]
        if suffix == "cpp":
            cmd = ' '.join(["clang-format", "-style=Microsoft", "-i", dir + file])
            os.system(cmd)
