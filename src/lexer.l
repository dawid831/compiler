%option noyywrap
%option yylineno


%{
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "parser.tab.hpp"
%}

%x COMMENT

%%

"#"             { BEGIN(COMMENT); }
<COMMENT>\n     { BEGIN(INITIAL); }
<COMMENT>.      ;

"PROGRAM"       return PROGRAM;
"IS"            return IS;
"IN"            return IN;
"END"           return END;

"PROCEDURE"     return PROCEDURE;

"IF"            return IF;
"THEN"          return THEN;
"ELSE"          return ELSE;
"ENDIF"         return ENDIF;

"WHILE"         return WHILE;
"DO"            return DO;
"ENDWHILE"      return ENDWHILE;

"FOR"           return FOR;
"FROM"          return FROM;
"TO"            return TO;
"DOWNTO"        return DOWNTO;
"ENDFOR"        return ENDFOR;

"REPEAT"        return REPEAT;
"UNTIL"         return UNTIL;

"READ"          return READ;
"WRITE"         return WRITE;

":="            return ASSIGN;
"!="            return NEQ;
"<="            return LEQ;
">="            return GEQ;

"+"             return PLUS;
"-"             return MINUS;
"*"             return MUL;
"/"             return DIV;
"%"             return MOD;

"="             return EQ;
"<"             return LT;
">"             return GT;

";"             return SEM;
":"             return COL;
","             return COM;
"("             return LBR;
")"             return RBR;
"["             return LSB;
"]"             return RSB;

"T"   return T;
"I"   return I;
"O"   return O;


[0-9]+          { 
                    #ifndef LEX_TEST
                        yylval.num = atoll(yytext);
                    #endif
                    return NUM;
                }
[_a-z]+         {
                    #ifndef LEX_TEST
                        yylval.id = strdup(yytext);
                    #endif
                        return PIDENTIFIER;
                }

[ \t\r\n]+      ;

.               {
                    std::cerr << "LEX ERROR line "
                              << yylineno << ": " << yytext << "\n";
                    exit(1);
                }

%%

#ifdef LEX_TEST
const char* token_name(int t) {
    switch (t) {
        case PROGRAM: return "PROGRAM";
        case IS: return "IS";
        case IN: return "IN";
        case END: return "END";

        case PROCEDURE: return "PROCEDURE";

        case IF: return "IF";
        case THEN: return "THEN";
        case ELSE: return "ELSE";
        case ENDIF: return "ENDIF";

        case WHILE: return "WHILE";
        case DO: return "DO";
        case ENDWHILE: return "ENDWHILE";

        case FOR: return "FOR";
        case FROM: return "FROM";
        case TO: return "TO";
        case DOWNTO: return "DOWNTO";
        case ENDFOR: return "ENDFOR";

        case REPEAT: return "REPEAT";
        case UNTIL: return "UNTIL";

        case READ: return "READ";
        case WRITE: return "WRITE";

        case ASSIGN: return "ASSIGN";
        case NEQ: return "NEQ";
        case LEQ: return "LEQ";
        case GEQ: return "GEQ";

        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";

        case EQ: return "EQ";
        case LT: return "LT";
        case GT: return "GT";

        case SEM: return "SEM";
        case COM: return "COM";
        case LBR: return "LBR";
        case RBR: return "RBR";
        case LSB: return "LSB";
        case RSB: return "RSB";

        case NUM: return "NUM";
        case PIDENTIFIER: return "PIDENTIFIER";

        default: return "UNKNOWN";
    }
}

int main() {
    int t;
    while ((t = yylex())) {
        std::cout << "TOKEN: " << token_name(t)
                  << " at line " << yylineno << "\n";
    }
    return 0;
}
#endif


