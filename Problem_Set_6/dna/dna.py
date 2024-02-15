import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv)!=3:
        print("Usage: python dna.py csvFile textFile")
        sys.exit(1)
    database = sys.argv[1]
    sequences = sys.argv[2]

    # TODO: Read database file into a variable
    with open(database) as dataFile:
        reader_d = csv.DictReader(dataFile)
        data = [row for row in reader_d]
        headers = reader_d.fieldnames
        headers.pop(0)
    # TODO: Read DNA sequence file into a variable
    with open(sequences) as sequenceFile:
        sequence = sequenceFile.read()

    # TODO: Find longest match of each STR in DNA sequence
    seQ = []
    for se in range(len(headers)):
        seQ.append(longest_match(sequence, headers[se]))
     # TODO: Check database for matching profiles
    for people in data:
        flag = True
        for se in range(len(headers)):
            if int(people[headers[se]]) != seQ[se]:
                flag = False
                break
        if flag:
            print(people["name"])
            sys.exit(2)
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
