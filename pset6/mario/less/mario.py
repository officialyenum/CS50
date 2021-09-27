from cs50 import get_int

def main():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8 :
            break

    for i in range(1, n + 1):
        num_hashes = i
        num_spaces = n - num_hashes

        print(" " * num_spaces, end="")
        print("#" * num_hashes)

main()