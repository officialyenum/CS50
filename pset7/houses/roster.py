# TODO
import cs50
import csv
from sys import argv

# check command line
if len(argv) != 2:
    print("usage error, roster.py houseName")
    exit()

# Make house name lower to avoid cap sensitivity
housename = argv[1].lower()

# Check if argument is indeed a house at Hogwarts
houses = ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]

if housename.lower() not in houses:
    print("provide house name: Gryffindor, Hufflepuff, Slytherin or Ravenclaw.")
    exit()


#declare database
db = cs50.SQL("sqlite:///students.db")


files = db.execute('SELECT first, middle, last, birth FROM students WHERE lower(house) = "{}" ORDER BY last, first;'.format(housename))


for file in files:
    if not file['middle']:
        print("{} {}, born {}".format(file['first'], file['last'], file['birth']))
    else:
        print("{} {} {}, born {}".format(file['first'], file['middle'], file['last'], file['birth']))

    #if(file['middle'] == "\\N"):
    #    name = file['first'] +" "+ file['last']
    #    year = ", born "+ str(file['birth'])
    #    print(name,year)
    #else:
    #    name = file['first'] +" "+ file['middle'] +" "+file['last']
    #    year = ", born "+ str(file['birth'])
    #    print(name,year)