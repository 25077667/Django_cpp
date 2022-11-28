class Scanner : public yyFlexLexer {
   public:
    Scanner(std::istream& arg_yyin) : yyFlexLexer(arg_yyin, std::cout.rdbuf()) {}
    int lex(Block_parser::semantic_type* yylval);  // note: this is the prototype we need
};

std::string block_parser_entry(const std::string& to_be_parsed);
#define yylex(x) scanner->lex(x)