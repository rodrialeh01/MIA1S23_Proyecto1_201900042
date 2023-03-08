// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 26 "parser.yy"

   
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


#line 71 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 149 "parser.tab.cc"

  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_MKDISK: // "mkdisk"
      case symbol_kind::S_RMDISK: // "rmdisk"
      case symbol_kind::S_FDISK: // "fdisk"
      case symbol_kind::S_MOUNT: // "mount"
      case symbol_kind::S_UNMOUNT: // "unmount"
      case symbol_kind::S_MKFS: // "mkfs"
      case symbol_kind::S_LOGIN: // "login"
      case symbol_kind::S_LOGOUT: // "logout"
      case symbol_kind::S_MKGRP: // "mkgrp"
      case symbol_kind::S_RMGRP: // "rmgrp"
      case symbol_kind::S_MKUSR: // "mkusr"
      case symbol_kind::S_RMUSR: // "rmusr"
      case symbol_kind::S_MKFILE: // "mkfile"
      case symbol_kind::S_CAT: // "cat"
      case symbol_kind::S_REMOVE: // "remove"
      case symbol_kind::S_EDIT: // "edit"
      case symbol_kind::S_RENAME: // "rename"
      case symbol_kind::S_MKDIR: // "mkdir"
      case symbol_kind::S_COPY: // "copy"
      case symbol_kind::S_MOVE: // "move"
      case symbol_kind::S_FIND: // "find"
      case symbol_kind::S_CHOWN: // "chown"
      case symbol_kind::S_CHGRP: // "chgrp"
      case symbol_kind::S_CHMOD: // "chmod"
      case symbol_kind::S_PAUSE: // "pause"
      case symbol_kind::S_EXECUTE: // "execute"
      case symbol_kind::S_REP: // "rep"
      case symbol_kind::S_RECOVERY: // "recovery"
      case symbol_kind::S_LOSS: // "loss"
      case symbol_kind::S_FULL: // "full"
      case symbol_kind::S_BESTFIT: // "BestFit"
      case symbol_kind::S_FIRSTFIT: // "FirstFit"
      case symbol_kind::S_WORSTFIT: // "WorstFit"
      case symbol_kind::S_DOSFS: // "2fs"
      case symbol_kind::S_TRESFS: // "3fs"
      case symbol_kind::S_MBR: // "mbr"
      case symbol_kind::S_DISK: // "disk"
      case symbol_kind::S_INODE: // "inode"
      case symbol_kind::S_JOURNALING: // "journaling"
      case symbol_kind::S_BLOCK: // "block"
      case symbol_kind::S_BMINODE: // "bm_inode"
      case symbol_kind::S_BMBLOCK: // "bm_block"
      case symbol_kind::S_TREE: // "tree"
      case symbol_kind::S_SB: // "sb"
      case symbol_kind::S_FILE: // "file"
      case symbol_kind::S_LS: // "ls"
      case symbol_kind::S_IGUAL: // "="
      case symbol_kind::S_R: // ">r"
      case symbol_kind::S_SIZE: // ">size"
      case symbol_kind::S_PATH: // ">path"
      case symbol_kind::S_FIT: // ">fit"
      case symbol_kind::S_UNIT: // ">UNIT"
      case symbol_kind::S_NAME: // ">name"
      case symbol_kind::S_TYPE: // ">type"
      case symbol_kind::S_DELETE: // ">delete"
      case symbol_kind::S_ADD: // ">add"
      case symbol_kind::S_ID: // ">id"
      case symbol_kind::S_FS: // ">fs"
      case symbol_kind::S_USER: // ">user"
      case symbol_kind::S_PASS: // ">pass"
      case symbol_kind::S_GRP: // ">grp"
      case symbol_kind::S_CONT: // ">cont"
      case symbol_kind::S_DESTINO: // ">destino"
      case symbol_kind::S_UGO: // ">ugo"
      case symbol_kind::S_COMRUTA: // ">ruta"
      case symbol_kind::S_FILEN: // "FILEN"
      case symbol_kind::S_BF: // "BF"
      case symbol_kind::S_FF: // "FF"
      case symbol_kind::S_WF: // "WF"
      case symbol_kind::S_K: // "K"
      case symbol_kind::S_M: // "M"
      case symbol_kind::S_B: // "B"
      case symbol_kind::S_P: // "P"
      case symbol_kind::S_E: // "E"
      case symbol_kind::S_L: // "L"
      case symbol_kind::S_RUTA: // "RUTA"
      case symbol_kind::S_CADENA: // "CADENA"
      case symbol_kind::S_NUM: // "NUM"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_MKDISK: // "mkdisk"
      case symbol_kind::S_RMDISK: // "rmdisk"
      case symbol_kind::S_FDISK: // "fdisk"
      case symbol_kind::S_MOUNT: // "mount"
      case symbol_kind::S_UNMOUNT: // "unmount"
      case symbol_kind::S_MKFS: // "mkfs"
      case symbol_kind::S_LOGIN: // "login"
      case symbol_kind::S_LOGOUT: // "logout"
      case symbol_kind::S_MKGRP: // "mkgrp"
      case symbol_kind::S_RMGRP: // "rmgrp"
      case symbol_kind::S_MKUSR: // "mkusr"
      case symbol_kind::S_RMUSR: // "rmusr"
      case symbol_kind::S_MKFILE: // "mkfile"
      case symbol_kind::S_CAT: // "cat"
      case symbol_kind::S_REMOVE: // "remove"
      case symbol_kind::S_EDIT: // "edit"
      case symbol_kind::S_RENAME: // "rename"
      case symbol_kind::S_MKDIR: // "mkdir"
      case symbol_kind::S_COPY: // "copy"
      case symbol_kind::S_MOVE: // "move"
      case symbol_kind::S_FIND: // "find"
      case symbol_kind::S_CHOWN: // "chown"
      case symbol_kind::S_CHGRP: // "chgrp"
      case symbol_kind::S_CHMOD: // "chmod"
      case symbol_kind::S_PAUSE: // "pause"
      case symbol_kind::S_EXECUTE: // "execute"
      case symbol_kind::S_REP: // "rep"
      case symbol_kind::S_RECOVERY: // "recovery"
      case symbol_kind::S_LOSS: // "loss"
      case symbol_kind::S_FULL: // "full"
      case symbol_kind::S_BESTFIT: // "BestFit"
      case symbol_kind::S_FIRSTFIT: // "FirstFit"
      case symbol_kind::S_WORSTFIT: // "WorstFit"
      case symbol_kind::S_DOSFS: // "2fs"
      case symbol_kind::S_TRESFS: // "3fs"
      case symbol_kind::S_MBR: // "mbr"
      case symbol_kind::S_DISK: // "disk"
      case symbol_kind::S_INODE: // "inode"
      case symbol_kind::S_JOURNALING: // "journaling"
      case symbol_kind::S_BLOCK: // "block"
      case symbol_kind::S_BMINODE: // "bm_inode"
      case symbol_kind::S_BMBLOCK: // "bm_block"
      case symbol_kind::S_TREE: // "tree"
      case symbol_kind::S_SB: // "sb"
      case symbol_kind::S_FILE: // "file"
      case symbol_kind::S_LS: // "ls"
      case symbol_kind::S_IGUAL: // "="
      case symbol_kind::S_R: // ">r"
      case symbol_kind::S_SIZE: // ">size"
      case symbol_kind::S_PATH: // ">path"
      case symbol_kind::S_FIT: // ">fit"
      case symbol_kind::S_UNIT: // ">UNIT"
      case symbol_kind::S_NAME: // ">name"
      case symbol_kind::S_TYPE: // ">type"
      case symbol_kind::S_DELETE: // ">delete"
      case symbol_kind::S_ADD: // ">add"
      case symbol_kind::S_ID: // ">id"
      case symbol_kind::S_FS: // ">fs"
      case symbol_kind::S_USER: // ">user"
      case symbol_kind::S_PASS: // ">pass"
      case symbol_kind::S_GRP: // ">grp"
      case symbol_kind::S_CONT: // ">cont"
      case symbol_kind::S_DESTINO: // ">destino"
      case symbol_kind::S_UGO: // ">ugo"
      case symbol_kind::S_COMRUTA: // ">ruta"
      case symbol_kind::S_FILEN: // "FILEN"
      case symbol_kind::S_BF: // "BF"
      case symbol_kind::S_FF: // "FF"
      case symbol_kind::S_WF: // "WF"
      case symbol_kind::S_K: // "K"
      case symbol_kind::S_M: // "M"
      case symbol_kind::S_B: // "B"
      case symbol_kind::S_P: // "P"
      case symbol_kind::S_E: // "E"
      case symbol_kind::S_L: // "L"
      case symbol_kind::S_RUTA: // "RUTA"
      case symbol_kind::S_CADENA: // "CADENA"
      case symbol_kind::S_NUM: // "NUM"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_MKDISK: // "mkdisk"
      case symbol_kind::S_RMDISK: // "rmdisk"
      case symbol_kind::S_FDISK: // "fdisk"
      case symbol_kind::S_MOUNT: // "mount"
      case symbol_kind::S_UNMOUNT: // "unmount"
      case symbol_kind::S_MKFS: // "mkfs"
      case symbol_kind::S_LOGIN: // "login"
      case symbol_kind::S_LOGOUT: // "logout"
      case symbol_kind::S_MKGRP: // "mkgrp"
      case symbol_kind::S_RMGRP: // "rmgrp"
      case symbol_kind::S_MKUSR: // "mkusr"
      case symbol_kind::S_RMUSR: // "rmusr"
      case symbol_kind::S_MKFILE: // "mkfile"
      case symbol_kind::S_CAT: // "cat"
      case symbol_kind::S_REMOVE: // "remove"
      case symbol_kind::S_EDIT: // "edit"
      case symbol_kind::S_RENAME: // "rename"
      case symbol_kind::S_MKDIR: // "mkdir"
      case symbol_kind::S_COPY: // "copy"
      case symbol_kind::S_MOVE: // "move"
      case symbol_kind::S_FIND: // "find"
      case symbol_kind::S_CHOWN: // "chown"
      case symbol_kind::S_CHGRP: // "chgrp"
      case symbol_kind::S_CHMOD: // "chmod"
      case symbol_kind::S_PAUSE: // "pause"
      case symbol_kind::S_EXECUTE: // "execute"
      case symbol_kind::S_REP: // "rep"
      case symbol_kind::S_RECOVERY: // "recovery"
      case symbol_kind::S_LOSS: // "loss"
      case symbol_kind::S_FULL: // "full"
      case symbol_kind::S_BESTFIT: // "BestFit"
      case symbol_kind::S_FIRSTFIT: // "FirstFit"
      case symbol_kind::S_WORSTFIT: // "WorstFit"
      case symbol_kind::S_DOSFS: // "2fs"
      case symbol_kind::S_TRESFS: // "3fs"
      case symbol_kind::S_MBR: // "mbr"
      case symbol_kind::S_DISK: // "disk"
      case symbol_kind::S_INODE: // "inode"
      case symbol_kind::S_JOURNALING: // "journaling"
      case symbol_kind::S_BLOCK: // "block"
      case symbol_kind::S_BMINODE: // "bm_inode"
      case symbol_kind::S_BMBLOCK: // "bm_block"
      case symbol_kind::S_TREE: // "tree"
      case symbol_kind::S_SB: // "sb"
      case symbol_kind::S_FILE: // "file"
      case symbol_kind::S_LS: // "ls"
      case symbol_kind::S_IGUAL: // "="
      case symbol_kind::S_R: // ">r"
      case symbol_kind::S_SIZE: // ">size"
      case symbol_kind::S_PATH: // ">path"
      case symbol_kind::S_FIT: // ">fit"
      case symbol_kind::S_UNIT: // ">UNIT"
      case symbol_kind::S_NAME: // ">name"
      case symbol_kind::S_TYPE: // ">type"
      case symbol_kind::S_DELETE: // ">delete"
      case symbol_kind::S_ADD: // ">add"
      case symbol_kind::S_ID: // ">id"
      case symbol_kind::S_FS: // ">fs"
      case symbol_kind::S_USER: // ">user"
      case symbol_kind::S_PASS: // ">pass"
      case symbol_kind::S_GRP: // ">grp"
      case symbol_kind::S_CONT: // ">cont"
      case symbol_kind::S_DESTINO: // ">destino"
      case symbol_kind::S_UGO: // ">ugo"
      case symbol_kind::S_COMRUTA: // ">ruta"
      case symbol_kind::S_FILEN: // "FILEN"
      case symbol_kind::S_BF: // "BF"
      case symbol_kind::S_FF: // "FF"
      case symbol_kind::S_WF: // "WF"
      case symbol_kind::S_K: // "K"
      case symbol_kind::S_M: // "M"
      case symbol_kind::S_B: // "B"
      case symbol_kind::S_P: // "P"
      case symbol_kind::S_E: // "E"
      case symbol_kind::S_L: // "L"
      case symbol_kind::S_RUTA: // "RUTA"
      case symbol_kind::S_CADENA: // "CADENA"
      case symbol_kind::S_NUM: // "NUM"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_MKDISK: // "mkdisk"
      case symbol_kind::S_RMDISK: // "rmdisk"
      case symbol_kind::S_FDISK: // "fdisk"
      case symbol_kind::S_MOUNT: // "mount"
      case symbol_kind::S_UNMOUNT: // "unmount"
      case symbol_kind::S_MKFS: // "mkfs"
      case symbol_kind::S_LOGIN: // "login"
      case symbol_kind::S_LOGOUT: // "logout"
      case symbol_kind::S_MKGRP: // "mkgrp"
      case symbol_kind::S_RMGRP: // "rmgrp"
      case symbol_kind::S_MKUSR: // "mkusr"
      case symbol_kind::S_RMUSR: // "rmusr"
      case symbol_kind::S_MKFILE: // "mkfile"
      case symbol_kind::S_CAT: // "cat"
      case symbol_kind::S_REMOVE: // "remove"
      case symbol_kind::S_EDIT: // "edit"
      case symbol_kind::S_RENAME: // "rename"
      case symbol_kind::S_MKDIR: // "mkdir"
      case symbol_kind::S_COPY: // "copy"
      case symbol_kind::S_MOVE: // "move"
      case symbol_kind::S_FIND: // "find"
      case symbol_kind::S_CHOWN: // "chown"
      case symbol_kind::S_CHGRP: // "chgrp"
      case symbol_kind::S_CHMOD: // "chmod"
      case symbol_kind::S_PAUSE: // "pause"
      case symbol_kind::S_EXECUTE: // "execute"
      case symbol_kind::S_REP: // "rep"
      case symbol_kind::S_RECOVERY: // "recovery"
      case symbol_kind::S_LOSS: // "loss"
      case symbol_kind::S_FULL: // "full"
      case symbol_kind::S_BESTFIT: // "BestFit"
      case symbol_kind::S_FIRSTFIT: // "FirstFit"
      case symbol_kind::S_WORSTFIT: // "WorstFit"
      case symbol_kind::S_DOSFS: // "2fs"
      case symbol_kind::S_TRESFS: // "3fs"
      case symbol_kind::S_MBR: // "mbr"
      case symbol_kind::S_DISK: // "disk"
      case symbol_kind::S_INODE: // "inode"
      case symbol_kind::S_JOURNALING: // "journaling"
      case symbol_kind::S_BLOCK: // "block"
      case symbol_kind::S_BMINODE: // "bm_inode"
      case symbol_kind::S_BMBLOCK: // "bm_block"
      case symbol_kind::S_TREE: // "tree"
      case symbol_kind::S_SB: // "sb"
      case symbol_kind::S_FILE: // "file"
      case symbol_kind::S_LS: // "ls"
      case symbol_kind::S_IGUAL: // "="
      case symbol_kind::S_R: // ">r"
      case symbol_kind::S_SIZE: // ">size"
      case symbol_kind::S_PATH: // ">path"
      case symbol_kind::S_FIT: // ">fit"
      case symbol_kind::S_UNIT: // ">UNIT"
      case symbol_kind::S_NAME: // ">name"
      case symbol_kind::S_TYPE: // ">type"
      case symbol_kind::S_DELETE: // ">delete"
      case symbol_kind::S_ADD: // ">add"
      case symbol_kind::S_ID: // ">id"
      case symbol_kind::S_FS: // ">fs"
      case symbol_kind::S_USER: // ">user"
      case symbol_kind::S_PASS: // ">pass"
      case symbol_kind::S_GRP: // ">grp"
      case symbol_kind::S_CONT: // ">cont"
      case symbol_kind::S_DESTINO: // ">destino"
      case symbol_kind::S_UGO: // ">ugo"
      case symbol_kind::S_COMRUTA: // ">ruta"
      case symbol_kind::S_FILEN: // "FILEN"
      case symbol_kind::S_BF: // "BF"
      case symbol_kind::S_FF: // "FF"
      case symbol_kind::S_WF: // "WF"
      case symbol_kind::S_K: // "K"
      case symbol_kind::S_M: // "M"
      case symbol_kind::S_B: // "B"
      case symbol_kind::S_P: // "P"
      case symbol_kind::S_E: // "E"
      case symbol_kind::S_L: // "L"
      case symbol_kind::S_RUTA: // "RUTA"
      case symbol_kind::S_CADENA: // "CADENA"
      case symbol_kind::S_NUM: // "NUM"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_MKDISK: // "mkdisk"
      case symbol_kind::S_RMDISK: // "rmdisk"
      case symbol_kind::S_FDISK: // "fdisk"
      case symbol_kind::S_MOUNT: // "mount"
      case symbol_kind::S_UNMOUNT: // "unmount"
      case symbol_kind::S_MKFS: // "mkfs"
      case symbol_kind::S_LOGIN: // "login"
      case symbol_kind::S_LOGOUT: // "logout"
      case symbol_kind::S_MKGRP: // "mkgrp"
      case symbol_kind::S_RMGRP: // "rmgrp"
      case symbol_kind::S_MKUSR: // "mkusr"
      case symbol_kind::S_RMUSR: // "rmusr"
      case symbol_kind::S_MKFILE: // "mkfile"
      case symbol_kind::S_CAT: // "cat"
      case symbol_kind::S_REMOVE: // "remove"
      case symbol_kind::S_EDIT: // "edit"
      case symbol_kind::S_RENAME: // "rename"
      case symbol_kind::S_MKDIR: // "mkdir"
      case symbol_kind::S_COPY: // "copy"
      case symbol_kind::S_MOVE: // "move"
      case symbol_kind::S_FIND: // "find"
      case symbol_kind::S_CHOWN: // "chown"
      case symbol_kind::S_CHGRP: // "chgrp"
      case symbol_kind::S_CHMOD: // "chmod"
      case symbol_kind::S_PAUSE: // "pause"
      case symbol_kind::S_EXECUTE: // "execute"
      case symbol_kind::S_REP: // "rep"
      case symbol_kind::S_RECOVERY: // "recovery"
      case symbol_kind::S_LOSS: // "loss"
      case symbol_kind::S_FULL: // "full"
      case symbol_kind::S_BESTFIT: // "BestFit"
      case symbol_kind::S_FIRSTFIT: // "FirstFit"
      case symbol_kind::S_WORSTFIT: // "WorstFit"
      case symbol_kind::S_DOSFS: // "2fs"
      case symbol_kind::S_TRESFS: // "3fs"
      case symbol_kind::S_MBR: // "mbr"
      case symbol_kind::S_DISK: // "disk"
      case symbol_kind::S_INODE: // "inode"
      case symbol_kind::S_JOURNALING: // "journaling"
      case symbol_kind::S_BLOCK: // "block"
      case symbol_kind::S_BMINODE: // "bm_inode"
      case symbol_kind::S_BMBLOCK: // "bm_block"
      case symbol_kind::S_TREE: // "tree"
      case symbol_kind::S_SB: // "sb"
      case symbol_kind::S_FILE: // "file"
      case symbol_kind::S_LS: // "ls"
      case symbol_kind::S_IGUAL: // "="
      case symbol_kind::S_R: // ">r"
      case symbol_kind::S_SIZE: // ">size"
      case symbol_kind::S_PATH: // ">path"
      case symbol_kind::S_FIT: // ">fit"
      case symbol_kind::S_UNIT: // ">UNIT"
      case symbol_kind::S_NAME: // ">name"
      case symbol_kind::S_TYPE: // ">type"
      case symbol_kind::S_DELETE: // ">delete"
      case symbol_kind::S_ADD: // ">add"
      case symbol_kind::S_ID: // ">id"
      case symbol_kind::S_FS: // ">fs"
      case symbol_kind::S_USER: // ">user"
      case symbol_kind::S_PASS: // ">pass"
      case symbol_kind::S_GRP: // ">grp"
      case symbol_kind::S_CONT: // ">cont"
      case symbol_kind::S_DESTINO: // ">destino"
      case symbol_kind::S_UGO: // ">ugo"
      case symbol_kind::S_COMRUTA: // ">ruta"
      case symbol_kind::S_FILEN: // "FILEN"
      case symbol_kind::S_BF: // "BF"
      case symbol_kind::S_FF: // "FF"
      case symbol_kind::S_WF: // "WF"
      case symbol_kind::S_K: // "K"
      case symbol_kind::S_M: // "M"
      case symbol_kind::S_B: // "B"
      case symbol_kind::S_P: // "P"
      case symbol_kind::S_E: // "E"
      case symbol_kind::S_L: // "L"
      case symbol_kind::S_RUTA: // "RUTA"
      case symbol_kind::S_CADENA: // "CADENA"
      case symbol_kind::S_NUM: // "NUM"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Inicio: Lista
