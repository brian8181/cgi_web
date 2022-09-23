#ifndef _REGEXPR_HPP
#define _REGEXPR_HPP

#include <string>
#include <regex>

using std::string;

const string SYMBOL_NAME = "\\$[-._~]*[A-Za-z][-.~A-Za-z0-9]*";
const string INT_LITERAL = "/d*[.]?/d+";
const string BOOL_LITERAL = "true|false";
const string STRING_LITERAL = "(\\'[\\w*\\.]*\\')|(\\\"[\\w\\.]*\\\")";  // 'ABC' or "ABC"
const string COMMAND = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)";
const string COMMENT = "\\n?\\{\\s*\\*[\\w\\s\\p]*\\*\\s*\\}\\n?";
const string CONFIG = "\\{\\s*#([A-Aa-z]\\w*)#\\s*\\}";


const string VARIABLE = "\\{\\s*\\$(" + SYMBOL_NAME + ")\\s*\\}";
const string INCLUDE = "\\{\\s*\\include file\\s*=\\s*\"(.*?)\"\\s*\\}";
const string CONFIG_LOAD = "\\{\\config_load file=\"(.*?)\"\\}";
const string LOAD_CONFIG_VALUE = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
const string LOAD_CONFIG_NAME = "([A-Za-z]+\\w*)";
const string COMMENT_OR_VARIABLE = "((" + COMMENT + ")" +  "|" + "(" + VARIABLE + "))";
const string ARRAY_KEYWORD = "array\\(" + STRING_LITERAL + "\\)";
<<<<<<< HEAD

const string LIT_VAL = INT_LITERAL + "|" + BOOL_LITERAL;
const string TEXT = "([,+_~.$\\w\\d]+)\\n";
//const string TEXT = "([0-9]+)\\n";
const string IF_KEYWORD = "\\{if\\s+" + SYMBOL_NAME  + "\\s*\\}\\n";
=======
const string TEXT = "(([,+_~.$\\s\\w\\d])+\n)|(\\s*\\$(" + SYMBOL_NAME + ")\\s*\n)";
//const string TEXT = "([,+_~.$\\s\\w\\d]+)\\n"
const string IF_KEYWORD = "\\{if\\s+\\$" + SYMBOL_NAME + "\\s*\\}\\n";
>>>>>>> eca746c427c5571a657f177bdac167fc8e75d27c
const string ELSE_KEYWORD = "\\{else\\}\\n";
const string ELSEIF_KEYWORD = "\\{else if\\s+" + SYMBOL_NAME  + "\\s*\\}\\n";;
const string ENDIF_KEYWORD = "\\{/if\\}\\n";
//const string IF_SEQUENCE  = "(" + IF_KEYWORD + TEXT + ENDIF_KEYWORD + ")|(" + IF_KEYWORD + TEXT + ELSE_KEYWORD + TEXT + ENDIF_KEYWORD + ")"; 
const string IF_SEQUENCE  = "(" + IF_KEYWORD + TEXT + ENDIF_KEYWORD + ")|(" + IF_KEYWORD + TEXT + ELSE_KEYWORD + TEXT + ENDIF_KEYWORD + ")"; 

const string FOREACH_KEYWORD = "\\{foreach\\s+\\$" + SYMBOL_NAME + "\\s*\\}\\n";
const string ENDFOREACH_KEYWORD = "\\{/foreach\\}\\n";
const string FOREACH_SEQUENCE = FOREACH_KEYWORD + TEXT + ENDFOREACH_KEYWORD;

// const string DEFAULT_FUNCTION = "\\|default:'(.*)'";
// const string CAT_FUNCTION = "\\|cat:'(.*)'";
// const string CAPITALIZE_FUNCTION = "\\|capitalize(:true)?";
// const string LOWER_FUNCTION = "\\|lower(:true)?";
// const string UPPER_FUNCTION = "\\|upper(:true)?";

#endif
