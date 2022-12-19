height = 0
while height < 1 or height > 8:
    height = input("Height: ")
    height = int(height)

for i in range(0, height, 1):
    for j in range(0, height+i+3, 1):
        if (j==height or j==height+1 or i+j<height-1):
            print(" ", end="")
        else:
            print("#", end="")

    print()