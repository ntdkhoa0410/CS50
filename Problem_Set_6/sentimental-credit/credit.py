import math

# Function to get user input
def get_input():
    while True:
        try:
            number = int(input("Enter card number: "))
            if number >= 0:
                return number
        except ValueError:
            continue

# Function to calculate the sum
def check_sum(no):
    length = 0
    sum_odd = 0
    sum_even = 0
    sum = 0
    quotient = 0
    remain = 0
    while no != 0:
        quotient = no // 10
        remain = no % 10
        length += 1
        if length % 2 != 0:
            sum_odd += remain
        else:
            sum_even += (remain * 2) % 10 + (remain * 2) // 10
        no = quotient
    return length, sum_odd, sum_even

# Function to check validity
def check_valid(number, length, sum_odd, sum_even):
    if length != 15 and length != 16 and length != 13:
        return "INVALID"
    elif (sum_odd + sum_even) % 10 != 0:
        return "INVALID"
    else:
        startNumber = number // 10 ** (length - 2)
        if (startNumber == 34 or startNumber == 37) and length == 15:
            return "AMEX"
        elif 51 <= startNumber <= 55 and length == 16:
            return "MASTERCARD"
        else:
            startNumber = number // 10 ** (length - 1)
            if startNumber == 4 and (length == 16 or length == 13):
                return "VISA"
            else:
                return "INVALID"

if __name__ == "__main__":
    number = get_input()
    length, sum_odd, sum_even = check_sum(number)
    result = check_valid(number, length, sum_odd, sum_even)
    print(result)
