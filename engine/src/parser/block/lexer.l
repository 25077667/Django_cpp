%{
#include "parser.hpp"
#include "scanner.hpp"
#include <sstream>
#define YY_DECL int Scanner::lex(Block_parser::semantic_type *yylval)

// workaround for bug in flex 2.6.4
#define yypanic(X) (void)(X)
%}

%option c++ interactive noyywrap noyylineno nodefault

CTRL_OPEN       \{\%
CTRL_CLOSE      \%\}
ID              [A-Za-z_\$][_[:alnum:]\$]*
CTX             .+
BLOCK_OPEN_HEAD ({CTRL_OPEN}" block ")
BLOCK_OPEN_TAIL (" "{CTRL_CLOSE})
BLOCK_CLOSE     ({CTRL_OPEN}" endblock "{CTRL_CLOSE})

%%

{BLOCK_OPEN_HEAD}   return Block_parser::token::BLOCK_OPEN_HEAD;
{BLOCK_OPEN_TAIL}   return Block_parser::token::BLOCK_OPEN_TAIL;
{BLOCK_CLOSE}       return Block_parser::token::BLOCK_CLOSE;
{ID}                return Block_parser::token::ID;
{CTX}               return Block_parser::token::CTX;

%%

int yyFlexLexer::yylex() {
    throw std::runtime_error("Invalid call to yyFlexLexer::yylex()");
}

// Return a string for json format
std::string block_parser_entry(const std::string& to_be_parsed) {
    //! CRITICAL: how to get the output from lex/yacc parsed context 
    std::ostream os;
    Block_parser(Scanner(std::istringstream{to_be_parsed})).parse();
    return os.str();
}