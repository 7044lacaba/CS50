# TODO

import cs50


def main():

    text = cs50.get_string("Text: ")

    # find letters
    letters = 0
    for i in text:
        if i.isalpha():
            letters += 1

    # find words
    words = 1
    for j in text:
        if j == (" "):
            words += 1

    # find sentences
    sentences = 0
    for k in text:
        if k == (".") or k == ("!") or k == ("?"):
            sentences += 1

    # l is average number of letters per 100 words
    l = ((letters / words) * 100)

    # s is average number of sentences per 100 words
    s = ((sentences / words) * 100)

    index = (0.0588 * l) - (0.296 * s) - 15.8
    index = round(index)

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


main()