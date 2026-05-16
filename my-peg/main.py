import sys

import gen_gram as gram
import gen_token as token
# from write import Writer

def main(argc, argv):
    if argc < 3:
        print("Usage: python main.py <tokens_file> <grammar_file>")
        return -1

    a = token.Gen_Token(argv[1])
    a.open()
    a.gen_h()
    a.save(r"C:\Users\admin\Desktop\code\C-Mds-lang\Include\token.h")
    a.gen_c()
    a.save(r"C:\Users\admin\Desktop\code\C-Mds-lang\src\tokenize.c")

    return 0

if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))