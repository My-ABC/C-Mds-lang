# 生成token
# 文件格式:
# TOKEN 或 TOKEN ...

from write import Writer

class Gen_Token(Writer):
    def __init__(self, tokens_file):
        super().__init__()
        self.files = tokens_file
        self.tokens_text_lines = []

    def open(self):
        with open(self.files, "r") as f:
            self.tokens_text_lines = f.readlines()

    def gen(self):
        # TODO: 生成token
        self.kw = {}
        for line in self.tokens_text_lines:
            if line.startswith("#") or line.strip() == "":
                continue
            L = line.split()
            if len(L) == 1:
                self.kw[L[0]] = ''
            elif len(L) == 2:
                if not (L[1].startswith('"') and L[1].endswith('"')):
                    raise Exception('没有引号')
                self.kw[L[0]] = L[1].split("'")[1] # 没去引号

            else:
                raise Exception(f"Invalid token line: {line}")
    
    def gen_h(self):
        self.gen()
        self.clear()

        self.write('typedef enum _token {\n') # TODO: 生成token枚举
        for k in self.kw.keys():
            with self.indent():
                self.write(f'TOKEN_{k},\n')
        with self.indent():
            self.write('TOKEN_NL,\n')
            self.write('TOKEN_EOF\n')
        self.write('} TokenType;\n\n')

        self.write("typedef struct _tokeninfo {\n") # TODO: 生成token信息结构体
        with self.indent():
            self.write("TokenType type;\n")
            self.write("char *text;\n")
            self.write("int start_pos;\n")
            self.write("int end_pos;\n")
        self.write("} TokenInfo;\n\n")

        self.write("TokenInfo *get_next_token(const char* input, int *pos);\n")

    def gen_c(self):
        self.clear()  
        self.gen()

        self.write('#include <stdlib.h>\n')
        self.write('#include <string.h>\n')
        self.write('#include <ctype.h>\n')
        self.write('#include "token.h"\n')
        self.write('#include "hardtokens.h"\n\n')

        self.write("#if defined(_WIN32) || defined(_WIN64)\n")
        self.write("static char* strndup(const char* s, size_t n) {\n")
        with self.indent():
            self.write("size_t len = 0;\n")
            self.write('const char* p = s;\n')
            self.write("while (len < n && *p) {\n")
            with self.indent():
                self.write("len++;\n")
                self.write("p++;\n")
            self.write("}\n")
            self.write("char* result = (char*)malloc(len + 1);\n")
            self.write("if (result) {\n")
            with self.indent():
                self.write("memcpy(result, s, len);\n")
                self.write("result[len] = '\\0';\n")
            self.write("}\n")
            self.write("return result;\n")
        self.write("}\n\n")
        self.write("#endif\n\n")

        self.write("TokenInfo *get_next_token(const char* input, int *pos) {\n") #TODO: 生成获取下一个token的函数声明
        with self.indent():
            self.write("if (input[*pos] == '\\0') {\n")
            with self.indent():
                self.write(f'TokenInfo *token = malloc(sizeof(TokenInfo));\n')
                self.write(f'if (token == NULL) {{\n')
                with self.indent():
                    self.write('return NULL;\n')
                self.write('}\n')
                self.write(f'token->type = TOKEN_EOF;\n')
                self.write(f'token->text = NULL;\n')
                self.write(f'token->start_pos = *pos;\n')
                self.write(f'token->end_pos = *pos;\n')
                self.write('return token;\n')
            self.write("}\n")

            self.write("if (input[*pos] == '\\n') {\n")
            with self.indent():
                self.write(f'TokenInfo *token = malloc(sizeof(TokenInfo));\n')
                self.write(f'if (token == NULL) {{\n')
                with self.indent():
                    self.write('return NULL;\n')
                self.write('}\n')
                self.write(f'token->type = TOKEN_NL;\n')
                self.write(f'token->text = NULL;\n')
                self.write(f'token->start_pos = *pos;\n')
                self.write(f'token->end_pos = *pos + 1;\n')
                self.write(f'*pos += 1;\n')
                self.write('return token;\n')
            self.write("}\n")

            self.write("if (input[*pos] == ' ') {\n")
            with self.indent():
                self.write(f'*pos += 1;\n')
                self.write('return get_next_token(input, pos);\n')
            self.write("}\n")

            for k, v in self.kw.items():
                if v != '':
                    if len(v) == 1:
                        self.write(f'if (input[*pos] == \'{v}\') {{\n')
                        with self.indent():
                            self.write(f'TokenInfo *token = malloc(sizeof(TokenInfo));\n')
                            self.write(f'if (token == NULL) {{\n')
                            with self.indent():
                                self.write('return NULL;\n')
                            self.write('}\n')
                            self.write(f'token->type = TOKEN_{k};\n')
                            self.write(f'token->text = strndup(input + *pos, {len(v)});\n')
                            self.write(f'token->start_pos = *pos;\n')
                            self.write(f'token->end_pos = *pos + {len(v)};\n')
                            self.write(f'*pos += {len(v)};\n')
                            self.write('return token;\n')
                        self.write('}\n')
                    else:
                        self.write(f'if (strncmp(input + *pos, "{v}", {len(v)}) == 0) {{\n')
                        with self.indent():
                            self.write(f'TokenInfo *token = malloc(sizeof(TokenInfo));\n')
                            self.write(f'if (token == NULL) {{\n')
                            with self.indent():
                                self.write('return NULL;\n')
                            self.write('}\n')
                            self.write(f'token->type = TOKEN_{k};\n')
                            self.write(f'token->text = strndup(input + *pos, {len(v)});\n')
                            self.write(f'token->start_pos = *pos;\n')
                            self.write(f'token->end_pos = *pos + {len(v)};\n')
                            self.write(f'*pos += {len(v)};\n')
                            self.write('return token;\n')
                        self.write('}\n')       
                else:
                    self.write(f'TokenInfo *token = get_token_{k}(input, pos);\n')
                    self.write("if (token != NULL) {\n")
                    with self.indent():
                        self.write('return token;\n')
                    self.write("}\n")
            self.write("return NULL;\n")
        self.write("}\n")

    def get(self):
        return self._out
    
    def save(self, filename):
        with open(filename, mode='w') as f:
            f.write(self._out)