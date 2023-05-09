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
   class Mkdisk;
   class Rmdisk;
   class Fdisk;
   class Execute;
   class Mount;
   class Unmount;
   class Rep;
   class Mkfs;
   class Login;
   class Logout;
   class Mkgrp;
   class Mkusr;
   class Rmgrp;
   class Rmusr;
   class Cat;
   class Chgrp;
}

%{
   
   #include <string>
   #include <stdio.h>
   #include "driver.h"
   #include <iostream>
   #include <fstream>
   #include <vector>
   #include "../Comandos/Mkdisk.h"
   #include "../Comandos/Rmdisk.h"
   #include "../Comandos/Fdisk.h"
   #include "../Comandos/Mount.h"
   #include "../Comandos/Unmount.h"
   #include "../Comandos/Rep.h"
   #include "../Comandos/Mkfs.h"
   #include "../Comandos/Login.h"
   #include "../Comandos/Logout.h"
   #include "../Comandos/Mkgrp.h"
   #include "../Comandos/Mkusr.h"
   #include "../Comandos/Rmgrp.h"
   #include "../Comandos/Rmusr.h"
   #include "../Comandos/Cat.h"
   #include "../Comandos/Chgrp.h"

   std::string dsk_size = "";
   std::string path = "";
   std::string fit = "";
   std::string unit = ""; 
   std::string name = "";
   std::string type = "";
   std::string delete_ = "";
   std::string add = "";
   std::string id = "";
   std::string comruta = "";
   std::string fs = "";
   std::string user = "";
   std::string pass = "";
   std::string grp = "";
   std::string file = "";
%}


