#include <cstdio>
#include <cstdlib>
#include <iostream>

extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <input_file> <output_file>\n";
        return 1;
    }

    // open input
    FILE* in = fopen(argv[1], "r");
    if (!in) {
        perror("Cannot open input file");
        return 1;
    }

    // open output
    FILE* out = fopen(argv[2], "w");
    if (!out) {
        perror("Cannot open output file");
        fclose(in);
        return 1;
    }

    // redirect lexer input
    yyin = in;

    // redirect stdout (codegen pisze na cout)
    if (!freopen(argv[2], "w", stdout)) {
        perror("Cannot redirect stdout");
        fclose(in);
        fclose(out);
        return 1;
    }

    // parse & generate
    yyparse();

    fclose(in);
    fclose(out);
    return 0;
}
