%skeleton "lalr1.cc" /* -*- C++ -*- */

%defines
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant

%define parse.trace
%define parse.error verbose
%param { Driver& driver }


%code requires
{
   class Driver;
}

%{
   
   #include <string>
   #include <stdio.h>
   #include "driver.h"
   #include <iostream>
   using namespace std;
%}


/******* TERMINALES ********/
%token <std::string> MKDISK"mkdisk" RMDISK"rmdisk" FDISK"fdisk" MOUNT"mount" UNMOUNT"unmount" MKFS"mkfs" LOGIN"login" LOGOUT"logout" MKGRP"mkgrp" RMGRP"rmgrp" MKUSR"mkusr" RMUSR"rmusr" MKFILE"mkfile" CAT"cat" REMOVE"remove" EDIT"edit" RENAME"rename" MKDIR"mkdir" COPY"copy" MOVE"move" FIND"find" CHOWN"chown" CHGRP"chgrp" CHMOD"chmod" PAUSE"pause" EXECUTE"execute" REP"rep" FULL"full" BESTFIT"BestFit" FIRSTFIT"FirstFit" WORSTFIT"WorstFit" DOSFS"2fs" TRESFS"3fs" MBR"mbr" DISK"disk" INODE"inode" JOURNALING"journaling" BLOCK"block" BMINODE"bm_inode" BMBLOCK"bm_block" TREE"tree" SB"sb" FILE"file" LS"ls" IGUAL"=" R">r" SIZE">size" PATH">path" FIT">fit" UNIT">UNIT" NAME">name" TYPE">type" DELETE">delete" ADD">add" ID">id" FS">fs" USER">user" PASS">pass" GRP">grp" CONT">cont" DESTINO">destino" UGO">ugo" COMRUTA">ruta" FILEN"FILEN" BF"BF" FF"FF" WF"WF" K"K" M"M" B"B" P"P" E"E" L"L"  RUTA"RUTA" CADENA"CADENA"
%token <float> NUM "NUM"                     
%token FIN 0 "eof"                    

