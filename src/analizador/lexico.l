%{
  #include <iostream>
  #include <stdio.h>
  #include <string>
  #include "driver.h"
  #include "parser.tab.hh"
%}

%option noyywrap
%option case-insensitive
%option outfile="scanner.cc" 

DIGIT                   [0-9]
NUM                     [-+]?{DIGIT}+("."{DIGIT}+)?
RUTA                    (\"(\/([^\/\n\""])*)+\")|((\/([^\/\n\ ])*)+)|"\"/\""
CADENA                  [A-Za-z0-9._*?]+|(\"[A-Za-z0-9._?* ]+\")
ESPACIOS                [\n\s\r\t]
COMENTARIO              #[^#\n\r]*
FILEN                   ">file"({DIGIT}+)

%%

"mkdisk"                {return yy::Parser::make_MKDISK(yytext);}
"rmdisk"                {return yy::Parser::make_RMDISK(yytext);}
"fdisk"                 {return yy::Parser::make_FDISK(yytext);}
"mount"                 {return yy::Parser::make_MOUNT(yytext);}
"unmount"               {return yy::Parser::make_UNMOUNT(yytext);}
"mkfs"                  {return yy::Parser::make_MKFS(yytext);}
"login"                 {return yy::Parser::make_LOGIN(yytext);}
"logout"                {return yy::Parser::make_LOGOUT(yytext);}
"mkgrp"                 {return yy::Parser::make_MKGRP(yytext);}
"rmgrp"                 {return yy::Parser::make_RMGRP(yytext);}
"mkusr"                 {return yy::Parser::make_MKUSR(yytext);}
"rmusr"                 {return yy::Parser::make_RMUSR(yytext);}
"mkfile"                {return yy::Parser::make_MKFILE(yytext);}
"cat"                   {return yy::Parser::make_CAT(yytext);}
"remove"                {return yy::Parser::make_REMOVE(yytext);}
"edit"                  {return yy::Parser::make_EDIT(yytext);}
"rename"                {return yy::Parser::make_RENAME(yytext);}
"mkdir"                 {return yy::Parser::make_MKDIR(yytext);}
"copy"                  {return yy::Parser::make_COPY(yytext);}
"move"                  {return yy::Parser::make_MOVE(yytext);}
"find"                  {return yy::Parser::make_FIND(yytext);}
"chown"                 {return yy::Parser::make_CHOWN(yytext);}
"chgrp"                 {return yy::Parser::make_CHGRP(yytext);}
"chmod"                 {return yy::Parser::make_CHMOD(yytext);}
"pause"                 {return yy::Parser::make_PAUSE(yytext);}
"execute"               {return yy::Parser::make_EXECUTE(yytext);}
"rep"                   {return yy::Parser::make_REP(yytext);}
"recovery"              {return yy::Parser::make_RECOVERY(yytext);}
"loss"                  {return yy::Parser::make_LOSS(yytext);}

"full"                  {return yy::Parser::make_FULL(yytext);}
"2fs"                   {return yy::Parser::make_DOSFS(yytext);}
"3fs"                   {return yy::Parser::make_TRESFS(yytext);}
"mbr"                   {return yy::Parser::make_MBR(yytext);}
"disk"                  {return yy::Parser::make_DISK(yytext);}
"inode"                 {return yy::Parser::make_INODE(yytext);}
"Journaling"            {return yy::Parser::make_JOURNALING(yytext);}
"block"                 {return yy::Parser::make_BLOCK(yytext);}
"bm_inode"              {return yy::Parser::make_BMINODE(yytext);}
"bm_block"              {return yy::Parser::make_BMBLOCK(yytext);}
"tree"                  {return yy::Parser::make_TREE(yytext);}
"sb"                    {return yy::Parser::make_SB(yytext);}
"file"                  {return yy::Parser::make_FILE(yytext);}
"ls"                    {return yy::Parser::make_LS(yytext);}
{RUTA}                  {return yy::Parser::make_RUTA(yytext);}
{NUM}                   {return yy::Parser::make_NUM(yytext);}

">r"		            {return yy::Parser::make_R(yytext);}
">size"		            {return yy::Parser::make_SIZE(yytext);}
">path"		            {return yy::Parser::make_PATH(yytext);}
">fit"		            {return yy::Parser::make_FIT(yytext);}
">unit"		            {return yy::Parser::make_UNIT(yytext);}
">name"                 {return yy::Parser::make_NAME(yytext);}
">type"                 {return yy::Parser::make_TYPE(yytext);}
">delete"               {return yy::Parser::make_DELETE(yytext);}
">add"                  {return yy::Parser::make_ADD(yytext);}
">id"                   {return yy::Parser::make_ID(yytext);}
">fs"                   {return yy::Parser::make_FS(yytext);}
">user"                 {return yy::Parser::make_USER(yytext);}
">pass"                 {return yy::Parser::make_PASS(yytext);}
">grp"                  {return yy::Parser::make_GRP(yytext);}
">cont"                 {return yy::Parser::make_CONT(yytext);}
">destino"              {return yy::Parser::make_DESTINO(yytext);}
">ugo"                  {return yy::Parser::make_UGO(yytext);}
">ruta"                 {return yy::Parser::make_COMRUTA(yytext);}
{FILEN}                 {return yy::Parser::make_FILEN(yytext);}

"BF"                    {return yy::Parser::make_BF(yytext);}
"FF"                    {return yy::Parser::make_FF(yytext);}
"WF"                    {return yy::Parser::make_WF(yytext);}
"K"                     {return yy::Parser::make_K(yytext);}
"M"                     {return yy::Parser::make_M(yytext);}
"B"                     {return yy::Parser::make_B(yytext);}
"P"                     {return yy::Parser::make_P(yytext);}
"E"                     {return yy::Parser::make_E(yytext);}
"L"                     {return yy::Parser::make_L(yytext);}

"="		                {return yy::Parser::make_IGUAL(yytext);}
{CADENA}                {return yy::Parser::make_CADENA(yytext);}
{ESPACIOS}              {}
{COMENTARIO}            {std::cout <<"\e[1m "<< yytext << "\e[m"<<std::endl;}


[[:blank:]]     {}
.               {printf("\e[1;31m[ERROR]:\e[1;37m Caracter NO reconocido: \e[m%s\n",yytext);}
<<EOF>>		      {return yy::Parser::make_FIN();}
%%

void Driver::runScannerFile(){
    yy_flex_debug = false;
    yyin = fopen (file.c_str (), "r");
    if(yyin == NULL){
        std::cout<<"No se encontro el archivo de entrada"<<std::endl;
        exit(1);
    }
}

void Driver::runScanner(std:: string text){
    yy_flex_debug = true;
    YY_BUFFER_STATE buffer = yy_scan_string(text.c_str());
}

void Driver::closeFile(){
    fclose(yyin);
}