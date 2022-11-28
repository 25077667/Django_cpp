%{
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <exception>
#include <FlexLexer.h>
using json = nlohmann::json;
%}

%require "3.2"
%language "C++"
%define api.parser.class {Block_parser}
%code { #include "scanner.hpp" }
%code requires { #include <nlohmann/json.hpp> }
%define api.value.type variant
%parse-param {Scanner* scanner}

%token BLOCK_OPEN_HEAD BLOCK_OPEN_TAIL CTX BLOCK_CLOSE ID

%code {
namespace detail {
        json gen_single_block(const std::string& name, const std::string& ctx) {
                return json{{"name", name}, {"ctx", ctx}};
        }
}
}

%%
// Grammar section

blocks  : %empty        { $$ = json{}.dump(); }
        | blocks block  { $$ += $2; }
        | error         { throw std::runtime_error($1); }
        ; 

block   : block_open block_ctx BLOCK_CLOSE { $$ = detail::gen_single_block($1, $2).dump(); }
        ;

block_open
        : BLOCK_OPEN_HEAD ID BLOCK_OPEN_TAIL { $$ = $2; }

block_ctx
        : blocks { $$ = $1; }
        | CTX    { $$ = $1; }
        ;
%%