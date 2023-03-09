# TODO
import cs50

# prompt
while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break


for i in range(height):
    # first half
    for j in range(i, (height - 1)):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
# space
    print("  ", end="")
# second half
    for l in range(i + 1):
        print("#", end="")
    print("")