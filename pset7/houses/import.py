# TODO
import cs50
import csv
from sys import argv

# check command line
if len(argv) != 2:
    print("usage error, import.py characters.csv")
    exit()

csv_file = argv[1]

if not (csv_file.endswith(".csv")):
    print("You must provide a *.csv file")
    exit()

#declare database
db = cs50.SQL("sqlite:///students.db")

#open csv
with open(csv_file, "r") as file:
    students = csv.DictReader(file)
    #for each row parse name
    for row in students:
        names = []
        for part in row["name"].split(" "):
            names.append(part)

        names.append(row["house"])
        names.append(row["birth"])

        if (len(names) == 5):
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", names[:5])

        if (len(names) == 4):
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", names[:4])


        #names = row['name']
        #namesDict = names.split()
        #print(len(namesDict))
        #if len(namesDict) == 2:
        #    firstName = namesDict[0]
        #    middleName = "\\N";
        #    lastName = namesDict[1]
        #    house = row['house']
        #    birth = row['birth']
        #    #insert each student into the students table of students.db
        #    db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)", firstName, middleName, lastName, house, birth)
        #else:
        #    firstName = namesDict[0]
        #    middleName = namesDict[2]
        #    lastName = namesDict[1]
        #    house = row['house']
        #    birth = row['birth']
        #    #insert each student into the students table of students.db
        #    db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)", firstName, middleName, lastName, house, birth)