/******* TERMINALES ********/
%token <std::string> MKDISK"mkdisk" RMDISK"rmdisk" FDISK"fdisk" MOUNT"mount" UNMOUNT"unmount" MKFS"mkfs" LOGIN"login" LOGOUT"logout" MKGRP"mkgrp" RMGRP"rmgrp" MKUSR"mkusr" RMUSR"rmusr" MKFILE"mkfile" CAT"cat" REMOVE"remove" EDIT"edit" RENAME"rename" MKDIR"mkdir" COPY"copy" MOVE"move" FIND"find" CHOWN"chown" CHGRP"chgrp" CHMOD"chmod" PAUSE"pause" EXECUTE"execute" REP"rep" RECOVERY"recovery" LOSS"loss" FULL"full" BESTFIT"BestFit" FIRSTFIT"FirstFit" WORSTFIT"WorstFit" DOSFS"2fs" TRESFS"3fs" MBR"mbr" DISK"disk" INODE"inode" JOURNALING"journaling" BLOCK"block" BMINODE"bm_inode" BMBLOCK"bm_block" TREE"tree" SB"sb" FILE"file" LS"ls" IGUAL"=" R">r" SIZE">size" PATH">path" FIT">fit" UNIT">UNIT" NAME">name" TYPE">type" DELETE">delete" ADD">add" ID">id" FS">fs" USER">user" PASS">pass" GRP">grp" CONT">cont" DESTINO">destino" UGO">ugo" COMRUTA">ruta" FILEN"FILEN" BF"BF" FF"FF" WF"WF" K"K" M"M" B"B" P"P" E"E" L"L"  RUTA"RUTA" CADENA"CADENA" 
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
         Mount *montar = new Mount();
         montar->path = $4;
         montar->name = $7;
         montar->MontarParticion(montar);
      }
      | MOUNT NAME IGUAL CADENA PATH IGUAL RUTA
      {
         Mount *montar = new Mount();
         montar->path = $7;
         montar->name = $4;
         montar->MontarParticion(montar);
      }
      | UNMOUNT ID IGUAL CADENA
      {
         Unmount *desmontar = new Unmount();
         desmontar->id = $4;
         desmontar->DesmontarParticion(desmontar);
      }
      | MKFS Lista_mkfs
      {
         Mkfs *formatear = new Mkfs();
         formatear->id = id;
         formatear->type = type;
         formatear->fs = fs;
         formatear->SistemaDeArchivos(formatear);
         id = "";
         type = "";
         fs = "";
      }
      | LOGIN Lista_login
      {
         Login *inicio = new Login();
         inicio->user = user;
         inicio->password = pass;
         inicio->id = id;
         inicio->IniciarSesion(inicio);
         user = "";
         pass = "";
         id = "";
      }
      | LOGOUT
      {
         Logout *cerrar = new Logout();
         cerrar->CerrarSesion(cerrar);
      }
      | MKGRP NAME IGUAL CADENA
      {
         Mkgrp *grupo = new Mkgrp();
         grupo->name = $4;
         grupo->CrearGrupo(grupo);
      }
      | RMGRP NAME IGUAL CADENA
      {
         Rmgrp *grupo = new Rmgrp();
         grupo->name = $4;
         grupo->EliminarGrupo(grupo);
      }
      | RMUSR USER IGUAL CADENA
      {
         Rmusr *usuario = new Rmusr();
         usuario->user = $4;
         usuario->EliminarUsuario(usuario);
      }
      | MKUSR Lista_mkusr
      {
         Mkusr *usuario = new Mkusr();
         usuario->user = user;
         usuario->password = pass;
         usuario->group = grp;
         usuario->CrearUsuario(usuario);
         user = "";
         pass = "";
         grp = "";
      }
      | MKFILE Lista_mkfile
      {
         std::cout << "COMANDO MKFILE" << std::endl;
      }
      | CAT Lista_cat
      {
         Cat *archivo = new Cat();
         archivo->file = file;
         archivo->LeerArchivo(archivo);
         file="";
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
         Chgrp *grupo = new Chgrp();
         grupo->user = $4;
         grupo->group = $7;
         grupo->CambiarGrupo(grupo);
      }
      | CHGRP GRP IGUAL CADENA USER IGUAL CADENA
      {
         Chgrp *grupo = new Chgrp();
         grupo->user = $7;
         grupo->group = $4;
         grupo->CambiarGrupo(grupo);
      }
      | CHMOD Lista_chmod
      {
         std::cout << "COMANDO CHMOD" << std::endl;
      }
      | RECOVERY ID IGUAL CADENA
      {
         std::cout << "COMANDO RECOVERY" << std::endl;
         std::cout << "ID: "<< $3 << std::endl;
      }
      | LOSS ID IGUAL CADENA
      {
         std::cout << "COMANDO LOSS" << std::endl;
         std::cout << "ID: "<< $3 << std::endl;
      }
      | EXECUTE PATH IGUAL RUTA
      {
         std::string filename($4);
         std::string linea;
         ifstream input_file(filename);
         if (!input_file.is_open()) {
            std::cout << "No se pudo abrir el archivo" << filename << "'" << endl;
         }

         while (getline(input_file, linea)){
            Driver driver;
            driver.parse(linea);
         }
         input_file.close();
      }
      | REP Lista_rep
      {
         Rep *reporte = new Rep();
         reporte-> id = id;
         reporte-> path = path;
         reporte-> name = name;
         reporte-> ruta = comruta;
         reporte->controlReportes(reporte);
         id="";
         path="";
         name="";
         comruta="";
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
         id = $3;
      }
      | TYPE IGUAL FULL
      {
         type = $3;
      }
      | FS IGUAL DOSFS
      {
         fs = $3;
      }
      | FS IGUAL TRESFS
      {
         fs = $3;
      }
   ;

   Lista_login
      : Lista_login param_login              {}
      | param_login                          {}
   ;

   param_login
      : USER IGUAL CADENA
      {
         user = $3;
      }
      | PASS IGUAL CADENA
      {
         pass = $3;
      }
      | PASS IGUAL NUM
      {
         pass = $3;
      }
      | ID IGUAL CADENA
      {
         id = $3;
      }
   ;

   Lista_mkusr
      : Lista_mkusr param_mkusr              {}
      | param_mkusr                          {}
   ;

   param_mkusr
      : USER IGUAL CADENA
      {
         user = $3;
      }
      | PASS IGUAL CADENA
      {
         pass = $3;
      }
      | PASS IGUAL NUM
      {
         pass = $3;
      }
      | GRP IGUAL CADENA
      {
         grp = $3;
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
         file= $3;
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
         name = $3;
      }
      | NAME IGUAL DISK
      {
         name = $3;
      }
      | NAME IGUAL INODE
      {
         name = $3;
      }
      | NAME IGUAL JOURNALING
      {
         name = $3;
      }
      | NAME IGUAL BLOCK
      {
         name = $3;
      }
      | NAME IGUAL BMINODE
      {
         name = $3;
      }
      | NAME IGUAL BMBLOCK
      {
         name = $3;
      }
      | NAME IGUAL TREE
      {
         name = $3;
      }
      | NAME IGUAL SB
      {
         name = $3;
      }
      | NAME IGUAL FILE
      {
         name = $3;
      }
      | NAME IGUAL LS
      {
         name = $3;
      }
      | PATH IGUAL RUTA
      {
         path = $3;
      }
      | ID IGUAL CADENA
      {
         id = $3;
      }
      | COMRUTA IGUAL RUTA
      {
         comruta = $3;
      }
   ;

%%

void yy::Parser::error( const std::string& error){
  
}