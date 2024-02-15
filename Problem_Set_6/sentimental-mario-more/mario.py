from cs50 import get_int

def main():
    height = 9
    while height < 1 or height > 8:
        height = get_int("Height: ")

    if height == 1:
        print("#  #")
    else:
        print_case(height)

def print_case(n):
    j = 1
    while j < n + 1:
        for k in range(0, n - j):
            print(" ", end="")
        for l in range(j, 0, -1):
            print("#", end="")
        print("  ", end="")
        for m in range(0, j):
            print('#', end="")
        print()
        j += 1

if __name__ == "__main__":
    main()
