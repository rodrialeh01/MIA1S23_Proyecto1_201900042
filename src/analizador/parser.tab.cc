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
#line 19 "parser.yy"

   
   #include <string>
   #include <stdio.h>
   #include "driver.h"
   #include <iostream>
   #include "../Comandos/Mkdisk.h"

   std::string dsk_size = "";
   std::string path = "";
   std::string fit = "";
   std::string unit = ""; 

#line 55 "parser.tab.cc"


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
#line 133 "parser.tab.cc"

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
#line 44 "parser.yy"
                                    {}
#line 910 "parser.tab.cc"
    break;

  case 3: // Lista: Lista COMANDO
#line 49 "parser.yy"
                                    {}
#line 916 "parser.tab.cc"
    break;

  case 4: // Lista: COMANDO
#line 50 "parser.yy"
                                    {}
#line 922 "parser.tab.cc"
    break;

  case 5: // COMANDO: "mkdisk" Lista_parametrosmkdisk
#line 55 "parser.yy"
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
      }
#line 939 "parser.tab.cc"
    break;

  case 6: // COMANDO: "rmdisk" ">path" "=" "RUTA"
#line 68 "parser.yy"
      {
         std::cout << "COMANDO RMDISK" << std::endl;
         std::cout << "RUTA: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 948 "parser.tab.cc"
    break;

  case 7: // COMANDO: "fdisk" Lista_fdisk
#line 73 "parser.yy"
      {
         std::cout << "COMANDO FDISK:" << std::endl;
      }
#line 956 "parser.tab.cc"
    break;

  case 8: // COMANDO: "mount" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 77 "parser.yy"
      {
         std::cout << "COMANDO MOUNT" << std::endl;
         std::cout << "RUTA: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 966 "parser.tab.cc"
    break;

  case 9: // COMANDO: "mount" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 83 "parser.yy"
      {
         std::cout << "COMANDO MOUNT" << std::endl;
         std::cout << "RUTA: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 976 "parser.tab.cc"
    break;

  case 10: // COMANDO: "unmount" ">id" "=" "CADENA"
#line 89 "parser.yy"
      {
         std::cout << "COMANDO UNMOUNT" << std::endl;
         std::cout << "ID: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 985 "parser.tab.cc"
    break;

  case 11: // COMANDO: "mkfs" Lista_mkfs
#line 94 "parser.yy"
      {
         std::cout << "COMANDO MKFS" << std::endl;
      }
#line 993 "parser.tab.cc"
    break;

  case 12: // COMANDO: "login" Lista_login
#line 98 "parser.yy"
      {
         std::cout << "COMANDO LOGIN" << std::endl;
      }
#line 1001 "parser.tab.cc"
    break;

  case 13: // COMANDO: "logout"
#line 102 "parser.yy"
      {
         std::cout << "COMANDO LOGOUT" << std::endl;
      }
#line 1009 "parser.tab.cc"
    break;

  case 14: // COMANDO: "mkgrp" ">name" "=" "CADENA"
#line 106 "parser.yy"
      {
         std::cout << "COMANDO MKGRP" << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1018 "parser.tab.cc"
    break;

  case 15: // COMANDO: "rmgrp" ">name" "=" "CADENA"
#line 111 "parser.yy"
      {
         std::cout << "COMANDO RMGRP" << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1027 "parser.tab.cc"
    break;

  case 16: // COMANDO: "rmusr" ">user" "=" "CADENA"
#line 116 "parser.yy"
      {
         std::cout << "COMANDO RMUSR" << std::endl;
         std::cout << "USER: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1036 "parser.tab.cc"
    break;

  case 17: // COMANDO: "mkusr" Lista_mkusr
#line 121 "parser.yy"
      {
         std::cout << "COMANDO MKUSR" << std::endl;
      }
#line 1044 "parser.tab.cc"
    break;

  case 18: // COMANDO: "mkfile" Lista_mkfile
#line 125 "parser.yy"
      {
         std::cout << "COMANDO MKFILE" << std::endl;
      }
#line 1052 "parser.tab.cc"
    break;

  case 19: // COMANDO: "cat" Lista_cat
#line 129 "parser.yy"
      {
         std::cout << "COMANDO CAT" << std::endl;
      }
#line 1060 "parser.tab.cc"
    break;

  case 20: // COMANDO: "remove" ">path" "=" "RUTA"
#line 133 "parser.yy"
      {
         std::cout << "COMANDO REMOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1069 "parser.tab.cc"
    break;

  case 21: // COMANDO: "edit" ">path" "=" "RUTA" ">cont" "=" "RUTA"
#line 138 "parser.yy"
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "CONT: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1079 "parser.tab.cc"
    break;

  case 22: // COMANDO: "edit" ">cont" "=" "RUTA" ">path" "=" "RUTA"
#line 144 "parser.yy"
      {
         std::cout << "COMANDO EDIT" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "CONT: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1089 "parser.tab.cc"
    break;

  case 23: // COMANDO: "rename" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 150 "parser.yy"
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1099 "parser.tab.cc"
    break;

  case 24: // COMANDO: "rename" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 156 "parser.yy"
      {
         std::cout << "COMANDO RENAME" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1109 "parser.tab.cc"
    break;

  case 25: // COMANDO: "mkdir" ">path" "=" "RUTA"
#line 162 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1118 "parser.tab.cc"
    break;

  case 26: // COMANDO: "mkdir" ">path" "=" "RUTA" ">r"
#line 167 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[1].value.as < std::string > () << std::endl;
         std::cout << "R" << std::endl;
      }
#line 1128 "parser.tab.cc"
    break;

  case 27: // COMANDO: "mkdir" ">r" ">path" "=" "RUTA"
#line 173 "parser.yy"
      {
         std::cout << "COMANDO MKDIR" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "R" << std::endl;
      }
#line 1138 "parser.tab.cc"
    break;

  case 28: // COMANDO: "copy" ">path" "=" "RUTA" ">destino" "=" "RUTA"
#line 179 "parser.yy"
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1148 "parser.tab.cc"
    break;

  case 29: // COMANDO: "copy" ">destino" "=" "RUTA" ">path" "=" "RUTA"
#line 185 "parser.yy"
      {
         std::cout << "COMANDO COPY" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1158 "parser.tab.cc"
    break;

  case 30: // COMANDO: "move" ">path" "=" "RUTA" ">destino" "=" "RUTA"
#line 191 "parser.yy"
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1168 "parser.tab.cc"
    break;

  case 31: // COMANDO: "move" ">destino" "=" "RUTA" ">path" "=" "RUTA"
#line 197 "parser.yy"
      {
         std::cout << "COMANDO MOVE" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "DESTINO: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1178 "parser.tab.cc"
    break;

  case 32: // COMANDO: "find" ">path" "=" "RUTA" ">name" "=" "CADENA"
#line 203 "parser.yy"
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1188 "parser.tab.cc"
    break;

  case 33: // COMANDO: "find" ">name" "=" "CADENA" ">path" "=" "RUTA"
#line 209 "parser.yy"
      {
         std::cout << "COMANDO FIND" << std::endl;
         std::cout << "PATH: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "NAME: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1198 "parser.tab.cc"
    break;

  case 34: // COMANDO: "chown" Lista_chown
#line 215 "parser.yy"
      {
         std::cout << "COMANDO CHOWN" << std::endl;
      }
#line 1206 "parser.tab.cc"
    break;

  case 35: // COMANDO: "chgrp" ">user" "=" "CADENA" ">grp" "=" "CADENA"
#line 219 "parser.yy"
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< yystack_[3].value.as < std::string > () << std::endl;
         std::cout << "GRP: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1216 "parser.tab.cc"
    break;

  case 36: // COMANDO: "chgrp" ">grp" "=" "CADENA" ">user" "=" "CADENA"
#line 225 "parser.yy"
      {
         std::cout << "COMANDO CHRGP" << std::endl;
         std::cout << "USER: "<< yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "GRP: "<< yystack_[3].value.as < std::string > () << std::endl;
      }
#line 1226 "parser.tab.cc"
    break;

  case 37: // COMANDO: "chmod" Lista_chmod
#line 231 "parser.yy"
      {
         std::cout << "COMANDO CHMOD" << std::endl;
      }
#line 1234 "parser.tab.cc"
    break;

  case 38: // COMANDO: "execute" ">path" "=" "RUTA"
#line 235 "parser.yy"
      {
        std::cout << "COMANDO EXECUTE" << std::endl;
        std::cout << "RUTA: "<< yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1243 "parser.tab.cc"
    break;

  case 39: // COMANDO: "rep" Lista_rep
#line 240 "parser.yy"
      {
         std::cout << "COMANDO REP" << std::endl;
      }
#line 1251 "parser.tab.cc"
    break;

  case 40: // COMANDO: "pause"
#line 244 "parser.yy"
      {
        std::cout << "Presione una tecla para continuar..." << std::endl;
        std::cin.ignore();
      }
#line 1260 "parser.tab.cc"
    break;

  case 41: // Lista_parametrosmkdisk: Lista_parametrosmkdisk parametromk
#line 251 "parser.yy"
                                           {}
#line 1266 "parser.tab.cc"
    break;

  case 42: // Lista_parametrosmkdisk: parametromk
#line 252 "parser.yy"
                                      {}
#line 1272 "parser.tab.cc"
    break;

  case 43: // parametromk: ">size" "=" "NUM"
#line 257 "parser.yy"
    {
        std::cout << "SIZE: " << yystack_[0].value.as < std::string > () << std::endl;
        dsk_size = yystack_[0].value.as < std::string > ();
    }
#line 1281 "parser.tab.cc"
    break;

  case 44: // parametromk: ">fit" "=" "BF"
#line 262 "parser.yy"
    {
        std::cout << "FIT: BEST"<< std::endl;
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1290 "parser.tab.cc"
    break;

  case 45: // parametromk: ">fit" "=" "FF"
#line 267 "parser.yy"
    {
        std::cout << "FIT: FIRST"<< std::endl;
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1299 "parser.tab.cc"
    break;

  case 46: // parametromk: ">fit" "=" "WF"
#line 272 "parser.yy"
    {
        std::cout << "FIT: WORST"<< std::endl;
        fit = yystack_[0].value.as < std::string > ();
    }
#line 1308 "parser.tab.cc"
    break;

  case 47: // parametromk: ">UNIT" "=" "K"
#line 277 "parser.yy"
    {
        std::cout << "UNIDADES: KILOBYTES" << std::endl;
        unit = yystack_[0].value.as < std::string > ();
    }
#line 1317 "parser.tab.cc"
    break;

  case 48: // parametromk: ">UNIT" "=" "M"
#line 282 "parser.yy"
    {
        std::cout << "UNIDADES: MEGABYTES" << std::endl;
        unit = yystack_[0].value.as < std::string > ();
    }
#line 1326 "parser.tab.cc"
    break;

  case 49: // parametromk: ">path" "=" "RUTA"
#line 287 "parser.yy"
    {
        std::cout << "RUTA: "<< yystack_[0].value.as < std::string > () << std::endl;
        path = yystack_[0].value.as < std::string > ();
    }
#line 1335 "parser.tab.cc"
    break;

  case 50: // Lista_fdisk: Lista_fdisk parametrofdisk
#line 294 "parser.yy"
                                    {}
#line 1341 "parser.tab.cc"
    break;

  case 51: // Lista_fdisk: parametrofdisk
#line 295 "parser.yy"
                                    {}
#line 1347 "parser.tab.cc"
    break;

  case 52: // parametrofdisk: ">size" "=" "NUM"
#line 300 "parser.yy"
      {
         std::cout << "SIZE: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1355 "parser.tab.cc"
    break;

  case 53: // parametrofdisk: ">path" "=" "RUTA"
#line 304 "parser.yy"
      {
         std::cout << "PATH: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1363 "parser.tab.cc"
    break;

  case 54: // parametrofdisk: ">name" "=" "CADENA"
#line 308 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1371 "parser.tab.cc"
    break;

  case 55: // parametrofdisk: ">UNIT" "=" "B"
#line 312 "parser.yy"
      {
         std::cout << "UNIT: BYTES" << std::endl;
      }
#line 1379 "parser.tab.cc"
    break;

  case 56: // parametrofdisk: ">UNIT" "=" "K"
#line 316 "parser.yy"
      {
         std::cout << "UNIT: KILOBYTES" << std::endl;
      }
#line 1387 "parser.tab.cc"
    break;

  case 57: // parametrofdisk: ">UNIT" "=" "M"
#line 320 "parser.yy"
      {
         std::cout << "UNIT: MEGABYTES" << std::endl;
      }
#line 1395 "parser.tab.cc"
    break;

  case 58: // parametrofdisk: ">type" "=" "P"
#line 324 "parser.yy"
      {
         std::cout << "TYPE: PRIMARY"<< std::endl;
      }
#line 1403 "parser.tab.cc"
    break;

  case 59: // parametrofdisk: ">type" "=" "E"
#line 328 "parser.yy"
      {
         std::cout << "TYPE: EXTEND" <<std::endl;
      }
#line 1411 "parser.tab.cc"
    break;

  case 60: // parametrofdisk: ">type" "=" "L"
#line 332 "parser.yy"
      {
         std::cout << "TYPE: LOGIC" << std::endl;
      }
#line 1419 "parser.tab.cc"
    break;

  case 61: // parametrofdisk: ">fit" "=" "BF"
#line 336 "parser.yy"
      {
         std::cout << "FIT: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1427 "parser.tab.cc"
    break;

  case 62: // parametrofdisk: ">fit" "=" "FF"
#line 340 "parser.yy"
      {
         std::cout << "FIT: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1435 "parser.tab.cc"
    break;

  case 63: // parametrofdisk: ">fit" "=" "WF"
#line 344 "parser.yy"
      {
         std::cout << "FIT: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1443 "parser.tab.cc"
    break;

  case 64: // parametrofdisk: ">delete" "=" "full"
#line 348 "parser.yy"
      {
         std::cout << "DELETE: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1451 "parser.tab.cc"
    break;

  case 65: // parametrofdisk: ">add" "=" "NUM"
#line 352 "parser.yy"
      {
         std::cout << "ADD: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1459 "parser.tab.cc"
    break;

  case 66: // Lista_mkfs: Lista_mkfs param_mkfs
#line 358 "parser.yy"
                                                {}
#line 1465 "parser.tab.cc"
    break;

  case 67: // Lista_mkfs: param_mkfs
#line 359 "parser.yy"
                                                {}
#line 1471 "parser.tab.cc"
    break;

  case 68: // param_mkfs: ">id" "=" "CADENA"
#line 364 "parser.yy"
      {
         std::cout << "ID: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1479 "parser.tab.cc"
    break;

  case 69: // param_mkfs: ">type" "=" "full"
#line 368 "parser.yy"
      {
         std::cout << "TYPE: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1487 "parser.tab.cc"
    break;

  case 70: // param_mkfs: ">fs" "=" "2fs"
#line 372 "parser.yy"
      {
         std::cout << "FS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1495 "parser.tab.cc"
    break;

  case 71: // param_mkfs: ">fs" "=" "3fs"
#line 376 "parser.yy"
      {
         std::cout << "FS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1503 "parser.tab.cc"
    break;

  case 72: // Lista_login: Lista_login param_login
#line 382 "parser.yy"
                                             {}
#line 1509 "parser.tab.cc"
    break;

  case 73: // Lista_login: param_login
#line 383 "parser.yy"
                                             {}
#line 1515 "parser.tab.cc"
    break;

  case 74: // param_login: ">user" "=" "CADENA"
#line 388 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1523 "parser.tab.cc"
    break;

  case 75: // param_login: ">pass" "=" "CADENA"
#line 392 "parser.yy"
      {
         std::cout << "PASSWORD: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1531 "parser.tab.cc"
    break;

  case 76: // param_login: ">pass" "=" "NUM"
#line 396 "parser.yy"
      {
         std::cout << "PASSWORD: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1539 "parser.tab.cc"
    break;

  case 77: // param_login: ">id" "=" "CADENA"
#line 400 "parser.yy"
      {
         std::cout << "ID: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1547 "parser.tab.cc"
    break;

  case 78: // Lista_mkusr: Lista_mkusr param_mkusr
#line 406 "parser.yy"
                                             {}
#line 1553 "parser.tab.cc"
    break;

  case 79: // Lista_mkusr: param_mkusr
#line 407 "parser.yy"
                                             {}
#line 1559 "parser.tab.cc"
    break;

  case 80: // param_mkusr: ">user" "=" "CADENA"
#line 412 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1567 "parser.tab.cc"
    break;

  case 81: // param_mkusr: ">pass" "=" "CADENA"
#line 416 "parser.yy"
      {
         std::cout << "PASS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1575 "parser.tab.cc"
    break;

  case 82: // param_mkusr: ">pass" "=" "NUM"
#line 420 "parser.yy"
      {
         std::cout << "PASS: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1583 "parser.tab.cc"
    break;

  case 83: // param_mkusr: ">grp" "=" "CADENA"
#line 424 "parser.yy"
      {
         std::cout << "GROUP: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1591 "parser.tab.cc"
    break;

  case 84: // Lista_mkfile: Lista_mkfile param_mkfile
#line 430 "parser.yy"
                                               {}
#line 1597 "parser.tab.cc"
    break;

  case 85: // Lista_mkfile: param_mkfile
#line 431 "parser.yy"
                                               {}
#line 1603 "parser.tab.cc"
    break;

  case 86: // param_mkfile: ">path" "=" "RUTA"
#line 436 "parser.yy"
      {
         std::cout << "PATH: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1611 "parser.tab.cc"
    break;

  case 87: // param_mkfile: ">r"
#line 440 "parser.yy"
      {
         std::cout << "R " << std::endl;
      }
#line 1619 "parser.tab.cc"
    break;

  case 88: // param_mkfile: ">size" "=" "NUM"
#line 444 "parser.yy"
      {
         std::cout << "SIZE: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1627 "parser.tab.cc"
    break;

  case 89: // param_mkfile: ">cont" "=" "RUTA"
#line 448 "parser.yy"
      {
         std::cout << "CONT: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1635 "parser.tab.cc"
    break;

  case 90: // Lista_cat: Lista_cat param_cat
#line 454 "parser.yy"
                                       {}
#line 1641 "parser.tab.cc"
    break;

  case 91: // Lista_cat: param_cat
#line 455 "parser.yy"
                                       {}
#line 1647 "parser.tab.cc"
    break;

  case 92: // param_cat: "FILEN" "=" "RUTA"
#line 460 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
         std::cout << "FILE: " << yystack_[2].value.as < std::string > () << std::endl;
      }
#line 1656 "parser.tab.cc"
    break;

  case 95: // param_chown: ">path" "=" "RUTA"
#line 473 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1664 "parser.tab.cc"
    break;

  case 96: // param_chown: ">user" "=" "CADENA"
#line 477 "parser.yy"
      {
         std::cout << "USER: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1672 "parser.tab.cc"
    break;

  case 97: // param_chown: ">r"
#line 481 "parser.yy"
      {
         std::cout << "R" << std::endl;
      }
#line 1680 "parser.tab.cc"
    break;

  case 100: // param_chmod: ">path" "=" "RUTA"
#line 493 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1688 "parser.tab.cc"
    break;

  case 101: // param_chmod: ">ugo" "=" "NUM"
#line 497 "parser.yy"
      {
         std::cout << "UGO: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1696 "parser.tab.cc"
    break;

  case 102: // param_chmod: ">r"
#line 501 "parser.yy"
      {
         std::cout << "R" << std::endl;
      }
#line 1704 "parser.tab.cc"
    break;

  case 105: // param_rep: ">name" "=" "mbr"
#line 513 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1712 "parser.tab.cc"
    break;

  case 106: // param_rep: ">name" "=" "disk"
#line 517 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1720 "parser.tab.cc"
    break;

  case 107: // param_rep: ">name" "=" "inode"
#line 521 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1728 "parser.tab.cc"
    break;

  case 108: // param_rep: ">name" "=" "journaling"
#line 525 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1736 "parser.tab.cc"
    break;

  case 109: // param_rep: ">name" "=" "block"
#line 529 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1744 "parser.tab.cc"
    break;

  case 110: // param_rep: ">name" "=" "bm_inode"
#line 533 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1752 "parser.tab.cc"
    break;

  case 111: // param_rep: ">name" "=" "bm_block"
#line 537 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1760 "parser.tab.cc"
    break;

  case 112: // param_rep: ">name" "=" "tree"
#line 541 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1768 "parser.tab.cc"
    break;

  case 113: // param_rep: ">name" "=" "sb"
#line 545 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1776 "parser.tab.cc"
    break;

  case 114: // param_rep: ">name" "=" "file"
#line 549 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1784 "parser.tab.cc"
    break;

  case 115: // param_rep: ">name" "=" "ls"
#line 553 "parser.yy"
      {
         std::cout << "NAME: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1792 "parser.tab.cc"
    break;

  case 116: // param_rep: ">path" "=" "RUTA"
#line 557 "parser.yy"
      {
         std::cout << "PATH: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1800 "parser.tab.cc"
    break;

  case 117: // param_rep: ">id" "=" "CADENA"
#line 561 "parser.yy"
      {
         std::cout << "ID: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1808 "parser.tab.cc"
    break;

  case 118: // param_rep: ">ruta" "=" "RUTA"
#line 565 "parser.yy"
      {
         std::cout << "RUTA: " << yystack_[0].value.as < std::string > () << std::endl;
      }
#line 1816 "parser.tab.cc"
    break;


#line 1820 "parser.tab.cc"

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
     -19,    35,    -8,    49,   -21,   -28,    66,   -20,   117,    -3,
     -28,    71,    72,    73,    74,    27,   -28,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    14,   -28,    84,    85,
      86,    87,    88,    89,    17,   -28,    90,    91,    92,    23,
     -28,    93,    94,    95,    96,    97,    30,   -28,    98,   -28,
      99,   100,   101,   -14,   -28,   102,   -27,   -28,   103,   104,
     105,   106,   107,   108,   109,   110,   112,   113,   114,   115,
     116,   -28,   118,   119,    -8,   -28,   120,   121,   -28,   122,
     123,   -21,   -28,   124,   125,   126,   127,   128,   -20,   -28,
     -28,   -28,   111,   129,    25,     2,   -28,   130,   131,   132,
      28,    29,   133,    32,   134,   135,   -28,   136,   137,   138,
     146,   139,    52,   -28,   140,   141,    34,   -28,   142,   143,
     144,    36,   145,   -28,   147,   148,   149,   151,   -28,   152,
     -28,   153,   154,   155,   156,   157,   150,   159,   160,   161,
     162,   163,   164,   165,   167,   168,   -28,   169,   170,   172,
     166,   -28,   173,   174,    16,   175,   177,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     158,   183,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   179,   201,   202,   204,   180,   209,   195,
     210,   196,   211,   212,   213,   -28,   -28,   203,   207,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   176,   215,   220,   221,
     222,   223,   -28,   -28,   224,   225,   226,   227,   228,   229,
     230,   231,   205,   208,   214,   216,   206,   217,   218,   219,
     232,   233,   234,   236,   237,   238,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,     0,     0,     0,     2,
       4,     0,     0,     0,     0,     5,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,    51,     0,     0,
       0,     0,     0,     0,    11,    67,     0,     0,     0,    12,
      73,     0,     0,     0,     0,     0,    17,    79,     0,    87,
       0,     0,     0,    18,    85,     0,    19,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,     0,     0,    34,    94,     0,     0,   102,     0,
       0,    37,    99,     0,     0,     0,     0,     0,    39,   104,
       1,     3,     0,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,    66,     0,     0,     0,    72,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,    84,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,     0,
       0,    98,     0,     0,     0,     0,     0,   103,    43,    49,
      44,    45,    46,    47,    48,     6,    52,    53,    61,    62,
      63,    56,    57,    55,    54,    58,    59,    60,    64,    65,
       0,     0,    10,    69,    68,    70,    71,    77,    74,    75,
      76,    14,    15,    80,    81,    82,    83,    16,    88,    86,
      89,    92,    20,     0,     0,     0,     0,     0,    25,     0,
       0,     0,     0,     0,     0,    95,    96,     0,     0,   100,
     101,    38,   116,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   117,   118,     0,     0,     0,     0,
       0,     0,    27,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     9,    21,    22,
      23,    24,    28,    29,    30,    31,    32,    33,    35,    36
  };

  const short
  Parser::yypgoto_[] =
  {
     -28,   -28,   -28,   171,   -28,   244,   -28,   235,   -28,   242,
     -28,   239,   -28,   240,   -28,   243,   -28,   241,   -28,    61,
     -28,   184,   -28,    69
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,    28,    29,    30,    35,    36,    46,    47,    54,    55,
      59,    60,    66,    67,    73,    74,    76,    77,    94,    95,
     101,   102,   108,   109
  };

  const short
  Parser::yytable_[] =
  {
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    98,    85,    99,
     104,    87,    37,   105,    69,    70,    71,   106,    79,    75,
      91,    86,    92,   100,    88,   107,    48,    50,    72,    49,
      80,    93,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,    38,    39,    40,    41,    42,    43,    44,
      45,    51,   183,   184,    52,    53,    31,    32,    33,    34,
      56,    81,    57,    58,    82,    89,   205,   206,    90,    63,
      64,    65,   180,   181,   182,   188,   189,   190,    61,   191,
     192,   193,    83,    62,    84,   195,   196,   197,    96,    78,
      97,   209,   210,   214,   215,    68,   103,   110,   112,   113,
     114,   115,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   127,   128,   129,   130,   131,   132,   134,   135,   136,
     138,   139,   140,   141,   142,   144,   145,   146,   147,   149,
     151,   152,   153,   154,   155,   166,   157,   158,   156,   159,
     160,   161,   162,   163,   198,   164,   165,   167,   168,   169,
     170,   172,   173,   174,   175,   176,   203,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
       0,     0,     0,     0,     0,     0,     0,   227,     0,     0,
     111,     0,     0,     0,     0,   179,   185,     0,   187,   186,
     194,   256,   200,   199,   201,   202,   204,   207,   208,   211,
     212,   213,   216,   272,   217,   219,   218,   220,   221,   222,
     223,   224,   225,   257,   226,   228,   229,   230,   231,   232,
     233,   258,   234,   235,   240,   236,   237,   238,   239,   241,
     242,   259,   254,   255,   261,   260,   262,   263,   264,   266,
     265,   267,   273,   269,   270,   268,   271,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   116,
       0,   126,   286,   290,   287,   171,     0,     0,     0,     0,
     288,     0,   289,   291,   292,   293,   133,     0,   137,     0,
       0,     0,     0,     0,     0,     0,   143,     0,   294,   295,
       0,   296,   297,     0,   298,   299,   148,   150
  };

  const signed char
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    48,    50,    50,
      50,    50,    50,    53,    48,    49,    50,    57,    50,    66,
      48,    63,    50,    64,    63,    65,    50,    57,    62,    53,
      62,    59,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    49,    50,    51,    52,    53,    54,    55,
      56,    54,    70,    71,    57,    58,    49,    50,    51,    52,
      57,    50,    59,    60,    53,    50,    34,    35,    53,    59,
      60,    61,    67,    68,    69,    67,    68,    69,    53,    70,
      71,    72,    48,    53,    50,    73,    74,    75,    59,    50,
      61,    77,    78,    77,    78,    59,    50,     0,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    94,    47,    47,    50,    47,
      47,    47,    47,    47,    30,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    30,   108,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    76,    76,    -1,    76,    78,
      77,    53,    76,    78,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    47,    77,    76,    78,    76,    76,    76,
      76,    76,    76,    50,    77,    76,    76,    76,    76,    76,
      76,    62,    77,    76,    78,    77,    77,    77,    76,    76,
      76,    50,    77,    76,    50,    53,    76,    48,    63,    63,
      50,    50,    47,    50,    61,    53,    59,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    35,
      -1,    46,    77,    77,    76,   101,    -1,    -1,    -1,    -1,
      76,    -1,    76,    76,    76,    76,    54,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    76,    76,
      -1,    77,    76,    -1,    77,    77,    73,    76
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    80,    81,
      82,    49,    50,    51,    52,    83,    84,    50,    49,    50,
      51,    52,    53,    54,    55,    56,    85,    86,    50,    53,
      57,    54,    57,    58,    87,    88,    57,    59,    60,    89,
      90,    53,    53,    59,    60,    61,    91,    92,    59,    48,
      49,    50,    62,    93,    94,    66,    95,    96,    50,    50,
      62,    50,    53,    48,    50,    50,    63,    50,    63,    50,
      53,    48,    50,    59,    97,    98,    59,    61,    48,    50,
      64,    99,   100,    50,    50,    53,    57,    65,   101,   102,
       0,    82,    47,    47,    47,    47,    84,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    86,    47,    47,    47,
      47,    47,    47,    88,    47,    47,    47,    90,    47,    47,
      47,    47,    47,    92,    47,    47,    47,    47,    94,    47,
      96,    47,    47,    47,    47,    47,    50,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    98,    47,    47,    47,
      47,   100,    47,    47,    47,    47,    47,   102,    78,    76,
      67,    68,    69,    70,    71,    76,    78,    76,    67,    68,
      69,    70,    71,    72,    77,    73,    74,    75,    30,    78,
      76,    77,    77,    30,    77,    34,    35,    77,    77,    77,
      78,    77,    77,    77,    77,    78,    77,    77,    78,    76,
      76,    76,    76,    76,    76,    76,    77,    47,    76,    76,
      76,    76,    76,    76,    77,    76,    77,    77,    77,    76,
      78,    76,    76,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    77,    76,    53,    50,    62,    50,
      53,    50,    76,    48,    63,    50,    63,    50,    53,    50,
      61,    59,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    77,    76,    76,    76,
      77,    76,    76,    76,    76,    76,    77,    76,    77,    77
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    79,    80,    81,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    88,    88,
      88,    88,    89,    89,    90,    90,    90,    90,    91,    91,
      92,    92,    92,    92,    93,    93,    94,    94,    94,    94,
      95,    95,    96,    97,    97,    98,    98,    98,    99,    99,
     100,   100,   100,   101,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     4,     2,     7,     7,
       4,     2,     2,     1,     4,     4,     4,     2,     2,     2,
       4,     7,     7,     7,     7,     4,     5,     5,     7,     7,
       7,     7,     7,     7,     2,     7,     7,     2,     4,     2,
       1,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     3,     3,
       3,     3,     2,     1,     3,     3,     3,     3,     2,     1,
       3,     3,     3,     3,     2,     1,     3,     1,     3,     3,
       2,     1,     3,     2,     1,     3,     3,     1,     2,     1,
       3,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3
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
  "\"full\"", "\"BestFit\"", "\"FirstFit\"", "\"WorstFit\"", "\"2fs\"",
  "\"3fs\"", "\"mbr\"", "\"disk\"", "\"inode\"", "\"journaling\"",
  "\"block\"", "\"bm_inode\"", "\"bm_block\"", "\"tree\"", "\"sb\"",
  "\"file\"", "\"ls\"", "\"=\"", "\">r\"", "\">size\"", "\">path\"",
  "\">fit\"", "\">UNIT\"", "\">name\"", "\">type\"", "\">delete\"",
  "\">add\"", "\">id\"", "\">fs\"", "\">user\"", "\">pass\"", "\">grp\"",
  "\">cont\"", "\">destino\"", "\">ugo\"", "\">ruta\"", "\"FILEN\"",
  "\"BF\"", "\"FF\"", "\"WF\"", "\"K\"", "\"M\"", "\"B\"", "\"P\"",
  "\"E\"", "\"L\"", "\"RUTA\"", "\"CADENA\"", "\"NUM\"", "$accept",
  "Inicio", "Lista", "COMANDO", "Lista_parametrosmkdisk", "parametromk",
  "Lista_fdisk", "parametrofdisk", "Lista_mkfs", "param_mkfs",
  "Lista_login", "param_login", "Lista_mkusr", "param_mkusr",
  "Lista_mkfile", "param_mkfile", "Lista_cat", "param_cat", "Lista_chown",
  "param_chown", "Lista_chmod", "param_chmod", "Lista_rep", "param_rep", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,    44,    44,    49,    50,    54,    67,    72,    76,    82,
      88,    93,    97,   101,   105,   110,   115,   120,   124,   128,
     132,   137,   143,   149,   155,   161,   166,   172,   178,   184,
     190,   196,   202,   208,   214,   218,   224,   230,   234,   239,
     243,   251,   252,   256,   261,   266,   271,   276,   281,   286,
     294,   295,   299,   303,   307,   311,   315,   319,   323,   327,
     331,   335,   339,   343,   347,   351,   358,   359,   363,   367,
     371,   375,   382,   383,   387,   391,   395,   399,   406,   407,
     411,   415,   419,   423,   430,   431,   435,   439,   443,   447,
     454,   455,   459,   467,   468,   472,   476,   480,   487,   488,
     492,   496,   500,   507,   508,   512,   516,   520,   524,   528,
     532,   536,   540,   544,   548,   552,   556,   560,   564
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
#line 2479 "parser.tab.cc"

#line 570 "parser.yy"


void yy::Parser::error( const std::string& error){
  std::cout << "XXXXXXXXXXXX ERROR EN EL COMANDO XXXXXXXXXXXXX" << std::endl;
}