/******* NO TERMINALES ********/
%start Inicio;                
/****************************************************************GRAMATICA***********************************************************/
%%
   Inicio 
      : Lista                       {}
   ;                     


   Lista
      : Lista COMANDO               {}
      | COMANDO                     {}
   ;

   COMANDO 
      : MKDISK Lista_parametrosmkdisk
      {
        std::cout << "COMANDO MKDISK:" << std::endl;
      }
      | RMDISK PATH IGUAL RUTA
      {
         std::cout << "COMANDO RMDISK" << std::endl;
         std::cout << "RUTA: "<< $4 << std::endl;
      }
      | FDISK Lista_fdisk
      {
         std::cout << "COMANDO FDISK:" << std::endl;
      }
      | MOUNT PATH IGUAL RUTA NAME IGUAL CADENA
      {
         std::cout << "COMANDO MOUNT" << std::endl;
         std::cout << "RUTA: "<< $4 << std::endl;
         std::cout << "NAME: "<< $7 << std::endl;
      }
      | MOUNT NAME IGUAL CADENA PATH IGUAL RUTA
      {
         std::cout << "COMANDO MOUNT" << std::endl;
         std::cout << "RUTA: "<< $4 << std::endl;
         std::cout << "NAME: "<< $7 << std::endl;
      }
      | UNMOUNT ID IGUAL CADENA
      {
         std::cout << "COMANDO UNMOUNT" << std::endl;
         std::cout << "ID: "<< $4 << std::endl;
      }
      | MKFS Lista_mkfs
      {
         std::cout << "COMANDO MKFS" << std::endl;
      }
      | LOGIN Lista_login
      {
         std::cout << "COMANDO LOGIN" << std::endl;
      }
      | LOGOUT
      {
         std::cout << "COMANDO LOGOUT" << std::endl;
      }
      | MKGRP NAME IGUAL CADENA
      {
         std::cout << "COMANDO MKGRP" << std::endl;
         std::cout << "NAME: "<< $4 << std::endl;
      }
      | RMGRP NAME IGUAL CADENA
      {
         std::cout << "COMANDO RMGRP" << std::endl;
         std::cout << "NAME: "<< $4 << std::endl;
      }
      | RMUSR USER IGUAL CADENA
      {
         std::cout << "COMANDO RMUSR" << std::endl;
         std::cout << "USER: "<< $4 << std::endl;
      }
      | MKUSR Lista_mkusr
      {
         std::cout << "COMANDO MKUSR" << std::endl;
      }
      | MKFILE Lista_mkfile
      {
         std::cout << "COMANDO MKFILE" << std::endl;
      }
      | CAT Lista_cat
      {
         std::cout << "COMANDO CAT" << std::endl;
      }
      | REMOVE PATH IGUAL RUTA
      {
         std::cout << "COMANDO REMOVE" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
      }
      | EDIT PATH IGUAL RUTA CONT IGUAL RUTA
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "CONT: "<< $7 << std::endl;
      }
      | EDIT CONT IGUAL RUTA PATH IGUAL RUTA
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< $7 << std::endl;
         std::cout << "CONT: "<< $4 << std::endl;
      }
      | RENAME PATH IGUAL RUTA NAME IGUAL CADENA
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "NAME: "<< $7 << std::endl;
      }
      | RENAME NAME IGUAL CADENA PATH IGUAL RUTA
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< $7 << std::endl;
         std::cout << "NAME: "<< $4 << std::endl;
      }
      | MKDIR PATH IGUAL RUTA
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
      }
      | MKDIR PATH IGUAL RUTA R
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "R" << std::endl;
      }
      | MKDIR R PATH IGUAL RUTA
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< $5 << std::endl;
         std::cout << "R" << std::endl;
      }
      | COPY PATH IGUAL RUTA DESTINO IGUAL RUTA
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "DESTINO: "<< $7 << std::endl;
      }
      | COPY DESTINO IGUAL RUTA PATH IGUAL RUTA
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< $7 << std::endl;
         std::cout << "DESTINO: "<< $4 << std::endl;
      }
      | MOVE PATH IGUAL RUTA DESTINO IGUAL RUTA
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "DESTINO: "<< $7 << std::endl;
      }
      | MOVE DESTINO IGUAL RUTA PATH IGUAL RUTA
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< $7 << std::endl;
         std::cout << "DESTINO: "<< $4 << std::endl;
      }
      | FIND PATH IGUAL RUTA NAME IGUAL CADENA
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< $4 << std::endl;
         std::cout << "NAME: "<< $7 << std::endl;
      }
      | FIND NAME IGUAL CADENA PATH IGUAL RUTA
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< $7 << std::endl;
         std::cout << "NAME: "<< $4 << std::endl;
      }
      | CHOWN Lista_chown
      {
         std::cout << "COMANDO CHOWN" << std::endl;
      }
      | CHGRP USER IGUAL CADENA GRP IGUAL CADENA
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< $4 << std::endl;
         std::cout << "GRP: "<< $7 << std::endl;
      }
      | CHGRP GRP IGUAL CADENA USER IGUAL CADENA
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< $7 << std::endl;
         std::cout << "GRP: "<< $4 << std::endl;
      }
      | CHMOD Lista_chmod
      {
         std::cout << "COMANDO CHMOD" << std::endl;
      }
      | EXECUTE PATH IGUAL RUTA
      {
        std::cout << "COMANDO EXECUTE" << std::endl;
        std::cout << "RUTA: "<< $4 << std::endl;
      }
      | REP Lista_rep
      {
         std::cout << "COMANDO REP" << std::endl;
      }
      | PAUSE
      {
        std::cout << "Presione una tecla para continuar..." << std::endl;
        std::cin.ignore();
      }
   ;

   Lista_parametrosmkdisk
      :Lista_parametrosmkdisk parametromk  {}
      | parametromk                   {}
   ;

    parametromk
    : SIZE IGUAL NUM
    {
        std::cout << "SIZE: " << $3 << std::endl;
    }
    | FIT IGUAL BF
    {
        std::cout << "FIT: BEST"<< std::endl;
    }
    | FIT IGUAL FF
    {
        std::cout << "FIT: FIRST"<< std::endl;
    }
    | FIT IGUAL WF
    {
        std::cout << "FIT: WORST"<< std::endl;
    }
    | UNIT IGUAL K
    {
        std::cout << "UNIDADES: KILOBYTES" << std::endl;
    }
    | UNIT IGUAL M 
    {
        std::cout << "UNIDADES: MEGABYTES" << std::endl;
    }
    | PATH IGUAL RUTA
    {
        std::cout << "RUTA: "<< $3 << std::endl;
    }
   ;

   Lista_fdisk
      : Lista_fdisk parametrofdisk  {}
      | parametrofdisk              {}
   ;

   parametrofdisk
      : SIZE IGUAL NUM
      {
         std::cout << "SIZE: " << $3 << std::endl;
      }
      | PATH IGUAL RUTA
      {
         std::cout << "PATH: " << $3 << std::endl;
      }
      | NAME IGUAL CADENA
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | UNIT IGUAL B
      {
         std::cout << "UNIT: BYTES" << std::endl;
      }
      | UNIT IGUAL K
      {
         std::cout << "UNIT: KILOBYTES" << std::endl;
      }
      | UNIT IGUAL M
      {
         std::cout << "UNIT: MEGABYTES" << std::endl;
      }
      | TYPE IGUAL P
      {
         std::cout << "TYPE: PRIMARY"<< std::endl;
      }
      | TYPE IGUAL E
      {
         std::cout << "TYPE: EXTEND" <<std::endl;
      }
      | TYPE IGUAL L
      {
         std::cout << "TYPE: LOGIC" << std::endl;
      }
      | FIT IGUAL BF
      {
         std::cout << "FIT: " << $3 << std::endl;
      }
      | FIT IGUAL FF
      {
         std::cout << "FIT: " << $3 << std::endl;
      }
      | FIT IGUAL WF
      {
         std::cout << "FIT: " << $3 << std::endl;
      }
      | DELETE IGUAL FULL
      {
         std::cout << "DELETE: " << $3 << std::endl;
      }
      | ADD IGUAL NUM
      {
         std::cout << "ADD: " << $3 << std::endl;
      }
   ;

   Lista_mkfs
      : Lista_mkfs param_mkfs                   {}
      | param_mkfs                              {}
   ;

   param_mkfs
      : ID IGUAL CADENA
      {
         std::cout << "ID: " << $3 << std::endl;
      }
      | TYPE IGUAL FULL
      {
         std::cout << "TYPE: " << $3 << std::endl;
      }
      | FS IGUAL DOSFS
      {
         std::cout << "FS: " << $3 << std::endl;
      }
      | FS IGUAL TRESFS
      {
         std::cout << "FS: " << $3 << std::endl;
      }
   ;

   Lista_login
      : Lista_login param_login              {}
      | param_login                          {}
   ;

   param_login
      : USER IGUAL CADENA
      {
         std::cout << "USER: " << $3 << std::endl;
      }
      | PASS IGUAL CADENA
      {
         std::cout << "PASSWORD: " << $3 << std::endl;
      }
      | PASS IGUAL NUM
      {
         std::cout << "PASSWORD: " << $3 << std::endl;
      }
      | ID IGUAL CADENA
      {
         std::cout << "ID: " << $3 << std::endl;
      }
   ;

   Lista_mkusr
      : Lista_mkusr param_mkusr              {}
      | param_mkusr                          {}
   ;

   param_mkusr
      : USER IGUAL CADENA
      {
         std::cout << "USER: " << $3 << std::endl;
      }
      | PASS IGUAL CADENA
      {
         std::cout << "PASS: " << $3 << std::endl;
      }
      | PASS IGUAL NUM
      {
         std::cout << "PASS: " << $3 << std::endl;
      }
      | GRP IGUAL CADENA
      {
         std::cout << "GROUP: " << $3 << std::endl;
      }
   ;

   Lista_mkfile
      : Lista_mkfile param_mkfile              {}
      | param_mkfile                           {}
   ;

   param_mkfile
      : PATH IGUAL RUTA
      {
         std::cout << "PATH: " << $3 << std::endl;
      }
      | R 
      {
         std::cout << "R " << std::endl;
      }
      | SIZE IGUAL NUM
      {
         std::cout << "SIZE: " << $3 << std::endl;
      }
      | CONT IGUAL RUTA
      {
         std::cout << "CONT: " << $3 << std::endl;
      }
   ;

   Lista_cat
      : Lista_cat param_cat            {}
      | param_cat                      {}
   ;

   param_cat
      : FILEN IGUAL RUTA
      {
         std::cout << "RUTA: " << $3 << std::endl;
         std::cout << "FILE: " << $1 << std::endl;
      }
   ;

   Lista_chown
      : Lista_chown param_chown
      | param_chown
   ;

   param_chown
      : PATH IGUAL RUTA
      {
         std::cout << "RUTA: " << $3 << std::endl;
      }
      | USER IGUAL CADENA
      {
         std::cout << "USER: " << $3 << std::endl;
      }
      | R
      {
         std::cout << "R" << std::endl;
      }
   ;

   Lista_chmod
      : Lista_chmod param_chmod
      | param_chmod
   ;

   param_chmod
      : PATH IGUAL RUTA
      {
         std::cout << "RUTA: " << $3 << std::endl;
      }
      | UGO IGUAL NUM
      {
         std::cout << "UGO: " << $3 << std::endl;
      }
      | R
      {
         std::cout << "R" << std::endl;
      }
   ;

   Lista_rep
      : Lista_rep param_rep
      | param_rep
   ;

   param_rep
      : NAME IGUAL MBR
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL DISK
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL INODE
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL JOURNALING
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL BLOCK
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL BMINODE
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL BMBLOCK
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL TREE
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL SB
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL FILE
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | NAME IGUAL LS
      {
         std::cout << "NAME: " << $3 << std::endl;
      }
      | PATH IGUAL RUTA
      {
         std::cout << "PATH: " << $3 << std::endl;
      }
      | ID IGUAL CADENA
      {
         std::cout << "ID: " << $3 << std::endl;
      }
      | COMRUTA IGUAL RUTA
      {
         std::cout << "RUTA: " << $3 << std::endl;
      }
   ;

%%

void yy::Parser::error( const std::string& error){
  std::cout << error << std::endl;
}