#line 67 "parser.yy"
                                    {}
#line 936 "parser.tab.cc"
    break;

  case 3: // Lista: Lista COMANDO
#line 72 "parser.yy"
                                    {}
#line 942 "parser.tab.cc"
    break;

  case 4: // Lista: COMANDO
#line 73 "parser.yy"
                                    {}
#line 948 "parser.tab.cc"
    break;

  case 5: // COMANDO: "mkdisk" Lista_parametrosmkdisk
#line 78 "parser.yy"
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
#line 969 "parser.tab.cc"
    break;

  case 6: // COMANDO: "rmdisk" ">path" "=" "RUTA"
#line 95 "parser.yy"
      {
         Rmdisk *disco = new Rmdisk();
         disco->path = yystack_[0].value.as < std::string > ();
         disco->EliminarDisco(disco);
         path = "";
      }
#line 980 "parser.tab.cc"
    break;

  case 7: // COMANDO: "fdisk" Lista_fdisk
#line 102 "parser.yy"
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
#line 1013 "parser.tab.cc"
    break;

  case 8: // COMANDO: "mount" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 131 "parser.yy"
      {
         Mount *montar = new Mount();
         montar->path = yystack_[3].value.as < std::string > ();
         montar->name = yystack_[0].value.as < std::string > ();
         montar->MontarParticion(montar);
      }
