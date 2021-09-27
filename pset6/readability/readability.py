from cs50 import get_string
import re
import math

#declare count variables
letter = 0
word = 0
sentence = 0

text = get_string("Text: ")

#iterate through text
for i in text:
    if i.isalpha():
        letter+= 1
#use regex to findall words and return the length
word=len(re.findall(r'\w+', text))
#use regex to findall sentences and return the length
sentence=len(re.findall(r'([A-Z][^\.!?]*[\.!?])', text))

L = 100.0 * letter / word
S = 100.0 * sentence / word
grade = round(0.0588 * (L) - 0.296 * (S) - 15.8)
if grade<1:
    print("Before Grade 1")
elif grade < 16:
    print(f"Grade {grade}")
else :
    print("Grade 16+");