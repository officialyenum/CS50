from csv import reader, DictReader
from sys import argv

if len(argv) < 3:
    print("usage error, dna.py sequence.txt database.csv")
    exit()

# read the dna sequence from the file
with open(argv[2]) as file:
    dr = reader(file)
    for row in dr:
        dl = row

# store dna sequences in a string
dna = dl[0]
# create a dictionary where we will store the sequences we intend to count
all_sequences = {}

# extract the sequences from the database into a list
with open(argv[1]) as file:
    people = reader(file)
    for row in people:
        dnaSequences = row
        # remove name from row to get only the people dna sequences
        dnaSequences.pop(0)
        break

# copy the list in a dictionary where the genes are the sequence
for item in dnaSequences:
    all_sequences[item] = 1

# iterate trough the dna sequences for repititions and count
for sequence in all_sequences:
    l = len(sequence)
    tempMax = 0
    temp = 0
    #for(int i = l - len(dna),i > -1, --i)
    for i in range(len(dna)):
        # after having counted a sequence it skips at the end of it to avoid counting again
        while temp > 0:
            temp -= 1
            continue

        # if the segment of dna corresponds to the sequence and there is a repetition of it we start counting
        if dna[i: i + l] == sequence:
            while dna[i - l: i] == dna[i: i + l]:
                temp += 1
                i += l

            # it compares the value to the previous longest sequence and if it is longer it overrides it
            if temp > tempMax:
                tempMax = temp

    # store the longest sequences in the dictionary using the correspondent sequence
    all_sequences[sequence] += tempMax

# open and iterate trough the database of people
with open(argv[1], newline='') as file:
    # make people csv file a dictionary to compare with all_sequence dictionary
    people = DictReader(file)
    for person in people:
        match = 0
        # compares the sequences to every person and prints name before leaving the program if there is a match
        for dna in all_sequences:
            if all_sequences[dna] == int(person[dna]):
                match += 1
        if match == len(all_sequences):
            print(person['name'])
            exit()

    print("No match")
