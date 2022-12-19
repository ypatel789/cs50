text = input("Text: ")

letters = 0
words = 1
sentences = 0

text_length = len(text)

for i in range(text_length):
    if (text[i].isalpha()):
        letters += 1

    if (text[i].isspace()):
        words += 1

    if (text[i] == "." or text[i] == "?" or text[i] == "!"):
        sentences += 1

L = float(letters) / float(words) * 100
S = float(sentences) / float(words) * 100

index = round(0.0588 * float(L) - 0.296 * float(S) - 15.8)
index = int(index)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade " + str(index))