#line 1024 "parser.tab.cc"
    break;

  case 9: // COMANDO: "mount" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 138 "parser.yy"
      {
         Mount *montar = new Mount();
         montar->path = yystack_[0].value.as < std::string > ();
         montar->name = yystack_[3].value.as < std::string > ();
         montar->MontarParticion(montar);
      }
#line 1035 "parser.tab.cc"
    break;

  case 10: // COMANDO: "unmount" ">id" "=" "CADENA"
#line 145 "parser.yy"
      {
         Unmount *desmontar = new Unmount();
         desmontar->id = yystack_[0].value.as < std::string > ();
         desmontar->DesmontarParticion(desmontar);
      }
#line 1045 "parser.tab.cc"
    break;

  case 11: // COMANDO: "mkfs" Lista_mkfs
#line 151 "parser.yy"
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
#line 1060 "parser.tab.cc"
    break;

  case 12: // COMANDO: "login" Lista_login
#line 162 "parser.yy"
      {
         std::cout << "COMANDO LOGIN" << std::endl;
      }
#line 1068 "parser.tab.cc"
    break;

  case 13: // COMANDO: "logout"
#line 166 "parser.yy"
      {
         std::cout << "COMANDO LOGOUT" << std::endl;
      }
#line 1076 "parser.tab.cc"
    break;

  case 14: // COMANDO: "mkgrp" ">name" "=" "CADENA"
