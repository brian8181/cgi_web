#ifndef _REGEXPR_HPP
#define _REGEXPR_HPP

#include <string>

using std::string;

// punctuation
string punct1 = R"([-!"#$%&'()*+,./:;<=>?@[\\\]^_`{|}~])";
string punct2 = R"([-!"#%&'()*,./:;?@[\\\]_{}])"; //ascii
string punct3 = R"([$+<=>^`|~])"; //ascii
string name_exp = "[A-Za-z]+\\w*";
string variable = "\\{\\s*\\$(" + name_exp + ")\\s*\\}";

// smarty tag
string start = "\\{\\s*(";
string cmd1 = "((config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)|(\\*)|(#))?";
string cmd2 = "((\\*)|(#))?";
string ending = ")\\s*\\}";
string name = "\\s*([\\w\\$]*)\\s*";
string whole_tag = start + cmd1 + name + cmd2 + ending;

// smarty modifier
string var_modifier = "\\b\\$[A-Za-z][\\w]*\\s*\\|[\\w]+\\b";
string list1 = "capitalize|cat|count_characters|count_paragraphs|count_sentences|count_words|date_format";
string list2 = "default|escape|indent|lower|upper|nl2br|regex_replace|replace|regex_replace|regex_replace|strip|strip_tags|truncate|wordwarp";
string match_var_mod = var_modifier + list1 + "|" + list2 + "\\:[\\w\\p]*\b";

// smarty misc
string param = "\\{\\s*\\$([A-Za-z]+\\w*)\\b\\s*\\}"; // {$ABC}
string config =  "\\{\\s*#([^\\}]+)#\\s*\\}";         // {#ABC#}
string comment = "\\{\\s*\\*([^\\}]+)\\*\\s*\\}";     // {*ABC*}

string attib = "file|section|scope|global|once|assign";

#endif
