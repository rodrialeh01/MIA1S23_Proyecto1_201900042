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
   class Execute;
   class Mkdisk;
   class Rmdisk;
   class Fdisk;
}

%{
   
   #include <string>
   #include <stdio.h>
   #include "driver.h"
   #include <iostream>
   #include "../Comandos/Execute.h"
   #include "../Comandos/Mkdisk.h"
   #include "../Comandos/Rmdisk.h"
   #include "../Comandos/Fdisk.h"

   std::string dsk_size = "";
   std::string path = "";
   std::string fit = "";
   std::string unit = ""; 
   std::string name = "";
   std::string type = "";
   std::string delete_ = "";
   std::string add = "";

%}


/******* TERMINALES ********/
%token <std::string> MKDISK"mkdisk" RMDISK"rmdisk" FDISK"fdisk" MOUNT"mount" UNMOUNT"unmount" MKFS"mkfs" LOGIN"login" LOGOUT"logout" MKGRP"mkgrp" RMGRP"rmgrp" MKUSR"mkusr" RMUSR"rmusr" MKFILE"mkfile" CAT"cat" REMOVE"remove" EDIT"edit" RENAME"rename" MKDIR"mkdir" COPY"copy" MOVE"move" FIND"find" CHOWN"chown" CHGRP"chgrp" CHMOD"chmod" PAUSE"pause" EXECUTE"execute" REP"rep" FULL"full" BESTFIT"BestFit" FIRSTFIT"FirstFit" WORSTFIT"WorstFit" DOSFS"2fs" TRESFS"3fs" MBR"mbr" DISK"disk" INODE"inode" JOURNALING"journaling" BLOCK"block" BMINODE"bm_inode" BMBLOCK"bm_block" TREE"tree" SB"sb" FILE"file" LS"ls" IGUAL"=" R">r" SIZE">size" PATH">path" FIT">fit" UNIT">UNIT" NAME">name" TYPE">type" DELETE">delete" ADD">add" ID">id" FS">fs" USER">user" PASS">pass" GRP">grp" CONT">cont" DESTINO">destino" UGO">ugo" COMRUTA">ruta" FILEN"FILEN" BF"BF" FF"FF" WF"WF" K"K" M"M" B"B" P"P" E"E" L"L"  RUTA"RUTA" CADENA"CADENA"
%token <std::string> NUM "NUM"                     
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
         Mkdisk *nuevo_disco = new Mkdisk();
         if(dsk_size != ""){
            nuevo_disco->size = stoi(dsk_size);
         }else{
            nuevo_disco->size = 0;
         }   
         nuevo_disco->path = path;
         nuevo_disco->fit = fit;
         nuevo_disco->unit = unit;
         nuevo_disco->CrearDisco(nuevo_disco);
         path = "";
         fit = "";
         unit = "";
         dsk_size = "";
      }
      | RMDISK PATH IGUAL RUTA
      {
         Rmdisk *disco = new Rmdisk();
         disco->path = $4;
         disco->EliminarDisco(disco);
         path = "";
      }
      | FDISK Lista_fdisk
      {
         Fdisk *particion = new Fdisk();
         if(dsk_size != ""){
            particion->size = stoi(dsk_size);
         }else{
            particion->size = 0;
         }
         particion->path = path;
         particion->fit = fit;
         particion->unit = unit;
         particion->name = name;
         particion->type = type;
         particion->dsk_delete = delete_;
         if(add != ""){
            particion->add = stoi(add);
         }else{
            particion->add = 0;
         }
         particion->SistemaDeParticiones(particion);
         path = "";
         fit = "";
         unit = "";
         dsk_size = "";
         name = "";
         type = "";
         delete_ = "";
         add = "";
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
        Execute *exec = new Execute();
        exec->path = $4;
        exec->AnalizarArchivo(exec);
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
        dsk_size = $3;
    }
    | FIT IGUAL BF
    {
        fit = $3;
    }
    | FIT IGUAL FF
    {
        fit = $3;
    }
    | FIT IGUAL WF
    {
        fit = $3;
    }
    | UNIT IGUAL K
    {
        unit = $3;
    }
    | UNIT IGUAL M 
    {
        unit = $3;
    }
    | PATH IGUAL RUTA
    {
        path = $3;
    }
   ;

   Lista_fdisk
      : Lista_fdisk parametrofdisk  {}
      | parametrofdisk              {}
   ;

   parametrofdisk
      : SIZE IGUAL NUM
      {
         dsk_size = $3;
      }
      | PATH IGUAL RUTA
      {
         path = $3;
      }
      | NAME IGUAL CADENA
      {
         name = $3;
      }
      | UNIT IGUAL B
      {
         unit = $3;
      }
      | UNIT IGUAL K
      {
         unit = $3;
      }
      | UNIT IGUAL M
      {
         unit = $3;
      }
      | TYPE IGUAL P
      {
         type = $3;
      }
      | TYPE IGUAL E
      {
         type = $3;
      }
      | TYPE IGUAL L
      {
         type = $3;
      }
      | FIT IGUAL BF
      {
         fit = $3;
      }
      | FIT IGUAL FF
      {
         fit = $3;
      }
      | FIT IGUAL WF
      {
         fit = $3;
      }
      | DELETE IGUAL FULL
      {
         delete_ = $3;
      }
      | ADD IGUAL NUM
      {
         add = $3;
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
  std::cout << "XXXXXXXXXXXX ERROR EN EL COMANDO XXXXXXXXXXXXX" << std::endl;
}