#line 170 "parser.yy"
      {
         std::cout << "COMANDO MKGRP" << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1085 "parser.tab.cc"
    break;

  case 15: // COMANDO: "rmgrp" ">name" "=" "CADENA"
#line 175 "parser.yy"
      {
         std::cout << "COMANDO RMGRP" << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1094 "parser.tab.cc"
    break;

  case 16: // COMANDO: "rmusr" ">user" "=" "CADENA"
#line 180 "parser.yy"
      {
         std::cout << "COMANDO RMUSR" << std::endl;
         std::cout << "USER: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1103 "parser.tab.cc"
    break;

  case 17: // COMANDO: "mkusr" Lista_mkusr
#line 185 "parser.yy"
      {
         std::cout << "COMANDO MKUSR" << std::endl;
      }
#line 1111 "parser.tab.cc"
    break;

  case 18: // COMANDO: "mkfile" Lista_mkfile
#line 189 "parser.yy"
      {
         std::cout << "COMANDO MKFILE" << std::endl;
      }
#line 1119 "parser.tab.cc"
    break;

  case 19: // COMANDO: "cat" Lista_cat
#line 193 "parser.yy"
      {
         std::cout << "COMANDO CAT" << std::endl;
      }
#line 1127 "parser.tab.cc"
    break;

  case 20: // COMANDO: "remove" ">path" "=" "RUTA"
#line 197 "parser.yy"
      {
         std::cout << "COMANDO REMOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1136 "parser.tab.cc"
    break;

  case 21: // COMANDO: "edit" ">path" "=" "RUTA" ">cont" "=" "RUTA"
#line 202 "parser.yy"
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "CONT: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1146 "parser.tab.cc"
    break;

  case 22: // COMANDO: "edit" ">cont" "=" "RUTA" ">path" "=" "RUTA"
#line 208 "parser.yy"
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "CONT: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1156 "parser.tab.cc"
    break;

  case 23: // COMANDO: "rename" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 214 "parser.yy"
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1166 "parser.tab.cc"
    break;

  case 24: // COMANDO: "rename" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 220 "parser.yy"
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1176 "parser.tab.cc"
    break;

  case 25: // COMANDO: "mkdir" ">path" "=" "RUTA"
#line 226 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1185 "parser.tab.cc"
    break;

  case 26: // COMANDO: "mkdir" ">path" "=" "RUTA" ">r"
#line 231 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[1].value.as < std::string > () << std::endl;
         std::cout << "R" << std::endl;
      }
#line 1195 "parser.tab.cc"
    break;

  case 27: // COMANDO: "mkdir" ">r" ">path" "=" "RUTA"
#line 237 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "R" << std::endl;
      }
#line 1205 "parser.tab.cc"
    break;

  case 28: // COMANDO: "copy" ">path" "=" "RUTA" ">destino" "=" "RUTA"
#line 243 "parser.yy"
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1215 "parser.tab.cc"
    break;

  case 29: // COMANDO: "copy" ">destino" "=" "RUTA" ">path" "=" "RUTA"
#line 249 "parser.yy"
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1225 "parser.tab.cc"
    break;

  case 30: // COMANDO: "move" ">path" "=" "RUTA" ">destino" "=" "RUTA"
#line 255 "parser.yy"
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1235 "parser.tab.cc"
    break;

  case 31: // COMANDO: "move" ">destino" "=" "RUTA" ">path" "=" "RUTA"
#line 261 "parser.yy"
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1245 "parser.tab.cc"
    break;

  case 32: // COMANDO: "find" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 267 "parser.yy"
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1255 "parser.tab.cc"
    break;

  case 33: // COMANDO: "find" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 273 "parser.yy"
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1265 "parser.tab.cc"
    break;

  case 34: // COMANDO: "chown" Lista_chown
#line 279 "parser.yy"
      {
         std::cout << "COMANDO CHOWN" << std::endl;
      }
#line 1273 "parser.tab.cc"
    break;

  case 35: // COMANDO: "chgrp" ">user" "=" "CADENA" ">grp" "=" "CADENA"
#line 283 "parser.yy"
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "GRP: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1283 "parser.tab.cc"
    break;

  case 36: // COMANDO: "chgrp" ">grp" "=" "CADENA" ">user" "=" "CADENA"
#line 289 "parser.yy"
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "GRP: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1293 "parser.tab.cc"
    break;

  case 37: // COMANDO: "chmod" Lista_chmod
#line 295 "parser.yy"
      {
         std::cout << "COMANDO CHMOD" << std::endl;
      }
#line 1301 "parser.tab.cc"
    break;

  case 38: // COMANDO: "recovery" ">id" "=" "CADENA"
#line 299 "parser.yy"
      {
         std::cout << "COMANDO RECOVERY" << std::endl;
         std::cout << "ID: "<< yystack_[1].value.as < std::string > () << std::endl;
      }
#line 1310 "parser.tab.cc"
    break;

  case 39: // COMANDO: "loss" ">id" "=" "CADENA"
#line 304 "parser.yy"
      {
         std::cout << "COMANDO LOSS" << std::endl;
         std::cout << "ID: "<< yystack_[1].value.as < std::string > () << std::endl;
      }
#line 1319 "parser.tab.cc"
    break;

  case 40: // COMANDO: "execute" ">path" "=" "RUTA"
#line 309 "parser.yy"
      {
         std::string filename(yystack_[0].value.as < std::string > ());
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
#line 1339 "parser.tab.cc"
    break;

  case 41: // COMANDO: "rep" Lista_rep
#line 325 "parser.yy"
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
#line 1356 "parser.tab.cc"
    break;

  case 42: // COMANDO: "pause"
#line 338 "parser.yy"
      {
        std::cout << "Presione una tecla para continuar..." << std::endl;
        std::cin.ignore();
      }
#line 1365 "parser.tab.cc"
    break;

  case 43: // Lista_parametrosmkdisk: Lista_parametrosmkdisk parametromk
#line 345 "parser.yy"
                                           {}
#line 1371 "parser.tab.cc"
    break;

  case 44: // Lista_parametrosmkdisk: parametromk
#line 346 "parser.yy"
                                      {}
#line 1377 "parser.tab.cc"
    break;

  case 45: // parametromk: ">size" "=" "NUM"
#line 351 "parser.yy"
    {
        dsk_size = yystack_[0].value.as < std::string > ();
    }
#line 1385 "parser.tab.cc"
    break;

  case 46: // parametromk: ">fit" "=" "BF"
#line 355 "parser.yy"
    {
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1393 "parser.tab.cc"
    break;

  case 47: // parametromk: ">fit" "=" "FF"
#line 359 "parser.yy"
    {
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1401 "parser.tab.cc"
    break;

  case 48: // parametromk: ">fit" "=" "WF"
#line 363 "parser.yy"
    {
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1409 "parser.tab.cc"
    break;

  case 49: // parametromk: ">UNIT" "=" "K"
#line 367 "parser.yy"
    {
        unit = yystack_[0].value.as < std::string > ();
    }
#line 1417 "parser.tab.cc"
    break;

  case 50: // parametromk: ">UNIT" "=" "M"
#line 371 "parser.yy"
    {
        unit = yystack_[0].value.as < std::string > ();
    }
#line 1425 "parser.tab.cc"
    break;

  case 51: // parametromk: ">path" "=" "RUTA"
#line 375 "parser.yy"
    {
        path = yystack_[0].value.as < std::string > ();
    }
#line 1433 "parser.tab.cc"
    break;

  case 52: // Lista_fdisk: Lista_fdisk parametrofdisk
#line 381 "parser.yy"
                                    {}
#line 1439 "parser.tab.cc"
    break;

  case 53: // Lista_fdisk: parametrofdisk
#line 382 "parser.yy"
                                    {}
#line 1445 "parser.tab.cc"
    break;

  case 54: // parametrofdisk: ">size" "=" "NUM"
#line 387 "parser.yy"
      {
         dsk_size = yystack_[0].value.as < std::string > ();
      }
#line 1453 "parser.tab.cc"
    break;

  case 55: // parametrofdisk: ">path" "=" "RUTA"
#line 391 "parser.yy"
      {
         path = yystack_[0].value.as < std::string > ();
      }
#line 1461 "parser.tab.cc"
    break;

  case 56: // parametrofdisk: ">name" "=" "CADENA"
#line 395 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1469 "parser.tab.cc"
    break;

  case 57: // parametrofdisk: ">UNIT" "=" "B"
#line 399 "parser.yy"
      {
         unit = yystack_[0].value.as < std::string > ();
      }
#line 1477 "parser.tab.cc"
    break;

  case 58: // parametrofdisk: ">UNIT" "=" "K"
#line 403 "parser.yy"
      {
         unit = yystack_[0].value.as < std::string > ();
      }
#line 1485 "parser.tab.cc"
    break;

  case 59: // parametrofdisk: ">UNIT" "=" "M"
#line 407 "parser.yy"
      {
         unit = yystack_[0].value.as < std::string > ();
      }
#line 1493 "parser.tab.cc"
    break;

  case 60: // parametrofdisk: ">type" "=" "P"
#line 411 "parser.yy"
      {
         type = yystack_[0].value.as < std::string > ();
      }
#line 1501 "parser.tab.cc"
    break;

  case 61: // parametrofdisk: ">type" "=" "E"
#line 415 "parser.yy"
      {
         type = yystack_[0].value.as < std::string > ();
      }
#line 1509 "parser.tab.cc"
    break;

  case 62: // parametrofdisk: ">type" "=" "L"
#line 419 "parser.yy"
      {
         type = yystack_[0].value.as < std::string > ();
      }
#line 1517 "parser.tab.cc"
    break;

  case 63: // parametrofdisk: ">fit" "=" "BF"
#line 423 "parser.yy"
      {
         fit = yystack_[0].value.as < std::string > ();
      }
#line 1525 "parser.tab.cc"
    break;

  case 64: // parametrofdisk: ">fit" "=" "FF"
#line 427 "parser.yy"
      {
         fit = yystack_[0].value.as < std::string > ();
      }
#line 1533 "parser.tab.cc"
    break;

  case 65: // parametrofdisk: ">fit" "=" "WF"
#line 431 "parser.yy"
      {
         fit = yystack_[0].value.as < std::string > ();
      }
#line 1541 "parser.tab.cc"
    break;

  case 66: // parametrofdisk: ">delete" "=" "full"
#line 435 "parser.yy"
      {
         delete_ = yystack_[0].value.as < std::string > ();
      }
#line 1549 "parser.tab.cc"
    break;

  case 67: // parametrofdisk: ">add" "=" "NUM"
#line 439 "parser.yy"
      {
         add = yystack_[0].value.as < std::string > ();
      }
#line 1557 "parser.tab.cc"
    break;

  case 68: // Lista_mkfs: Lista_mkfs param_mkfs
#line 445 "parser.yy"
                                                {}
#line 1563 "parser.tab.cc"
    break;

  case 69: // Lista_mkfs: param_mkfs
#line 446 "parser.yy"
                                                {}
#line 1569 "parser.tab.cc"
    break;

  case 70: // param_mkfs: ">id" "=" "CADENA"
#line 451 "parser.yy"
      {
         id = yystack_[0].value.as < std::string > ();
      }
#line 1577 "parser.tab.cc"
    break;

  case 71: // param_mkfs: ">type" "=" "full"
#line 455 "parser.yy"
      {
         type = yystack_[0].value.as < std::string > ();
      }
#line 1585 "parser.tab.cc"
    break;

  case 72: // param_mkfs: ">fs" "=" "2fs"
#line 459 "parser.yy"
      {
         fs = yystack_[0].value.as < std::string > ();
      }
#line 1593 "parser.tab.cc"
    break;

  case 73: // param_mkfs: ">fs" "=" "3fs"
#line 463 "parser.yy"
      {
         fs = yystack_[0].value.as < std::string > ();
      }
#line 1601 "parser.tab.cc"
    break;

  case 74: // Lista_login: Lista_login param_login
#line 469 "parser.yy"
                                             {}
#line 1607 "parser.tab.cc"
    break;

  case 75: // Lista_login: param_login
#line 470 "parser.yy"
                                             {}
#line 1613 "parser.tab.cc"
    break;

  case 76: // param_login: ">user" "=" "CADENA"
#line 475 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1621 "parser.tab.cc"
    break;

  case 77: // param_login: ">pass" "=" "CADENA"
#line 479 "parser.yy"
      {
         std::cout << "PASSWORD: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1629 "parser.tab.cc"
    break;

  case 78: // param_login: ">pass" "=" "NUM"
#line 483 "parser.yy"
      {
         std::cout << "PASSWORD: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1637 "parser.tab.cc"
    break;

  case 79: // param_login: ">id" "=" "CADENA"
#line 487 "parser.yy"
      {
         std::cout << "ID: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1645 "parser.tab.cc"
    break;

  case 80: // Lista_mkusr: Lista_mkusr param_mkusr
#line 493 "parser.yy"
                                             {}
#line 1651 "parser.tab.cc"
    break;

  case 81: // Lista_mkusr: param_mkusr
#line 494 "parser.yy"
                                             {}
#line 1657 "parser.tab.cc"
    break;

  case 82: // param_mkusr: ">user" "=" "CADENA"
#line 499 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1665 "parser.tab.cc"
    break;

  case 83: // param_mkusr: ">pass" "=" "CADENA"
#line 503 "parser.yy"
      {
         std::cout << "PASS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1673 "parser.tab.cc"
    break;

  case 84: // param_mkusr: ">pass" "=" "NUM"
#line 507 "parser.yy"
      {
         std::cout << "PASS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1681 "parser.tab.cc"
    break;

  case 85: // param_mkusr: ">grp" "=" "CADENA"
#line 511 "parser.yy"
      {
         std::cout << "GROUP: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1689 "parser.tab.cc"
    break;

  case 86: // Lista_mkfile: Lista_mkfile param_mkfile
#line 517 "parser.yy"
                                               {}
#line 1695 "parser.tab.cc"
    break;

  case 87: // Lista_mkfile: param_mkfile
#line 518 "parser.yy"
                                               {}
#line 1701 "parser.tab.cc"
    break;

  case 88: // param_mkfile: ">path" "=" "RUTA"
#line 523 "parser.yy"
      {
         std::cout << "PATH: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1709 "parser.tab.cc"
    break;

  case 89: // param_mkfile: ">r"
#line 527 "parser.yy"
      {
         std::cout << "R " << std::endl;
      }
#line 1717 "parser.tab.cc"
    break;

  case 90: // param_mkfile: ">size" "=" "NUM"
#line 531 "parser.yy"
      {
         std::cout << "SIZE: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1725 "parser.tab.cc"
    break;

  case 91: // param_mkfile: ">cont" "=" "RUTA"
#line 535 "parser.yy"
      {
         std::cout << "CONT: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1733 "parser.tab.cc"
    break;

  case 92: // Lista_cat: Lista_cat param_cat
#line 541 "parser.yy"
                                       {}
#line 1739 "parser.tab.cc"
    break;

  case 93: // Lista_cat: param_cat
#line 542 "parser.yy"
                                       {}
#line 1745 "parser.tab.cc"
    break;

  case 94: // param_cat: "FILEN" "=" "RUTA"
#line 547 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "FILE: " << yystack_[2].value.as < std::string > () << std::endl;
      }
#line 1754 "parser.tab.cc"
    break;

  case 97: // param_chown: ">path" "=" "RUTA"
#line 560 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1762 "parser.tab.cc"
    break;

  case 98: // param_chown: ">user" "=" "CADENA"
#line 564 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1770 "parser.tab.cc"
    break;

  case 99: // param_chown: ">r"
#line 568 "parser.yy"
      {
         std::cout << "R" << std::endl;
      }
#line 1778 "parser.tab.cc"
    break;

  case 102: // param_chmod: ">path" "=" "RUTA"
#line 580 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1786 "parser.tab.cc"
    break;

  case 103: // param_chmod: ">ugo" "=" "NUM"
#line 584 "parser.yy"
      {
         std::cout << "UGO: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1794 "parser.tab.cc"
    break;

  case 104: // param_chmod: ">r"
#line 588 "parser.yy"
      {
         std::cout << "R" << std::endl;
      }
#line 1802 "parser.tab.cc"
    break;

  case 107: // param_rep: ">name" "=" "mbr"
#line 600 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1810 "parser.tab.cc"
    break;

  case 108: // param_rep: ">name" "=" "disk"
#line 604 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1818 "parser.tab.cc"
    break;

  case 109: // param_rep: ">name" "=" "inode"
#line 608 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1826 "parser.tab.cc"
    break;

  case 110: // param_rep: ">name" "=" "journaling"
#line 612 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1834 "parser.tab.cc"
    break;

  case 111: // param_rep: ">name" "=" "block"
#line 616 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1842 "parser.tab.cc"
    break;

  case 112: // param_rep: ">name" "=" "bm_inode"
#line 620 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1850 "parser.tab.cc"
    break;

  case 113: // param_rep: ">name" "=" "bm_block"
#line 624 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1858 "parser.tab.cc"
    break;

  case 114: // param_rep: ">name" "=" "tree"
#line 628 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1866 "parser.tab.cc"
    break;

  case 115: // param_rep: ">name" "=" "sb"
#line 632 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1874 "parser.tab.cc"
    break;

  case 116: // param_rep: ">name" "=" "file"
#line 636 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1882 "parser.tab.cc"
    break;

  case 117: // param_rep: ">name" "=" "ls"
#line 640 "parser.yy"
      {
         name = yystack_[0].value.as < std::string > ();
      }
#line 1890 "parser.tab.cc"
    break;

  case 118: // param_rep: ">path" "=" "RUTA"
#line 644 "parser.yy"
      {
         path = yystack_[0].value.as < std::string > ();
      }
#line 1898 "parser.tab.cc"
    break;

  case 119: // param_rep: ">id" "=" "CADENA"
#line 648 "parser.yy"
      {
         id = yystack_[0].value.as < std::string > ();
      }
#line 1906 "parser.tab.cc"
    break;

  case 120: // param_rep: ">ruta" "=" "RUTA"
#line 652 "parser.yy"
      {
         comruta = yystack_[0].value.as < std::string > ();
      }
#line 1914 "parser.tab.cc"
    break;


#line 1918 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -28;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      -3,    27,   -18,    14,    -4,   -10,    17,    23,   -28,    45,
      50,    30,    56,   -14,   -27,    59,   -12,    31,    54,   -22,
     -19,    35,    -8,    49,   -21,   -28,    66,   -20,    60,    61,
     121,    -3,   -28,    73,    74,    75,    76,    27,   -28,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    14,   -28,
      86,    87,    88,    89,    90,    91,    17,   -28,    92,    93,
      94,    23,   -28,    95,    96,    97,    98,    99,    30,   -28,
     100,   -28,   101,   102,   103,   -14,   -28,   104,   -27,   -28,
     105,   106,   107,   108,   109,   110,   111,   112,   114,   115,
     116,   117,   118,   -28,   119,   120,    -8,   -28,   122,   123,
     -28,   124,   125,   -21,   -28,   126,   127,   128,   129,   130,
     -20,   -28,   131,   132,   -28,   -28,   113,   133,    25,     2,
     -28,   134,   135,   136,    28,    29,   137,    32,   138,   139,
     -28,   140,   141,   142,   150,   143,    52,   -28,   144,   145,
      34,   -28,   146,   147,   148,    36,   149,   -28,   151,   152,
     153,   155,   -28,   156,   -28,   157,   158,   159,   160,   161,
     154,   163,   164,   165,   166,   167,   168,   169,   171,   172,
     -28,   173,   174,   176,   170,   -28,   177,   178,    16,   179,
     181,   -28,   182,   183,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   162,   187,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   193,
     195,   205,   211,   186,   215,   201,   216,   202,   217,   218,
     219,   -28,   -28,   207,   213,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   180,   223,   226,   227,   228,   229,
     -28,   -28,   230,   231,   232,   233,   234,   235,   236,   237,
     208,   210,   212,   214,   220,   222,   224,   225,   238,   239,
     240,   242,   243,   244,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     2,     4,     0,     0,     0,     0,     5,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,    53,
       0,     0,     0,     0,     0,     0,    11,    69,     0,     0,
       0,    12,    75,     0,     0,     0,     0,     0,    17,    81,
       0,    89,     0,     0,     0,    18,    87,     0,    19,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,    34,    96,     0,     0,
     104,     0,     0,    37,   101,     0,     0,     0,     0,     0,
      41,   106,     0,     0,     1,     3,     0,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,    68,     0,     0,
       0,    74,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,    86,     0,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,   105,     0,     0,    45,    51,    46,    47,    48,    49,
      50,     6,    54,    55,    63,    64,    65,    58,    59,    57,
      56,    60,    61,    62,    66,    67,     0,     0,    10,    71,
      70,    72,    73,    79,    76,    77,    78,    14,    15,    82,
      83,    84,    85,    16,    90,    88,    91,    94,    20,     0,
       0,     0,     0,     0,    25,     0,     0,     0,     0,     0,
       0,    97,    98,     0,     0,   102,   103,    40,   118,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     119,   120,    38,    39,     0,     0,     0,     0,     0,     0,
      27,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    21,    22,    23,    24,
      28,    29,    30,    31,    32,    33,    35,    36
  };

  const short
  Parser::yypgoto_[] =
  {
     -28,   -28,   -28,   175,   -28,   252,   -28,   245,   -28,   241,
     -28,   246,   -28,   247,   -28,   221,   -28,   248,   -28,    63,
     -28,   188,   -28,   184
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,    30,    31,    32,    37,    38,    48,    49,    56,    57,
      61,    62,    68,    69,    75,    76,    78,    79,    96,    97,
     103,   104,   110,   111
  };

  const short
  Parser::yytable_[] =
  {
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   100,
      87,   101,   106,    89,    39,   107,    71,    72,    73,   108,
      81,    77,    93,    88,    94,   102,    90,   109,    50,    52,
      74,    51,    82,    95,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,    40,    41,    42,    43,    44,
      45,    46,    47,    53,   189,   190,    54,    55,    33,    34,
      35,    36,    58,    83,    59,    60,    84,    91,   211,   212,
      92,    65,    66,    67,   186,   187,   188,   194,   195,   196,
      63,   197,   198,   199,    85,    64,    86,   201,   202,   203,
      98,    80,    99,   215,   216,   220,   221,    70,   105,   112,
     113,   114,   116,   117,   118,   119,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   142,   143,   144,   145,   146,   148,
     149,   150,   151,   153,   155,   156,   157,   158,   159,   170,
     161,   162,   160,   163,   164,   165,   166,   167,   168,   169,
     204,   171,   172,   173,   174,   176,   177,   178,   179,   180,
     182,   183,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   184,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   233,     0,     0,   115,     0,     0,     0,
       0,   185,   191,     0,   193,   192,   200,   264,   206,   205,
     207,   208,   210,   213,   214,   217,   218,   219,   222,   280,
     223,   225,   224,   226,   227,   228,   229,   230,   231,   265,
     232,   234,   235,   236,   237,   238,   239,   267,   240,   241,
     246,   242,   243,   244,   245,   247,   248,   266,   260,   261,
     268,   262,   263,   269,   270,   271,   272,   274,   273,   275,
     278,   277,   281,   276,   279,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   120,
     296,   175,   297,   130,   181,     0,   152,   137,     0,   298,
     299,     0,   300,   301,     0,     0,     0,   141,     0,     0,
       0,     0,     0,     0,     0,   147,   302,   303,     0,   304,
     305,     0,   306,   307,     0,     0,   154
  };

  const signed char
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    50,
      52,    52,    52,    52,    52,    55,    50,    51,    52,    59,
      52,    68,    50,    65,    52,    66,    65,    67,    52,    59,
      64,    55,    64,    61,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    51,    52,    53,    54,    55,
      56,    57,    58,    56,    72,    73,    59,    60,    51,    52,
      53,    54,    59,    52,    61,    62,    55,    52,    36,    37,
      55,    61,    62,    63,    69,    70,    71,    69,    70,    71,
      55,    72,    73,    74,    50,    55,    52,    75,    76,    77,
      61,    52,    63,    79,    80,    79,    80,    61,    52,    59,
      59,     0,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    96,
      49,    49,    52,    49,    49,    49,    49,    49,    49,    49,
      32,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    78,    78,    -1,    78,    80,    79,    55,    78,    80,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    49,
      79,    78,    80,    78,    78,    78,    78,    78,    78,    52,
      79,    78,    78,    78,    78,    78,    78,    52,    79,    78,
      80,    79,    79,    79,    78,    78,    78,    64,    79,    78,
      55,    79,    79,    52,    78,    50,    65,    65,    52,    52,
      63,    52,    49,    55,    61,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    79,    78,    37,
      78,   103,    78,    48,   110,    -1,    75,    56,    -1,    79,
      78,    -1,    78,    78,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    78,    78,    -1,    79,
      78,    -1,    79,    79,    -1,    -1,    78
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      82,    83,    84,    51,    52,    53,    54,    85,    86,    52,
      51,    52,    53,    54,    55,    56,    57,    58,    87,    88,
      52,    55,    59,    56,    59,    60,    89,    90,    59,    61,
      62,    91,    92,    55,    55,    61,    62,    63,    93,    94,
      61,    50,    51,    52,    64,    95,    96,    68,    97,    98,
      52,    52,    64,    52,    55,    50,    52,    52,    65,    52,
      65,    52,    55,    50,    52,    61,    99,   100,    61,    63,
      50,    52,    66,   101,   102,    52,    52,    55,    59,    67,
     103,   104,    59,    59,     0,    84,    49,    49,    49,    49,
      86,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      88,    49,    49,    49,    49,    49,    49,    90,    49,    49,
      49,    92,    49,    49,    49,    49,    49,    94,    49,    49,
      49,    49,    96,    49,    98,    49,    49,    49,    49,    49,
      52,    49,    49,    49,    49,    49,    49,    49,    49,    49,
     100,    49,    49,    49,    49,   102,    49,    49,    49,    49,
      49,   104,    49,    49,    80,    78,    69,    70,    71,    72,
      73,    78,    80,    78,    69,    70,    71,    72,    73,    74,
      79,    75,    76,    77,    32,    80,    78,    79,    79,    32,
      79,    36,    37,    79,    79,    79,    80,    79,    79,    79,
      79,    80,    79,    79,    80,    78,    78,    78,    78,    78,
      78,    78,    79,    49,    78,    78,    78,    78,    78,    78,
      79,    78,    79,    79,    79,    78,    80,    78,    78,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      79,    78,    79,    79,    55,    52,    64,    52,    55,    52,
      78,    50,    65,    52,    65,    52,    55,    52,    63,    61,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    79,    78,    78,    78,    79,    78,
      78,    78,    78,    78,    79,    78,    79,    79
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    85,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    92,    92,    92,
      93,    93,    94,    94,    94,    94,    95,    95,    96,    96,
      96,    96,    97,    97,    98,    99,    99,   100,   100,   100,
     101,   101,   102,   102,   102,   103,   103,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     4,     2,     7,     7,
       4,     2,     2,     1,     4,     4,     4,     2,     2,     2,
       4,     7,     7,     7,     7,     4,     5,     5,     7,     7,
       7,     7,     7,     7,     2,     7,     7,     2,     4,     4,
       4,     2,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       3,     3,     3,     3,     2,     1,     3,     3,     3,     3,
       2,     1,     3,     3,     3,     3,     2,     1,     3,     1,
       3,     3,     2,     1,     3,     2,     1,     3,     3,     1,
       2,     1,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"eof\"", "error", "\"invalid token\"", "\"mkdisk\"", "\"rmdisk\"",
  "\"fdisk\"", "\"mount\"", "\"unmount\"", "\"mkfs\"", "\"login\"",
  "\"logout\"", "\"mkgrp\"", "\"rmgrp\"", "\"mkusr\"", "\"rmusr\"",
  "\"mkfile\"", "\"cat\"", "\"remove\"", "\"edit\"", "\"rename\"",
  "\"mkdir\"", "\"copy\"", "\"move\"", "\"find\"", "\"chown\"",
  "\"chgrp\"", "\"chmod\"", "\"pause\"", "\"execute\"", "\"rep\"",
  "\"recovery\"", "\"loss\"", "\"full\"", "\"BestFit\"", "\"FirstFit\"",
  "\"WorstFit\"", "\"2fs\"", "\"3fs\"", "\"mbr\"", "\"disk\"", "\"inode\"",
  "\"journaling\"", "\"block\"", "\"bm_inode\"", "\"bm_block\"",
  "\"tree\"", "\"sb\"", "\"file\"", "\"ls\"", "\"=\"", "\">r\"",
  "\">size\"", "\">path\"", "\">fit\"", "\">UNIT\"", "\">name\"",
  "\">type\"", "\">delete\"", "\">add\"", "\">id\"", "\">fs\"",
  "\">user\"", "\">pass\"", "\">grp\"", "\">cont\"", "\">destino\"",
  "\">ugo\"", "\">ruta\"", "\"FILEN\"", "\"BF\"", "\"FF\"", "\"WF\"",
  "\"K\"", "\"M\"", "\"B\"", "\"P\"", "\"E\"", "\"L\"", "\"RUTA\"",
  "\"CADENA\"", "\"NUM\"", "$accept", "Inicio", "Lista", "COMANDO",
  "Lista_parametrosmkdisk", "parametromk", "Lista_fdisk", "parametrofdisk",
  "Lista_mkfs", "param_mkfs", "Lista_login", "param_login", "Lista_mkusr",
  "param_mkusr", "Lista_mkfile", "param_mkfile", "Lista_cat", "param_cat",
  "Lista_chown", "param_chown", "Lista_chmod", "param_chmod", "Lista_rep",
  "param_rep", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,    67,    67,    72,    73,    77,    94,   101,   130,   137,
     144,   150,   161,   165,   169,   174,   179,   184,   188,   192,
     196,   201,   207,   213,   219,   225,   230,   236,   242,   248,
     254,   260,   266,   272,   278,   282,   288,   294,   298,   303,
     308,   324,   337,   345,   346,   350,   354,   358,   362,   366,
     370,   374,   381,   382,   386,   390,   394,   398,   402,   406,
     410,   414,   418,   422,   426,   430,   434,   438,   445,   446,
     450,   454,   458,   462,   469,   470,   474,   478,   482,   486,
     493,   494,   498,   502,   506,   510,   517,   518,   522,   526,
     530,   534,   541,   542,   546,   554,   555,   559,   563,   567,
     574,   575,   579,   583,   587,   594,   595,   599,   603,   607,
     611,   615,   619,   623,   627,   631,   635,   639,   643,   647,
     651
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2586 "parser.tab.cc"

#line 657 "parser.yy"


void yy::Parser::error( const std::string& error){
  
}
