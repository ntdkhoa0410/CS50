# TODO
from cs50 import get_string

def count_letters(text):
    number = 0
    for  i in range (0, len(text)):
        if text[i].isalpha():
            number +=1
    return number

def count_words(text):
    words = text.split()
    return len(words)

def count_sentences(text):
    sentence = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentence += 1
    return sentence

def main():
    text = get_string("Text: ")
    letters_number = count_letters(text)
    words_number = count_words(text)
    sentences_number = count_sentences(text)
    L = letters_number / words_number * 100
    S = sentences_number / words_number * 100
    index =  0.0588 * L - 0.296 * S - 15.8
    if index < 0:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")
   # print(f"{sentences_number}")


if __name__ == "__main__":
    main()