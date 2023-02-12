// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 14 "parser.yy"

   class Driver;

#line 53 "parser.tab.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 188 "parser.tab.hh"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "NUM"
      char dummy1[sizeof (float)];

      // "mkdisk"
      // "rmdisk"
      // "fdisk"
      // "mount"
      // "unmount"
      // "mkfs"
      // "login"
      // "logout"
      // "mkgrp"
      // "rmgrp"
      // "mkusr"
      // "rmusr"
      // "mkfile"
      // "cat"
      // "remove"
      // "edit"
      // "rename"
      // "mkdir"
      // "copy"
      // "move"
      // "find"
      // "chown"
      // "chgrp"
      // "chmod"
      // "pause"
      // "execute"
      // "rep"
      // "full"
      // "BestFit"
      // "FirstFit"
      // "WorstFit"
      // "2fs"
      // "3fs"
      // "mbr"
      // "disk"
      // "inode"
      // "journaling"
      // "block"
      // "bm_inode"
      // "bm_block"
      // "tree"
      // "sb"
      // "file"
      // "ls"
      // "="
      // ">r"
      // ">size"
      // ">path"
      // ">fit"
      // ">UNIT"
      // ">name"
      // ">type"
      // ">delete"
      // ">add"
      // ">id"
      // ">fs"
      // ">user"
      // ">pass"
      // ">grp"
      // ">cont"
      // ">destino"
      // ">ugo"
      // ">ruta"
      // "FILEN"
      // "BF"
      // "FF"
      // "WF"
      // "K"
      // "M"
      // "B"
      // "P"
      // "E"
      // "L"
      // "RUTA"
      // "CADENA"
      char dummy2[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    FIN = 0,                       // "eof"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    MKDISK = 258,                  // "mkdisk"
    RMDISK = 259,                  // "rmdisk"
    FDISK = 260,                   // "fdisk"
    MOUNT = 261,                   // "mount"
    UNMOUNT = 262,                 // "unmount"
    MKFS = 263,                    // "mkfs"
    LOGIN = 264,                   // "login"
    LOGOUT = 265,                  // "logout"
    MKGRP = 266,                   // "mkgrp"
    RMGRP = 267,                   // "rmgrp"
    MKUSR = 268,                   // "mkusr"
    RMUSR = 269,                   // "rmusr"
    MKFILE = 270,                  // "mkfile"
    CAT = 271,                     // "cat"
    REMOVE = 272,                  // "remove"
    EDIT = 273,                    // "edit"
    RENAME = 274,                  // "rename"
    MKDIR = 275,                   // "mkdir"
    COPY = 276,                    // "copy"
    MOVE = 277,                    // "move"
    FIND = 278,                    // "find"
    CHOWN = 279,                   // "chown"
    CHGRP = 280,                   // "chgrp"
    CHMOD = 281,                   // "chmod"
    PAUSE = 282,                   // "pause"
    EXECUTE = 283,                 // "execute"
    REP = 284,                     // "rep"
    FULL = 285,                    // "full"
    BESTFIT = 286,                 // "BestFit"
    FIRSTFIT = 287,                // "FirstFit"
    WORSTFIT = 288,                // "WorstFit"
    DOSFS = 289,                   // "2fs"
    TRESFS = 290,                  // "3fs"
    MBR = 291,                     // "mbr"
    DISK = 292,                    // "disk"
    INODE = 293,                   // "inode"
    JOURNALING = 294,              // "journaling"
    BLOCK = 295,                   // "block"
    BMINODE = 296,                 // "bm_inode"
    BMBLOCK = 297,                 // "bm_block"
    TREE = 298,                    // "tree"
    SB = 299,                      // "sb"
    FILE = 300,                    // "file"
    LS = 301,                      // "ls"
    IGUAL = 302,                   // "="
    R = 303,                       // ">r"
    SIZE = 304,                    // ">size"
    PATH = 305,                    // ">path"
    FIT = 306,                     // ">fit"
    UNIT = 307,                    // ">UNIT"
    NAME = 308,                    // ">name"
    TYPE = 309,                    // ">type"
    DELETE = 310,                  // ">delete"
    ADD = 311,                     // ">add"
    ID = 312,                      // ">id"
    FS = 313,                      // ">fs"
    USER = 314,                    // ">user"
    PASS = 315,                    // ">pass"
    GRP = 316,                     // ">grp"
    CONT = 317,                    // ">cont"
    DESTINO = 318,                 // ">destino"
    UGO = 319,                     // ">ugo"
    COMRUTA = 320,                 // ">ruta"
    FILEN = 321,                   // "FILEN"
    BF = 322,                      // "BF"
    FF = 323,                      // "FF"
    WF = 324,                      // "WF"
    K = 325,                       // "K"
    M = 326,                       // "M"
    B = 327,                       // "B"
    P = 328,                       // "P"
    E = 329,                       // "E"
    L = 330,                       // "L"
    RUTA = 331,                    // "RUTA"
    CADENA = 332,                  // "CADENA"
    NUM = 333                      // "NUM"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 79, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "eof"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_MKDISK = 3,                            // "mkdisk"
        S_RMDISK = 4,                            // "rmdisk"
        S_FDISK = 5,                             // "fdisk"
        S_MOUNT = 6,                             // "mount"
        S_UNMOUNT = 7,                           // "unmount"
        S_MKFS = 8,                              // "mkfs"
        S_LOGIN = 9,                             // "login"
        S_LOGOUT = 10,                           // "logout"
        S_MKGRP = 11,                            // "mkgrp"
        S_RMGRP = 12,                            // "rmgrp"
        S_MKUSR = 13,                            // "mkusr"
        S_RMUSR = 14,                            // "rmusr"
        S_MKFILE = 15,                           // "mkfile"
        S_CAT = 16,                              // "cat"
        S_REMOVE = 17,                           // "remove"
        S_EDIT = 18,                             // "edit"
        S_RENAME = 19,                           // "rename"
        S_MKDIR = 20,                            // "mkdir"
        S_COPY = 21,                             // "copy"
        S_MOVE = 22,                             // "move"
        S_FIND = 23,                             // "find"
        S_CHOWN = 24,                            // "chown"
        S_CHGRP = 25,                            // "chgrp"
        S_CHMOD = 26,                            // "chmod"
        S_PAUSE = 27,                            // "pause"
        S_EXECUTE = 28,                          // "execute"
        S_REP = 29,                              // "rep"
        S_FULL = 30,                             // "full"
        S_BESTFIT = 31,                          // "BestFit"
        S_FIRSTFIT = 32,                         // "FirstFit"
        S_WORSTFIT = 33,                         // "WorstFit"
        S_DOSFS = 34,                            // "2fs"
        S_TRESFS = 35,                           // "3fs"
        S_MBR = 36,                              // "mbr"
        S_DISK = 37,                             // "disk"
        S_INODE = 38,                            // "inode"
        S_JOURNALING = 39,                       // "journaling"
        S_BLOCK = 40,                            // "block"
        S_BMINODE = 41,                          // "bm_inode"
        S_BMBLOCK = 42,                          // "bm_block"
        S_TREE = 43,                             // "tree"
        S_SB = 44,                               // "sb"
        S_FILE = 45,                             // "file"
        S_LS = 46,                               // "ls"
        S_IGUAL = 47,                            // "="
        S_R = 48,                                // ">r"
        S_SIZE = 49,                             // ">size"
        S_PATH = 50,                             // ">path"
        S_FIT = 51,                              // ">fit"
        S_UNIT = 52,                             // ">UNIT"
        S_NAME = 53,                             // ">name"
        S_TYPE = 54,                             // ">type"
        S_DELETE = 55,                           // ">delete"
        S_ADD = 56,                              // ">add"
        S_ID = 57,                               // ">id"
        S_FS = 58,                               // ">fs"
        S_USER = 59,                             // ">user"
        S_PASS = 60,                             // ">pass"
        S_GRP = 61,                              // ">grp"
        S_CONT = 62,                             // ">cont"
        S_DESTINO = 63,                          // ">destino"
        S_UGO = 64,                              // ">ugo"
        S_COMRUTA = 65,                          // ">ruta"
        S_FILEN = 66,                            // "FILEN"
        S_BF = 67,                               // "BF"
        S_FF = 68,                               // "FF"
        S_WF = 69,                               // "WF"
        S_K = 70,                                // "K"
        S_M = 71,                                // "M"
        S_B = 72,                                // "B"
        S_P = 73,                                // "P"
        S_E = 74,                                // "E"
        S_L = 75,                                // "L"
        S_RUTA = 76,                             // "RUTA"
        S_CADENA = 77,                           // "CADENA"
        S_NUM = 78,                              // "NUM"
        S_YYACCEPT = 79,                         // $accept
        S_Inicio = 80,                           // Inicio
        S_Lista = 81,                            // Lista
        S_COMANDO = 82,                          // COMANDO
        S_Lista_parametrosmkdisk = 83,           // Lista_parametrosmkdisk
        S_parametromk = 84,                      // parametromk
        S_Lista_fdisk = 85,                      // Lista_fdisk
        S_parametrofdisk = 86,                   // parametrofdisk
        S_Lista_mkfs = 87,                       // Lista_mkfs
        S_param_mkfs = 88,                       // param_mkfs
        S_Lista_login = 89,                      // Lista_login
        S_param_login = 90,                      // param_login
        S_Lista_mkusr = 91,                      // Lista_mkusr
        S_param_mkusr = 92,                      // param_mkusr
        S_Lista_mkfile = 93,                     // Lista_mkfile
        S_param_mkfile = 94,                     // param_mkfile
        S_Lista_cat = 95,                        // Lista_cat
        S_param_cat = 96,                        // param_cat
        S_Lista_chown = 97,                      // Lista_chown
        S_param_chown = 98,                      // param_chown
        S_Lista_chmod = 99,                      // Lista_chmod
        S_param_chmod = 100,                     // param_chmod
        S_Lista_rep = 101,                       // Lista_rep
        S_param_rep = 102                        // param_rep
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_NUM: // "NUM"
        value.move< float > (std::move (that.value));
        break;

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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_NUM: // "NUM"
        value.template destroy< float > ();
        break;

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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const float& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    Parser (Driver& driver_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FIN ()
      {
        return symbol_type (token::FIN);
      }
#else
      static
      symbol_type
      make_FIN ()
      {
        return symbol_type (token::FIN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKDISK (std::string v)
      {
        return symbol_type (token::MKDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_MKDISK (const std::string& v)
      {
        return symbol_type (token::MKDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RMDISK (std::string v)
      {
        return symbol_type (token::RMDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_RMDISK (const std::string& v)
      {
        return symbol_type (token::RMDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FDISK (std::string v)
      {
        return symbol_type (token::FDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_FDISK (const std::string& v)
      {
        return symbol_type (token::FDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOUNT (std::string v)
      {
        return symbol_type (token::MOUNT, std::move (v));
      }
#else
      static
      symbol_type
      make_MOUNT (const std::string& v)
      {
        return symbol_type (token::MOUNT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNMOUNT (std::string v)
      {
        return symbol_type (token::UNMOUNT, std::move (v));
      }
#else
      static
      symbol_type
      make_UNMOUNT (const std::string& v)
      {
        return symbol_type (token::UNMOUNT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKFS (std::string v)
      {
        return symbol_type (token::MKFS, std::move (v));
      }
#else
      static
      symbol_type
      make_MKFS (const std::string& v)
      {
        return symbol_type (token::MKFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIN (std::string v)
      {
        return symbol_type (token::LOGIN, std::move (v));
      }
#else
      static
      symbol_type
      make_LOGIN (const std::string& v)
      {
        return symbol_type (token::LOGIN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGOUT (std::string v)
      {
        return symbol_type (token::LOGOUT, std::move (v));
      }
#else
      static
      symbol_type
      make_LOGOUT (const std::string& v)
      {
        return symbol_type (token::LOGOUT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKGRP (std::string v)
      {
        return symbol_type (token::MKGRP, std::move (v));
      }
#else
      static
      symbol_type
      make_MKGRP (const std::string& v)
      {
        return symbol_type (token::MKGRP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RMGRP (std::string v)
      {
        return symbol_type (token::RMGRP, std::move (v));
      }
#else
      static
      symbol_type
      make_RMGRP (const std::string& v)
      {
        return symbol_type (token::RMGRP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKUSR (std::string v)
      {
        return symbol_type (token::MKUSR, std::move (v));
      }
#else
      static
      symbol_type
      make_MKUSR (const std::string& v)
      {
        return symbol_type (token::MKUSR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RMUSR (std::string v)
      {
        return symbol_type (token::RMUSR, std::move (v));
      }
#else
      static
      symbol_type
      make_RMUSR (const std::string& v)
      {
        return symbol_type (token::RMUSR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKFILE (std::string v)
      {
        return symbol_type (token::MKFILE, std::move (v));
      }
#else
      static
      symbol_type
      make_MKFILE (const std::string& v)
      {
        return symbol_type (token::MKFILE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CAT (std::string v)
      {
        return symbol_type (token::CAT, std::move (v));
      }
#else
      static
      symbol_type
      make_CAT (const std::string& v)
      {
        return symbol_type (token::CAT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REMOVE (std::string v)
      {
        return symbol_type (token::REMOVE, std::move (v));
      }
#else
      static
      symbol_type
      make_REMOVE (const std::string& v)
      {
        return symbol_type (token::REMOVE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EDIT (std::string v)
      {
        return symbol_type (token::EDIT, std::move (v));
      }
#else
      static
      symbol_type
      make_EDIT (const std::string& v)
      {
        return symbol_type (token::EDIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RENAME (std::string v)
      {
        return symbol_type (token::RENAME, std::move (v));
      }
#else
      static
      symbol_type
      make_RENAME (const std::string& v)
      {
        return symbol_type (token::RENAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKDIR (std::string v)
      {
        return symbol_type (token::MKDIR, std::move (v));
      }
#else
      static
      symbol_type
      make_MKDIR (const std::string& v)
      {
        return symbol_type (token::MKDIR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COPY (std::string v)
      {
        return symbol_type (token::COPY, std::move (v));
      }
#else
      static
      symbol_type
      make_COPY (const std::string& v)
      {
        return symbol_type (token::COPY, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOVE (std::string v)
      {
        return symbol_type (token::MOVE, std::move (v));
      }
#else
      static
      symbol_type
      make_MOVE (const std::string& v)
      {
        return symbol_type (token::MOVE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FIND (std::string v)
      {
        return symbol_type (token::FIND, std::move (v));
      }
#else
      static
      symbol_type
      make_FIND (const std::string& v)
      {
        return symbol_type (token::FIND, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHOWN (std::string v)
      {
        return symbol_type (token::CHOWN, std::move (v));
      }
#else
      static
      symbol_type
      make_CHOWN (const std::string& v)
      {
        return symbol_type (token::CHOWN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHGRP (std::string v)
      {
        return symbol_type (token::CHGRP, std::move (v));
      }
#else
      static
      symbol_type
      make_CHGRP (const std::string& v)
      {
        return symbol_type (token::CHGRP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHMOD (std::string v)
      {
        return symbol_type (token::CHMOD, std::move (v));
      }
#else
      static
      symbol_type
      make_CHMOD (const std::string& v)
      {
        return symbol_type (token::CHMOD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PAUSE (std::string v)
      {
        return symbol_type (token::PAUSE, std::move (v));
      }
#else
      static
      symbol_type
      make_PAUSE (const std::string& v)
      {
        return symbol_type (token::PAUSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXECUTE (std::string v)
      {
        return symbol_type (token::EXECUTE, std::move (v));
      }
#else
      static
      symbol_type
      make_EXECUTE (const std::string& v)
      {
        return symbol_type (token::EXECUTE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REP (std::string v)
      {
        return symbol_type (token::REP, std::move (v));
      }
#else
      static
      symbol_type
      make_REP (const std::string& v)
      {
        return symbol_type (token::REP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FULL (std::string v)
      {
        return symbol_type (token::FULL, std::move (v));
      }
#else
      static
      symbol_type
      make_FULL (const std::string& v)
      {
        return symbol_type (token::FULL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BESTFIT (std::string v)
      {
        return symbol_type (token::BESTFIT, std::move (v));
      }
#else
      static
      symbol_type
      make_BESTFIT (const std::string& v)
      {
        return symbol_type (token::BESTFIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FIRSTFIT (std::string v)
      {
        return symbol_type (token::FIRSTFIT, std::move (v));
      }
#else
      static
      symbol_type
      make_FIRSTFIT (const std::string& v)
      {
        return symbol_type (token::FIRSTFIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WORSTFIT (std::string v)
      {
        return symbol_type (token::WORSTFIT, std::move (v));
      }
#else
      static
      symbol_type
      make_WORSTFIT (const std::string& v)
      {
        return symbol_type (token::WORSTFIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOSFS (std::string v)
      {
        return symbol_type (token::DOSFS, std::move (v));
      }
#else
      static
      symbol_type
      make_DOSFS (const std::string& v)
      {
        return symbol_type (token::DOSFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRESFS (std::string v)
      {
        return symbol_type (token::TRESFS, std::move (v));
      }
#else
      static
      symbol_type
      make_TRESFS (const std::string& v)
      {
        return symbol_type (token::TRESFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MBR (std::string v)
      {
        return symbol_type (token::MBR, std::move (v));
      }
#else
      static
      symbol_type
      make_MBR (const std::string& v)
      {
        return symbol_type (token::MBR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DISK (std::string v)
      {
        return symbol_type (token::DISK, std::move (v));
      }
#else
      static
      symbol_type
      make_DISK (const std::string& v)
      {
        return symbol_type (token::DISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INODE (std::string v)
      {
        return symbol_type (token::INODE, std::move (v));
      }
#else
      static
      symbol_type
      make_INODE (const std::string& v)
      {
        return symbol_type (token::INODE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_JOURNALING (std::string v)
      {
        return symbol_type (token::JOURNALING, std::move (v));
      }
#else
      static
      symbol_type
      make_JOURNALING (const std::string& v)
      {
        return symbol_type (token::JOURNALING, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BLOCK (std::string v)
      {
        return symbol_type (token::BLOCK, std::move (v));
      }
#else
      static
      symbol_type
      make_BLOCK (const std::string& v)
      {
        return symbol_type (token::BLOCK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BMINODE (std::string v)
      {
        return symbol_type (token::BMINODE, std::move (v));
      }
#else
      static
      symbol_type
      make_BMINODE (const std::string& v)
      {
        return symbol_type (token::BMINODE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BMBLOCK (std::string v)
      {
        return symbol_type (token::BMBLOCK, std::move (v));
      }
#else
      static
      symbol_type
      make_BMBLOCK (const std::string& v)
      {
        return symbol_type (token::BMBLOCK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TREE (std::string v)
      {
        return symbol_type (token::TREE, std::move (v));
      }
#else
      static
      symbol_type
      make_TREE (const std::string& v)
      {
        return symbol_type (token::TREE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SB (std::string v)
      {
        return symbol_type (token::SB, std::move (v));
      }
#else
      static
      symbol_type
      make_SB (const std::string& v)
      {
        return symbol_type (token::SB, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FILE (std::string v)
      {
        return symbol_type (token::FILE, std::move (v));
      }
#else
      static
      symbol_type
      make_FILE (const std::string& v)
      {
        return symbol_type (token::FILE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LS (std::string v)
      {
        return symbol_type (token::LS, std::move (v));
      }
#else
      static
      symbol_type
      make_LS (const std::string& v)
      {
        return symbol_type (token::LS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IGUAL (std::string v)
      {
        return symbol_type (token::IGUAL, std::move (v));
      }
#else
      static
      symbol_type
      make_IGUAL (const std::string& v)
      {
        return symbol_type (token::IGUAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_R (std::string v)
      {
        return symbol_type (token::R, std::move (v));
      }
#else
      static
      symbol_type
      make_R (const std::string& v)
      {
        return symbol_type (token::R, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZE (std::string v)
      {
        return symbol_type (token::SIZE, std::move (v));
      }
#else
      static
      symbol_type
      make_SIZE (const std::string& v)
      {
        return symbol_type (token::SIZE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PATH (std::string v)
      {
        return symbol_type (token::PATH, std::move (v));
      }
#else
      static
      symbol_type
      make_PATH (const std::string& v)
      {
        return symbol_type (token::PATH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FIT (std::string v)
      {
        return symbol_type (token::FIT, std::move (v));
      }
#else
      static
      symbol_type
      make_FIT (const std::string& v)
      {
        return symbol_type (token::FIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNIT (std::string v)
      {
        return symbol_type (token::UNIT, std::move (v));
      }
#else
      static
      symbol_type
      make_UNIT (const std::string& v)
      {
        return symbol_type (token::UNIT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (std::string v)
      {
        return symbol_type (token::NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_NAME (const std::string& v)
      {
        return symbol_type (token::NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (std::string v)
      {
        return symbol_type (token::TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_TYPE (const std::string& v)
      {
        return symbol_type (token::TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DELETE (std::string v)
      {
        return symbol_type (token::DELETE, std::move (v));
      }
#else
      static
      symbol_type
      make_DELETE (const std::string& v)
      {
        return symbol_type (token::DELETE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD (std::string v)
      {
        return symbol_type (token::ADD, std::move (v));
      }
#else
      static
      symbol_type
      make_ADD (const std::string& v)
      {
        return symbol_type (token::ADD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (std::string v)
      {
        return symbol_type (token::ID, std::move (v));
      }
#else
      static
      symbol_type
      make_ID (const std::string& v)
      {
        return symbol_type (token::ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FS (std::string v)
      {
        return symbol_type (token::FS, std::move (v));
      }
#else
      static
      symbol_type
      make_FS (const std::string& v)
      {
        return symbol_type (token::FS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER (std::string v)
      {
        return symbol_type (token::USER, std::move (v));
      }
#else
      static
      symbol_type
      make_USER (const std::string& v)
      {
        return symbol_type (token::USER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PASS (std::string v)
      {
        return symbol_type (token::PASS, std::move (v));
      }
#else
      static
      symbol_type
      make_PASS (const std::string& v)
      {
        return symbol_type (token::PASS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GRP (std::string v)
      {
        return symbol_type (token::GRP, std::move (v));
      }
#else
      static
      symbol_type
      make_GRP (const std::string& v)
      {
        return symbol_type (token::GRP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONT (std::string v)
      {
        return symbol_type (token::CONT, std::move (v));
      }
#else
      static
      symbol_type
      make_CONT (const std::string& v)
      {
        return symbol_type (token::CONT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DESTINO (std::string v)
      {
        return symbol_type (token::DESTINO, std::move (v));
      }
#else
      static
      symbol_type
      make_DESTINO (const std::string& v)
      {
        return symbol_type (token::DESTINO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UGO (std::string v)
      {
        return symbol_type (token::UGO, std::move (v));
      }
#else
      static
      symbol_type
      make_UGO (const std::string& v)
      {
        return symbol_type (token::UGO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMRUTA (std::string v)
      {
        return symbol_type (token::COMRUTA, std::move (v));
      }
#else
      static
      symbol_type
      make_COMRUTA (const std::string& v)
      {
        return symbol_type (token::COMRUTA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FILEN (std::string v)
      {
        return symbol_type (token::FILEN, std::move (v));
      }
#else
      static
      symbol_type
      make_FILEN (const std::string& v)
      {
        return symbol_type (token::FILEN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BF (std::string v)
      {
        return symbol_type (token::BF, std::move (v));
      }
#else
      static
      symbol_type
      make_BF (const std::string& v)
      {
        return symbol_type (token::BF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FF (std::string v)
      {
        return symbol_type (token::FF, std::move (v));
      }
#else
      static
      symbol_type
      make_FF (const std::string& v)
      {
        return symbol_type (token::FF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WF (std::string v)
      {
        return symbol_type (token::WF, std::move (v));
      }
#else
      static
      symbol_type
      make_WF (const std::string& v)
      {
        return symbol_type (token::WF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_K (std::string v)
      {
        return symbol_type (token::K, std::move (v));
      }
#else
      static
      symbol_type
      make_K (const std::string& v)
      {
        return symbol_type (token::K, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_M (std::string v)
      {
        return symbol_type (token::M, std::move (v));
      }
#else
      static
      symbol_type
      make_M (const std::string& v)
      {
        return symbol_type (token::M, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_B (std::string v)
      {
        return symbol_type (token::B, std::move (v));
      }
#else
      static
      symbol_type
      make_B (const std::string& v)
      {
        return symbol_type (token::B, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_P (std::string v)
      {
        return symbol_type (token::P, std::move (v));
      }
#else
      static
      symbol_type
      make_P (const std::string& v)
      {
        return symbol_type (token::P, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_E (std::string v)
      {
        return symbol_type (token::E, std::move (v));
      }
#else
      static
      symbol_type
      make_E (const std::string& v)
      {
        return symbol_type (token::E, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_L (std::string v)
      {
        return symbol_type (token::L, std::move (v));
      }
#else
      static
      symbol_type
      make_L (const std::string& v)
      {
        return symbol_type (token::L, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RUTA (std::string v)
      {
        return symbol_type (token::RUTA, std::move (v));
      }
#else
      static
      symbol_type
      make_RUTA (const std::string& v)
      {
        return symbol_type (token::RUTA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CADENA (std::string v)
      {
        return symbol_type (token::CADENA, std::move (v));
      }
#else
      static
      symbol_type
      make_CADENA (const std::string& v)
      {
        return symbol_type (token::CADENA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUM (float v)
      {
        return symbol_type (token::NUM, std::move (v));
      }
#else
      static
      symbol_type
      make_NUM (const float& v)
      {
        return symbol_type (token::NUM, v);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 317,     ///< Last index in yytable_.
      yynnts_ = 24,  ///< Number of nonterminal symbols.
      yyfinal_ = 110 ///< Termination state number.
    };


    // User arguments.
    Driver& driver;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
    };
    // Last valid token kind.
    const int code_max = 333;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_NUM: // "NUM"
        value.copy< float > (YY_MOVE (that.value));
        break;

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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_NUM: // "NUM"
        value.move< float > (YY_MOVE (s.value));
        break;

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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2974 "parser.tab.hh"




#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
