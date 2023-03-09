import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Standard Error Message")
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    datafile = sys.argv[1]
    with open(datafile) as f:
        reader = csv.DictReader(f)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    for line in file:
        buff = line.rstrip()
        break
    file.close()

    # TODO: Find longest match of each STR in DNA sequence

    listsubseq = []
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            for index in row[1:]:
                listsubseq.append(index)
            break

    scores = []
    for i in listsubseq:
        scores.append(longest_match(buff, i))

    # TODO: Check database for matching profiles

    for i in database:
        counter = 0
        for j in range(len(listsubseq)):
            if int(i[listsubseq[j]]) == int(scores[j]):
                counter += 1
            else:
                break
            if counter == len(scores):
                print(i["name"])
                break
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
