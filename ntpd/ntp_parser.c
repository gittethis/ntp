/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

   /* As a special exception, you may create a larger work that contains
      part or all of the Bison parser skeleton and distribute that work
      under terms of your choice, so long as that work isn't itself a
      parser generator using the skeleton or a modified version thereof
      as a parser skeleton.  Alternatively, if you modify or redistribute
      the parser skeleton itself, you may (at your option) remove this
      special exception, which will cause the skeleton and the resulting
      Bison output files to be licensed under the GNU General Public
      License without this special exception.

      This special exception was added by the Free Software Foundation in
      version 2.2 of Bison.  */

      /* C LALR(1) parser skeleton written by Richard Stallman, by
         simplifying the original so-called "semantic" parser.  */

         /* All symbols defined below should begin with yy or YY, to avoid
            infringing on user name space.  This should be done even for local
            variables, as they might otherwise be expanded by user macros.
            There are some unavoidable exceptions within include files to
            define necessary library symbols; they are noted "INFRINGES ON
            USER NAME SPACE" below.  */

            /* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 11 "ntp_parser.y" /* yacc.c:339  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ntp.h"
#include "ntpd.h"
#include "ntp_machine.h"
#include "ntp_stdlib.h"
#include "ntp_filegen.h"
#include "ntp_scanner.h"
#include "ntp_config.h"
#include "ntp_crypto.h"
#include "ntp_calendar.h"

#include "ntpsim.h"		/* HMS: Do we really want this all the time? */
              /* SK: It might be a good idea to always
                 include the simulator code. That way
                 someone can use the same configuration file
                 for both the simulator and the daemon
              */

#define YYMALLOC	emalloc
#define YYFREE	free
#define YYERROR_VERBOSE
#define YYMAXDEPTH	1000	/* stop the madness sooner */
void yyerror(const char* msg);

#ifdef SIM
#  define ONLY_SIM(a)	(a)
#else
#  define ONLY_SIM(a)	NULL
#endif

#line 101 "ntp_parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ntp_parser.h".  */
#ifndef YY_YY_NTP_PARSER_H_INCLUDED
# define YY_YY_NTP_PARSER_H_INCLUDED
   /* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
    T_Abbrev = 258,
    T_Age = 259,
    T_All = 260,
    T_Allan = 261,
    T_Allpeers = 262,
    T_Auth = 263,
    T_Autokey = 264,
    T_Automax = 265,
    T_Average = 266,
    T_Basedate = 267,
    T_Bclient = 268,
    T_Bcpollbstep = 269,
    T_Beacon = 270,
    T_Broadcast = 271,
    T_Broadcastclient = 272,
    T_Broadcastdelay = 273,
    T_Burst = 274,
    T_Calibrate = 275,
    T_Ceiling = 276,
    T_Checkhash = 277,
    T_Clockstats = 278,
    T_Cohort = 279,
    T_ControlKey = 280,
    T_Crypto = 281,
    T_Cryptostats = 282,
    T_Ctl = 283,
    T_Day = 284,
    T_Default = 285,
    T_Delrestrict = 286,
    T_Device = 287,
    T_Digest = 288,
    T_Disable = 289,
    T_Discard = 290,
    T_Dispersion = 291,
    T_Double = 292,
    T_Driftfile = 293,
    T_Drop = 294,
    T_Dscp = 295,
    T_Ellipsis = 296,
    T_Enable = 297,
    T_End = 298,
    T_Epeer = 299,
    T_False = 300,
    T_File = 301,
    T_Filegen = 302,
    T_Filenum = 303,
    T_Flag1 = 304,
    T_Flag2 = 305,
    T_Flag3 = 306,
    T_Flag4 = 307,
    T_Flake = 308,
    T_Floor = 309,
    T_Freq = 310,
    T_Fudge = 311,
    T_Fuzz = 312,
    T_Host = 313,
    T_Huffpuff = 314,
    T_Iburst = 315,
    T_Nts = 316,
    T_Ident = 317,
    T_Ignore = 318,
    T_Ignorehash = 319,
    T_Incalloc = 320,
    T_Incmem = 321,
    T_Initalloc = 322,
    T_Initmem = 323,
    T_Includefile = 324,
    T_Integer = 325,
    T_Interface = 326,
    T_Intrange = 327,
    T_Io = 328,
    T_Ippeerlimit = 329,
    T_Ipv4 = 330,
    T_Ipv4_flag = 331,
    T_Ipv6 = 332,
    T_Ipv6_flag = 333,
    T_Kernel = 334,
    T_Key = 335,
    T_Keys = 336,
    T_Keysdir = 337,
    T_Kod = 338,
    T_Leapfile = 339,
    T_Leapsmearinterval = 340,
    T_Limited = 341,
    T_Link = 342,
    T_Listen = 343,
    T_Logconfig = 344,
    T_Logfile = 345,
    T_Loopstats = 346,
    T_Lowpriotrap = 347,
    T_Manycastclient = 348,
    T_Manycastserver = 349,
    T_Mask = 350,
    T_Maxage = 351,
    T_Maxclock = 352,
    T_Maxdepth = 353,
    T_Maxdist = 354,
    T_Maxmem = 355,
    T_Maxpoll = 356,
    T_Mdnstries = 357,
    T_Mem = 358,
    T_Memlock = 359,
    T_Minclock = 360,
    T_Mindepth = 361,
    T_Mindist = 362,
    T_Minimum = 363,
    T_Minjitter = 364,
    T_Minpoll = 365,
    T_Minsane = 366,
    T_Mode = 367,
    T_Mode7 = 368,
    T_Monitor = 369,
    T_Month = 370,
    T_Mru = 371,
    T_Mssntp = 372,
    T_Multicastclient = 373,
    T_Nic = 374,
    T_Nolink = 375,
    T_Nomodify = 376,
    T_Nomrulist = 377,
    T_None = 378,
    T_Nonvolatile = 379,
    T_Noepeer = 380,
    T_Nopeer = 381,
    T_Noquery = 382,
    T_Noselect = 383,
    T_Noserve = 384,
    T_Notrap = 385,
    T_Notrust = 386,
    T_Ntp = 387,
    T_Ntpport = 388,
    T_NtpSignDsocket = 389,
    T_Orphan = 390,
    T_Orphanwait = 391,
    T_PCEdigest = 392,
    T_Panic = 393,
    T_Peer = 394,
    T_Peerstats = 395,
    T_Phone = 396,
    T_Pid = 397,
    T_Pidfile = 398,
    T_Poll = 399,
    T_PollSkewList = 400,
    T_Pool = 401,
    T_Port = 402,
    T_PpsData = 403,
    T_Preempt = 404,
    T_Prefer = 405,
    T_Protostats = 406,
    T_Pw = 407,
    T_Randfile = 408,
    T_Rawstats = 409,
    T_Refid = 410,
    T_Requestkey = 411,
    T_Reset = 412,
    T_Restrict = 413,
    T_Revoke = 414,
    T_Rlimit = 415,
    T_Saveconfigdir = 416,
    T_Server = 417,
    T_Serverresponse = 418,
    T_ServerresponseFuzz = 419,
    T_Setvar = 420,
    T_Source = 421,
    T_Stacksize = 422,
    T_Statistics = 423,
    T_Stats = 424,
    T_Statsdir = 425,
    T_Step = 426,
    T_Stepback = 427,
    T_Stepfwd = 428,
    T_Stepout = 429,
    T_Stratum = 430,
    T_String = 431,
    T_Sys = 432,
    T_Sysstats = 433,
    T_Tick = 434,
    T_Time1 = 435,
    T_Time2 = 436,
    T_TimeData = 437,
    T_Timer = 438,
    T_Timingstats = 439,
    T_Tinker = 440,
    T_Tos = 441,
    T_Trap = 442,
    T_True = 443,
    T_Trustedkey = 444,
    T_Ttl = 445,
    T_Type = 446,
    T_U_int = 447,
    T_UEcrypto = 448,
    T_UEcryptonak = 449,
    T_UEdigest = 450,
    T_Unconfig = 451,
    T_Unpeer = 452,
    T_Version = 453,
    T_WanderThreshold = 454,
    T_Week = 455,
    T_Wildcard = 456,
    T_Xleave = 457,
    T_Xmtnonce = 458,
    T_Year = 459,
    T_Flag = 460,
    T_EOC = 461,
    T_Simulate = 462,
    T_Beep_Delay = 463,
    T_Sim_Duration = 464,
    T_Server_Offset = 465,
    T_Duration = 466,
    T_Freq_Offset = 467,
    T_Wander = 468,
    T_Jitter = 469,
    T_Prop_Delay = 470,
    T_Proc_Delay = 471
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "ntp_parser.y" /* yacc.c:355  */

    char* String;
    double			Double;
    int			Integer;
    unsigned		U_int;
    gen_fifo* Generic_fifo;
    attr_val* Attr_val;
    attr_val_fifo* Attr_val_fifo;
    int_fifo* Int_fifo;
    string_fifo* String_fifo;
    address_node* Address_node;
    address_fifo* Address_fifo;
    setvar_node* Set_var;
    server_info* Sim_server;
    server_info_fifo* Sim_server_fifo;
    script_info* Sim_script;
    script_info_fifo* Sim_script_fifo;

#line 377 "ntp_parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_NTP_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 394 "ntp_parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void* malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free(void*); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
    yytype_int16 yyss_alloc;
    YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

   /* Relocate STACK from its old location to the new one.  The
      local variables YYSIZE and YYSTACKSIZE give the old and new number of
      elements in the stack, and YYPTR gives the new location of the
      stack.  Advance YYPTR to a properly aligned location for the next
      stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
      /* Copy COUNT objects from SRC to DST.  The source and destination do
         not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

         /* YYFINAL -- State number of the termination state.  */
#define YYFINAL  225
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   788

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  223
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  116
/* YYNRULES -- Number of rules.  */
#define YYNRULES  347
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  468

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   471

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

   /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
      as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     219,   220,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   218,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   221,   217,   222,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   400,   400,   404,   405,   406,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   443,   453,   454,   455,   456,   457,   461,   462,   467,
     472,   474,   480,   481,   489,   490,   491,   495,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   513,   515,
     520,   521,   522,   523,   524,   525,   529,   534,   543,   553,
     554,   564,   566,   568,   570,   581,   588,   590,   595,   597,
     599,   601,   603,   613,   619,   620,   628,   630,   642,   643,
     644,   645,   646,   655,   660,   665,   673,   675,   677,   679,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   696,
     697,   706,   708,   717,   727,   732,   740,   741,   742,   743,
     744,   745,   746,   747,   752,   753,   761,   771,   780,   795,
     800,   801,   805,   806,   810,   811,   812,   813,   814,   815,
     816,   825,   829,   833,   842,   851,   867,   883,   893,   902,
     918,   919,   927,   928,   948,   949,   957,   968,   969,   970,
     971,   972,   973,   974,   975,   976,   977,   978,   979,   980,
     981,   982,   983,   984,   988,   993,  1001,  1006,  1007,  1008,
    1012,  1017,  1025,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1045,  1055,  1060,  1068,  1070,  1072,  1081,  1083,  1088,
    1089,  1090,  1094,  1095,  1096,  1097,  1105,  1115,  1120,  1128,
    1133,  1134,  1142,  1147,  1152,  1160,  1165,  1166,  1167,  1176,
    1178,  1183,  1188,  1196,  1198,  1215,  1216,  1217,  1218,  1219,
    1220,  1224,  1225,  1226,  1227,  1228,  1229,  1237,  1242,  1247,
    1255,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,
    1269,  1278,  1279,  1280,  1287,  1294,  1301,  1317,  1336,  1344,
    1346,  1348,  1350,  1352,  1354,  1356,  1363,  1368,  1369,  1370,
    1374,  1378,  1387,  1389,  1392,  1396,  1400,  1401,  1402,  1406,
    1417,  1435,  1448,  1449,  1454,  1480,  1486,  1491,  1496,  1498,
    1503,  1504,  1512,  1514,  1522,  1527,  1535,  1560,  1567,  1577,
    1578,  1582,  1583,  1584,  1585,  1589,  1590,  1591,  1595,  1600,
    1605,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1629,  1634,
    1642,  1647,  1655,  1657,  1661,  1666,  1671,  1679,  1684,  1692,
    1701,  1702,  1706,  1707,  1711,  1719,  1737,  1741,  1746,  1754,
    1759,  1760,  1764,  1769,  1777,  1782,  1787,  1792,  1797,  1805,
    1810,  1815,  1823,  1828,  1829,  1830,  1831,  1832
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char* const yytname[] =
{
  "$end", "error", "$undefined", "T_Abbrev", "T_Age", "T_All", "T_Allan",
  "T_Allpeers", "T_Auth", "T_Autokey", "T_Automax", "T_Average",
  "T_Basedate", "T_Bclient", "T_Bcpollbstep", "T_Beacon", "T_Broadcast",
  "T_Broadcastclient", "T_Broadcastdelay", "T_Burst", "T_Calibrate",
  "T_Ceiling", "T_Checkhash", "T_Clockstats", "T_Cohort", "T_ControlKey",
  "T_Crypto", "T_Cryptostats", "T_Ctl", "T_Day", "T_Default",
  "T_Delrestrict", "T_Device", "T_Digest", "T_Disable", "T_Discard",
  "T_Dispersion", "T_Double", "T_Driftfile", "T_Drop", "T_Dscp",
  "T_Ellipsis", "T_Enable", "T_End", "T_Epeer", "T_False", "T_File",
  "T_Filegen", "T_Filenum", "T_Flag1", "T_Flag2", "T_Flag3", "T_Flag4",
  "T_Flake", "T_Floor", "T_Freq", "T_Fudge", "T_Fuzz", "T_Host",
  "T_Huffpuff", "T_Iburst", "T_Nts", "T_Ident", "T_Ignore", "T_Ignorehash",
  "T_Incalloc", "T_Incmem", "T_Initalloc", "T_Initmem", "T_Includefile",
  "T_Integer", "T_Interface", "T_Intrange", "T_Io", "T_Ippeerlimit",
  "T_Ipv4", "T_Ipv4_flag", "T_Ipv6", "T_Ipv6_flag", "T_Kernel", "T_Key",
  "T_Keys", "T_Keysdir", "T_Kod", "T_Leapfile", "T_Leapsmearinterval",
  "T_Limited", "T_Link", "T_Listen", "T_Logconfig", "T_Logfile",
  "T_Loopstats", "T_Lowpriotrap", "T_Manycastclient", "T_Manycastserver",
  "T_Mask", "T_Maxage", "T_Maxclock", "T_Maxdepth", "T_Maxdist",
  "T_Maxmem", "T_Maxpoll", "T_Mdnstries", "T_Mem", "T_Memlock",
  "T_Minclock", "T_Mindepth", "T_Mindist", "T_Minimum", "T_Minjitter",
  "T_Minpoll", "T_Minsane", "T_Mode", "T_Mode7", "T_Monitor", "T_Month",
  "T_Mru", "T_Mssntp", "T_Multicastclient", "T_Nic", "T_Nolink",
  "T_Nomodify", "T_Nomrulist", "T_None", "T_Nonvolatile", "T_Noepeer",
  "T_Nopeer", "T_Noquery", "T_Noselect", "T_Noserve", "T_Notrap",
  "T_Notrust", "T_Ntp", "T_Ntpport", "T_NtpSignDsocket", "T_Orphan",
  "T_Orphanwait", "T_PCEdigest", "T_Panic", "T_Peer", "T_Peerstats",
  "T_Phone", "T_Pid", "T_Pidfile", "T_Poll", "T_PollSkewList", "T_Pool",
  "T_Port", "T_PpsData", "T_Preempt", "T_Prefer", "T_Protostats", "T_Pw",
  "T_Randfile", "T_Rawstats", "T_Refid", "T_Requestkey", "T_Reset",
  "T_Restrict", "T_Revoke", "T_Rlimit", "T_Saveconfigdir", "T_Server",
  "T_Serverresponse", "T_ServerresponseFuzz", "T_Setvar", "T_Source",
  "T_Stacksize", "T_Statistics", "T_Stats", "T_Statsdir", "T_Step",
  "T_Stepback", "T_Stepfwd", "T_Stepout", "T_Stratum", "T_String", "T_Sys",
  "T_Sysstats", "T_Tick", "T_Time1", "T_Time2", "T_TimeData", "T_Timer",
  "T_Timingstats", "T_Tinker", "T_Tos", "T_Trap", "T_True", "T_Trustedkey",
  "T_Ttl", "T_Type", "T_U_int", "T_UEcrypto", "T_UEcryptonak",
  "T_UEdigest", "T_Unconfig", "T_Unpeer", "T_Version", "T_WanderThreshold",
  "T_Week", "T_Wildcard", "T_Xleave", "T_Xmtnonce", "T_Year", "T_Flag",
  "T_EOC", "T_Simulate", "T_Beep_Delay", "T_Sim_Duration",
  "T_Server_Offset", "T_Duration", "T_Freq_Offset", "T_Wander", "T_Jitter",
  "T_Prop_Delay", "T_Proc_Delay", "'|'", "'='", "'('", "')'", "'{'", "'}'",
  "$accept", "configuration", "command_list", "command", "server_command",
  "client_type", "address", "ip_address", "address_fam", "option_list",
  "option", "option_flag", "option_flag_keyword", "option_int",
  "option_int_keyword", "option_str", "option_str_keyword",
  "unpeer_command", "unpeer_keyword", "other_mode_command",
  "authentication_command", "crypto_command_list", "crypto_command",
  "crypto_str_keyword", "orphan_mode_command", "tos_option_list",
  "tos_option", "tos_option_int_keyword", "tos_option_dbl_keyword",
  "monitoring_command", "stats_list", "stat", "filegen_option_list",
  "filegen_option", "link_nolink", "enable_disable", "filegen_type",
  "access_control_command", "restrict_mask", "res_ippeerlimit",
  "ac_flag_list", "access_control_flag", "discard_option_list",
  "discard_option", "discard_option_keyword", "mru_option_list",
  "mru_option", "mru_option_keyword", "fudge_command", "fudge_factor_list",
  "fudge_factor", "fudge_factor_dbl_keyword", "fudge_factor_bool_keyword",
  "device_command", "device_item_list", "device_item",
  "device_item_path_keyword", "rlimit_command", "rlimit_option_list",
  "rlimit_option", "rlimit_option_keyword", "system_option_command",
  "system_option_list", "system_option", "system_option_flag_keyword",
  "system_option_local_flag_keyword", "tinker_command",
  "tinker_option_list", "tinker_option", "tinker_option_keyword",
  "miscellaneous_command", "misc_cmd_dbl_keyword", "misc_cmd_int_keyword",
  "opt_hash_check", "misc_cmd_str_keyword", "misc_cmd_str_lcl_keyword",
  "drift_parm", "pollskew_list", "pollskew_spec", "pollskew_cycle",
  "variable_assign", "t_default_or_zero", "trap_option_list",
  "trap_option", "log_config_list", "log_config_command",
  "interface_command", "interface_nic", "nic_rule_class",
  "nic_rule_action", "reset_command", "counter_set_list",
  "counter_set_keyword", "integer_list", "integer_list_range",
  "integer_list_range_elt", "integer_range", "string_list", "address_list",
  "boolean", "number", "basedate", "simulate_command", "sim_conf_start",
  "sim_init_statement_list", "sim_init_statement", "sim_init_keyword",
  "sim_server_list", "sim_server", "sim_server_offset", "sim_server_name",
  "sim_act_list", "sim_act", "sim_act_stmt_list", "sim_act_stmt",
  "sim_act_keyword", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   124,    61,    40,
      41,   123,   125
};
# endif

#define YYPACT_NINF -244

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-244)))

#define YYTABLE_NINF -7

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      59,  -179,   -40,  -244,  -244,  -244,   -20,  -244,  -135,   -50,
     172,     2,  -131,  -244,   172,  -244,   -18,   -50,  -244,  -125,
    -244,  -123,  -106,  -104,  -244,  -102,  -244,  -244,   -50,    19,
     212,   -50,  -244,  -244,   -98,  -244,   -84,  -244,  -244,  -244,
      25,    14,    10,    30,     1,  -244,  -244,   -73,   -18,   -72,
    -244,     0,   652,   -69,   -63,    42,  -244,  -244,  -244,   113,
     258,   -92,  -244,   -50,  -244,   -50,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,    -2,    48,   -57,
     -56,  -244,   -25,  -244,  -244,   -94,  -244,  -244,  -244,   101,
     -69,  -244,    34,  -244,  -244,  -124,  -244,   -39,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
     172,  -244,  -244,  -244,  -244,  -244,  -244,     2,  -244,    65,
     102,  -244,   172,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,    15,   441,  -244,  -244,    17,  -244,  -102,  -244,
    -244,   -50,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,   212,  -244,    72,   -50,  -244,  -244,   -21,   -13,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,    14,  -244,    83,
     132,   139,    83,    34,  -244,  -244,  -244,  -244,     1,  -244,
     114,   -36,  -244,   -18,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,     0,  -244,    -2,    11,
    -244,  -244,  -244,   -41,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,   652,  -244,   118,    -2,  -244,  -244,  -244,   119,
     -63,  -244,  -244,  -244,   131,  -244,    -3,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,     5,
    -161,  -244,  -244,  -244,  -244,  -244,   137,  -244,    33,  -244,
     -69,  -244,  -244,  -244,  -124,  -244,    35,  -244,  -244,  -244,
    -244,  -244,   112,    37,  -244,  -244,  -244,  -244,  -244,    38,
     140,  -244,  -244,    15,  -244,    -2,   -41,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,   152,
    -244,   153,  -244,    83,    83,  -244,    83,  -244,  -244,    49,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,   -51,   185,  -244,  -244,  -244,   444,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -147,    22,    12,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,    55,  -244,  -244,     8,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,    23,  -244,
     532,  -244,  -244,   532,  -244,   209,   -69,   171,  -244,   180,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,   -67,  -244,    66,    39,    52,  -151,  -244,    40,  -244,
      -2,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
     189,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,   205,  -244,  -244,
     532,   532,   532,  -244,  -244,  -244,  -244,    43,  -244,  -244,
    -244,   -50,  -244,  -244,  -244,    54,  -244,  -244,  -244,  -244,
    -244,    53,    56,    -2,    63,  -188,  -244,    64,    -2,  -244,
    -244,  -244,    51,    21,  -244,  -244,  -244,  -244,  -244,   109,
      67,    69,  -244,    76,  -244,    -2,  -244,  -244
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,    25,    61,   257,     0,    74,     0,     0,
       0,     0,   271,   260,     0,   249,     0,     0,   265,     0,
     289,     0,     0,     0,   261,     0,   266,    26,     0,     0,
       0,     0,   290,   258,     0,    24,     0,   267,   272,    23,
       0,     0,     0,     0,     0,   268,    22,     0,     0,     0,
     259,     0,     0,     0,     0,     0,    59,    60,   326,     0,
       2,     0,     7,     0,     8,     0,     9,    10,    13,    11,
      12,    14,    20,    15,    16,    17,    18,     0,     0,     0,
       0,   241,     0,   242,    19,     0,     5,    65,    66,    67,
       0,    29,   140,    30,    31,     0,    27,     0,   215,   216,
     217,   218,   221,   219,   220,   222,   223,   224,   225,   226,
     210,   212,   213,   214,   167,   168,   169,   131,   165,     0,
     269,   250,   209,   106,   107,   108,   109,   113,   110,   111,
     112,   114,     0,     6,    68,    69,   264,   286,   251,   285,
     318,    62,    64,   173,   174,   175,   176,   177,   178,   179,
     180,   132,   171,     0,    63,    73,   316,   252,   253,    70,
     301,   302,   303,   304,   305,   306,   307,   298,   300,   142,
      30,    31,   142,   140,    71,   208,   206,   207,   202,   204,
       0,     0,   254,   101,   105,   102,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   227,   229,     0,     0,
      90,    91,    92,     0,    93,    94,   100,    95,    99,    96,
      97,    98,    83,    85,     0,     0,    89,   280,   312,     0,
      72,   311,   313,   309,   256,     1,     0,     4,    32,    58,
     323,   322,   243,   244,   245,   246,   297,   296,   295,     0,
       0,    82,    78,    79,    80,    81,     0,    75,     0,   139,
       0,   138,   201,   200,   196,   198,     0,    28,   211,   164,
     166,   270,   103,     0,   192,   193,   194,   195,   191,     0,
       0,   189,   190,   181,   183,     0,     0,   247,   263,   262,
     248,   284,   317,   170,   172,   315,   276,   275,   273,     0,
     299,     0,   144,   142,   142,   144,   142,   203,   205,     0,
     104,   228,   230,   324,   321,   319,   320,    88,    84,    86,
      87,   255,     0,   310,   308,     3,    21,   291,   292,   293,
     288,   294,   287,   330,   331,     0,     0,     0,    77,    76,
     141,   197,   199,   123,   122,     0,   120,   121,     0,   115,
     118,   119,   187,   188,   186,   182,   184,   185,     0,   143,
     134,   144,   144,   137,   144,   279,     0,     0,   281,     0,
      38,    39,    40,    41,    57,    50,    52,    51,    54,    42,
      43,    44,    45,    53,    55,    46,    47,    33,    34,    37,
      35,     0,    36,     0,     0,     0,     0,   333,     0,   328,
       0,   116,   130,   126,   128,   124,   125,   127,   129,   117,
       0,   147,   148,   149,   150,   151,   152,   153,   155,   156,
     154,   157,   158,   159,   160,   161,   162,     0,   163,   145,
     135,   136,   133,   278,   277,   283,   282,     0,    48,    49,
      56,     0,   327,   325,   332,     0,   329,   274,   146,   314,
     336,     0,     0,     0,     0,     0,   338,     0,     0,   334,
     337,   335,     0,     0,   343,   344,   345,   346,   347,     0,
       0,     0,   339,     0,   341,     0,   340,   342
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -244,  -244,  -244,   -35,  -244,  -244,    -9,    -7,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,    79,  -244,  -244,  -244,
    -244,   -32,  -244,  -244,  -244,  -244,  -244,  -244,   115,  -129,
    -243,  -244,  -244,   177,  -244,  -244,   144,  -244,  -244,  -244,
      24,  -244,  -244,  -244,  -244,    45,  -244,  -244,  -244,   124,
    -244,  -244,   292,   -78,  -244,  -244,  -244,  -244,   111,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,   173,  -244,  -244,  -244,  -244,
    -244,  -244,   146,  -244,  -244,    95,  -244,  -244,   285,    41,
    -196,  -244,  -244,  -244,  -244,    -6,  -244,  -244,   -60,  -244,
    -244,  -244,  -117,  -244,  -127,  -244
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    59,    60,    61,    62,    63,   140,    96,    97,   316,
     377,   378,   379,   380,   381,   382,   383,    64,    65,    66,
      67,    89,   247,   248,    68,   212,   213,   214,   215,    69,
     183,   131,   262,   339,   340,   341,   399,    70,   251,   292,
     350,   419,   117,   118,   119,   151,   152,   153,    71,   273,
     274,   275,   276,    72,   254,   255,   256,    73,   178,   179,
     180,    74,   110,   111,   112,   113,    75,   196,   197,   198,
      76,    77,    78,   280,    79,    80,   121,   158,   288,   289,
     182,   424,   311,   358,   138,   139,    81,    82,   322,   239,
      83,   167,   168,   224,   220,   221,   222,   157,   141,   307,
     232,   216,    84,    85,   325,   326,   327,   386,   387,   442,
     388,   445,   446,   459,   460,   461
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      95,    92,   302,   428,   304,   123,   186,   218,   132,   124,
     317,   384,   392,   114,   236,   384,   184,   286,   263,   310,
     356,   160,   161,   444,   252,   226,    93,    86,    94,   305,
      87,    90,   258,   173,   449,   230,   187,   393,   237,   278,
     169,    91,   162,   295,   258,   120,   217,   323,   324,   175,
      88,   133,   353,   134,   228,   188,   229,   287,   253,   189,
       1,   323,   324,   238,   264,   265,   266,   267,   231,     2,
     135,   433,   136,   125,   137,     3,     4,     5,   155,   346,
     318,   279,   319,   249,     6,     7,   170,   163,   171,   142,
       8,     9,   156,    10,    11,   159,   357,    12,   277,    13,
     174,    14,    15,   181,   185,   176,    16,    91,   420,   421,
     115,   422,   223,   225,   227,    17,   116,   164,   233,   234,
     235,    18,   126,   394,   268,   429,    91,   240,    19,   250,
      20,   395,   282,   127,   241,   260,   128,   257,   190,   261,
      21,    22,   284,    23,    24,   282,   333,   306,    25,    26,
     396,   300,    27,    28,   334,   285,   219,   291,   335,   242,
     129,    29,   293,   243,   351,   352,   130,   354,   177,   294,
     269,   191,   192,   193,   194,    30,   172,    31,    32,   195,
      98,   320,   299,    33,   298,    99,    91,   303,   309,   312,
     270,   165,   100,    34,   436,   271,   272,   166,    35,   336,
      36,   314,    37,   315,    38,    39,   321,   328,   397,   329,
     344,   332,   398,   342,   343,    40,    41,    42,    43,    44,
      45,    46,   348,   349,    47,   355,   359,    48,   389,    49,
     390,   391,   337,   454,   455,   456,   457,   458,    50,   423,
     400,   426,   430,   330,    51,    52,    53,   447,    54,    55,
     427,   101,   452,   244,   245,    56,    57,   431,   432,   437,
     246,   435,   438,   439,   441,    -6,    58,   444,     2,   467,
     451,   443,   453,   464,     3,     4,     5,   143,   144,   145,
     146,   448,   466,     6,     7,   102,   103,   465,   296,     8,
       9,   308,    10,    11,   259,   283,    12,   345,    13,   331,
      14,    15,   297,   338,   104,    16,   122,   301,   147,   105,
     148,   281,   149,   290,    17,   313,   154,   347,   150,   385,
      18,   454,   455,   456,   457,   458,   434,    19,   450,    20,
       0,   462,   463,     0,     0,     0,     0,     0,     0,    21,
      22,   106,    23,    24,     0,     0,     0,    25,    26,   425,
       0,    27,    28,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,     0,     0,   107,   108,   109,     0,     0,
       0,     0,     0,     0,    30,     0,    31,    32,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,    35,     0,    36,
       0,    37,     0,    38,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,    41,    42,    43,    44,    45,
      46,     0,   440,    47,     0,     0,    48,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,    51,    52,    53,     0,    54,    55,     0,
       0,     2,     0,   360,    56,    57,     0,     3,     4,     5,
       0,     0,     0,   361,    -6,    58,     6,     7,     0,     0,
       0,     0,     8,     9,     0,    10,    11,     0,     0,    12,
       0,    13,     0,    14,    15,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    18,   362,   363,   364,     0,     0,     0,
      19,     0,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,   365,    23,    24,     0,     0,     0,
      25,    26,     0,     0,    27,    28,     0,     0,     0,     0,
       0,     0,     0,    29,     0,   366,     0,     0,     0,     0,
       0,     0,     0,     0,   367,     0,   368,    30,     0,    31,
      32,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,   369,     0,     0,    34,   401,     0,     0,     0,
      35,     0,    36,     0,    37,   402,    38,    39,     0,     0,
       0,     0,     0,   370,   371,   403,     0,    40,    41,    42,
      43,    44,    45,    46,     0,     0,    47,     0,     0,    48,
       0,    49,     0,     0,     0,   404,     0,     0,   405,     0,
      50,     0,     0,     0,   406,     0,    51,    52,    53,     0,
      54,    55,   372,     0,   373,     0,     0,    56,    57,     0,
       0,     0,   374,     0,     0,     0,   375,   376,    58,   407,
       0,     0,     0,   408,   409,     0,     0,   410,   411,   412,
       0,   413,   414,   415,   199,   416,   200,   201,     0,     0,
       0,     0,     0,   202,     0,     0,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   417,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     418,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,   206,     0,     0,     0,     0,     0,   207,     0,   208,
       0,     0,     0,   209,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   210,   211
};

static const yytype_int16 yycheck[] =
{
       9,     8,   198,    70,    45,    23,     6,    70,    17,    27,
       5,   162,     4,    11,    39,   162,    48,    30,     3,   215,
      71,     7,     8,   211,   148,    60,    76,   206,    78,    70,
      70,   166,   110,    42,   222,    37,    36,    29,    63,    22,
      30,   176,    28,   172,   122,   176,    53,   208,   209,    48,
      70,   176,   295,   176,    63,    55,    65,    70,   182,    59,
       1,   208,   209,    88,    49,    50,    51,    52,    70,    10,
     176,   222,   176,    91,   176,    16,    17,    18,   176,   275,
      75,    64,    77,    90,    25,    26,    76,    73,    78,    70,
      31,    32,   176,    34,    35,    70,   147,    38,   133,    40,
      70,    42,    43,   176,   176,   104,    47,   176,   351,   352,
     108,   354,    70,     0,   206,    56,   114,   103,    70,   176,
     176,    62,   140,   115,   109,   192,   176,   221,    69,    95,
      71,   123,   141,   151,    33,    70,   154,   176,   138,    37,
      81,    82,    70,    84,    85,   154,    34,   188,    89,    90,
     142,   183,    93,    94,    42,   176,   219,    74,    46,    58,
     178,   102,    30,    62,   293,   294,   184,   296,   167,    30,
     155,   171,   172,   173,   174,   116,   166,   118,   119,   179,
       8,   176,   218,   124,    70,    13,   176,   176,    70,    70,
     175,   177,    20,   134,   390,   180,   181,   183,   139,    87,
     141,    70,   143,   206,   145,   146,   201,    70,   200,   176,
      70,   176,   204,   176,   176,   156,   157,   158,   159,   160,
     161,   162,    70,    70,   165,   176,    41,   168,   206,   170,
     218,   176,   120,   212,   213,   214,   215,   216,   179,    30,
     217,    70,   176,   250,   185,   186,   187,   443,   189,   190,
      70,    79,   448,   152,   153,   196,   197,   218,   206,    70,
     159,   221,    57,   220,   210,   206,   207,   211,    10,   465,
     206,   218,   221,   206,    16,    17,    18,    65,    66,    67,
      68,   218,   206,    25,    26,   113,   114,   218,   173,    31,
      32,   212,    34,    35,   117,   151,    38,   273,    40,   254,
      42,    43,   178,   191,   132,    47,    14,   196,    96,   137,
      98,   138,   100,   167,    56,   220,    31,   276,   106,   325,
      62,   212,   213,   214,   215,   216,   386,    69,   445,    71,
      -1,   222,   459,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,   169,    84,    85,    -1,    -1,    -1,    89,    90,   356,
      -1,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,   193,   194,   195,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,   118,   119,    -1,    -1,
      -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   134,    -1,    -1,    -1,    -1,   139,    -1,   141,
      -1,   143,    -1,   145,   146,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   156,   157,   158,   159,   160,   161,
     162,    -1,   431,   165,    -1,    -1,   168,    -1,   170,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,    -1,
      -1,    -1,    -1,   185,   186,   187,    -1,   189,   190,    -1,
      -1,    10,    -1,     9,   196,   197,    -1,    16,    17,    18,
      -1,    -1,    -1,    19,   206,   207,    25,    26,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,    -1,    -1,    38,
      -1,    40,    -1,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    62,    60,    61,    62,    -1,    -1,    -1,
      69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    80,    84,    85,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110,    -1,   112,   116,    -1,   118,
     119,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,   128,    -1,    -1,   134,    44,    -1,    -1,    -1,
     139,    -1,   141,    -1,   143,    53,   145,   146,    -1,    -1,
      -1,    -1,    -1,   149,   150,    63,    -1,   156,   157,   158,
     159,   160,   161,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,   170,    -1,    -1,    -1,    83,    -1,    -1,    86,    -1,
     179,    -1,    -1,    -1,    92,    -1,   185,   186,   187,    -1,
     189,   190,   188,    -1,   190,    -1,    -1,   196,   197,    -1,
      -1,    -1,   198,    -1,    -1,    -1,   202,   203,   207,   117,
      -1,    -1,    -1,   121,   122,    -1,    -1,   125,   126,   127,
      -1,   129,   130,   131,    12,   133,    14,    15,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   163,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      -1,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,   136
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    10,    16,    17,    18,    25,    26,    31,    32,
      34,    35,    38,    40,    42,    43,    47,    56,    62,    69,
      71,    81,    82,    84,    85,    89,    90,    93,    94,   102,
     116,   118,   119,   124,   134,   139,   141,   143,   145,   146,
     156,   157,   158,   159,   160,   161,   162,   165,   168,   170,
     179,   185,   186,   187,   189,   190,   196,   197,   207,   224,
     225,   226,   227,   228,   240,   241,   242,   243,   247,   252,
     260,   271,   276,   280,   284,   289,   293,   294,   295,   297,
     298,   309,   310,   313,   325,   326,   206,    70,    70,   244,
     166,   176,   230,    76,    78,   229,   230,   231,     8,    13,
      20,    79,   113,   114,   132,   137,   169,   193,   194,   195,
     285,   286,   287,   288,    11,   108,   114,   265,   266,   267,
     176,   299,   285,    23,    27,    91,   140,   151,   154,   178,
     184,   254,   229,   176,   176,   176,   176,   176,   307,   308,
     229,   321,    70,    65,    66,    67,    68,    96,    98,   100,
     106,   268,   269,   270,   321,   176,   176,   320,   300,    70,
       7,     8,    28,    73,   103,   177,   183,   314,   315,    30,
      76,    78,   166,   229,    70,    48,   104,   167,   281,   282,
     283,   176,   303,   253,   254,   176,     6,    36,    55,    59,
     138,   171,   172,   173,   174,   179,   290,   291,   292,    12,
      14,    15,    21,    24,    54,    97,    99,   105,   107,   111,
     135,   136,   248,   249,   250,   251,   324,   230,    70,   219,
     317,   318,   319,    70,   316,     0,   226,   206,   229,   229,
      37,    70,   323,    70,   176,   176,    39,    63,    88,   312,
     221,    33,    58,    62,   152,   153,   159,   245,   246,   230,
      95,   261,   148,   182,   277,   278,   279,   176,   286,   266,
      70,    37,   255,     3,    49,    50,    51,    52,   109,   155,
     175,   180,   181,   272,   273,   274,   275,   226,    22,    64,
     296,   308,   229,   269,    70,   176,    30,    70,   301,   302,
     315,    74,   262,    30,    30,   262,   261,   282,    70,   218,
     254,   291,   323,   176,    45,    70,   188,   322,   249,    70,
     323,   305,    70,   318,    70,   206,   232,     5,    75,    77,
     176,   201,   311,   208,   209,   327,   328,   329,    70,   176,
     230,   278,   176,    34,    42,    46,    87,   120,   191,   256,
     257,   258,   176,   176,    70,   273,   323,   322,    70,    70,
     263,   262,   262,   263,   262,   176,    71,   147,   306,    41,
       9,    19,    60,    61,    62,    80,   101,   110,   112,   128,
     149,   150,   188,   190,   198,   202,   203,   233,   234,   235,
     236,   237,   238,   239,   162,   328,   330,   331,   333,   206,
     218,   176,     4,    29,   115,   123,   142,   200,   204,   259,
     217,    44,    53,    63,    83,    86,    92,   117,   121,   122,
     125,   126,   127,   129,   130,   131,   133,   163,   198,   264,
     263,   263,   263,    30,   304,   230,    70,    70,    70,   192,
     176,   218,   206,   222,   331,   221,   323,    70,    57,   220,
     229,   210,   332,   218,   211,   334,   335,   323,   218,   222,
     335,   206,   323,   221,   212,   213,   214,   215,   216,   336,
     337,   338,   222,   337,   206,   218,   206,   323
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   223,   224,   225,   225,   225,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   227,   228,   228,   228,   228,   228,   229,   229,   230,
     231,   231,   232,   232,   233,   233,   233,   234,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   236,   236,
     237,   237,   237,   237,   237,   237,   238,   239,   240,   241,
     241,   242,   242,   242,   242,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   244,   244,   245,   245,   246,   246,
     246,   246,   246,   247,   248,   248,   249,   249,   249,   249,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   251,
     251,   252,   252,   252,   253,   253,   254,   254,   254,   254,
     254,   254,   254,   254,   255,   255,   256,   256,   256,   256,
     257,   257,   258,   258,   259,   259,   259,   259,   259,   259,
     259,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     261,   261,   262,   262,   263,   263,   263,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   265,   265,   266,   267,   267,   267,
     268,   268,   269,   270,   270,   270,   270,   270,   270,   270,
     270,   271,   272,   272,   273,   273,   273,   273,   273,   274,
     274,   274,   275,   275,   275,   275,   276,   277,   277,   278,
     279,   279,   280,   281,   281,   282,   283,   283,   283,   284,
     284,   285,   285,   286,   286,   287,   287,   287,   287,   287,
     287,   288,   288,   288,   288,   288,   288,   289,   290,   290,
     291,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   293,   293,   293,   293,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   294,   294,   294,
     295,   295,   296,   296,   296,   297,   298,   298,   298,   299,
     299,   299,   300,   300,   301,   302,   302,   303,   304,   304,
     305,   305,   306,   306,   307,   307,   308,   309,   309,   310,
     310,   311,   311,   311,   311,   312,   312,   312,   313,   314,
     314,   315,   315,   315,   315,   315,   315,   315,   316,   316,
     317,   317,   318,   318,   319,   320,   320,   321,   321,   322,
     322,   322,   323,   323,   324,   325,   326,   327,   327,   328,
     329,   329,   330,   330,   331,   332,   333,   334,   334,   335,
     336,   336,   337,   338,   338,   338,   338,   338
};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     0,     2,     2,     2,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     5,     4,     5,     5,     4,     3,     3,
       0,     2,     0,     2,     0,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     2,
       1,     1,     2,     2,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     3,     3,     1,
       2,     2,     2,     2,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       2,     0,     0,     2,     4,     1,     1,     4,     1,     0,
       0,     2,     2,     2,     2,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     1,     1,     5,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     5,     1,     3,     2,     3,
       1,     1,     2,     1,     5,     4,     3,     2,     1,     6,
       3,     2,     3,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print(FILE* yyoutput, int yytype, YYSTYPE const* const yyvaluep)
{
    FILE* yyo = yyoutput;
    YYUSE(yyo);
    if (!yyvaluep)
        return;
# ifdef YYPRINT
    if (yytype < YYNTOKENS)
        YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    YYUSE(yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print(FILE* yyoutput, int yytype, YYSTYPE const* const yyvaluep)
{
    YYFPRINTF(yyoutput, "%s %s (",
        yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

    yy_symbol_value_print(yyoutput, yytype, yyvaluep);
    YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yytype_int16* yybottom, yytype_int16* yytop)
{
    YYFPRINTF(stderr, "Stack now");
    for (; yybottom <= yytop; yybottom++)
    {
        int yybot = *yybottom;
        YYFPRINTF(stderr, " %d", yybot);
    }
    YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yytype_int16* yyssp, YYSTYPE* yyvsp, int yyrule)
{
    unsigned long int yylno = yyrline[yyrule];
    int yynrhs = yyr2[yyrule];
    int yyi;
    YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
        yyrule - 1, yylno);
    /* The symbols being reduced.  */
    for (yyi = 0; yyi < yynrhs; yyi++)
    {
        YYFPRINTF(stderr, "   $%d = ", yyi + 1);
        yy_symbol_print(stderr,
            yystos[yyssp[yyi + 1 - yynrhs]],
            &(yyvsp[(yyi + 1) - (yynrhs)])
        );
        YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
   /* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen(const char* yystr)
{
    YYSIZE_T yylen;
    for (yylen = 0; yystr[yylen]; yylen++)
        continue;
    return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char*
yystpcpy(char* yydest, const char* yysrc)
{
    char* yyd = yydest;
    const char* yys = yysrc;

    while ((*yyd++ = *yys++) != '\0')
        continue;

    return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr(char* yyres, const char* yystr)
{
    if (*yystr == '"')
    {
        YYSIZE_T yyn = 0;
        char const* yyp = yystr;

        for (;;)
            switch (*++yyp)
            {
            case '\'':
            case ',':
                goto do_not_strip_quotes;

            case '\\':
                if (*++yyp != '\\')
                    goto do_not_strip_quotes;
                /* Fall through.  */
            default:
                if (yyres)
                    yyres[yyn] = *yyp;
                yyn++;
                break;

            case '"':
                if (yyres)
                    yyres[yyn] = '\0';
                return yyn;
            }
    do_not_strip_quotes:;
    }

    if (!yyres)
        return yystrlen(yystr);

    return yystpcpy(yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error(YYSIZE_T* yymsg_alloc, char** yymsg,
    yytype_int16* yyssp, int yytoken)
{
    YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
    YYSIZE_T yysize = yysize0;
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    /* Internationalized format string. */
    const char* yyformat = YY_NULLPTR;
    /* Arguments of yyformat. */
    char const* yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
    /* Number of reported tokens (one for the "unexpected", one per
       "expected"). */
    int yycount = 0;

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yychar) is if
         this state is a consistent state with a default action.  Thus,
         detecting the absence of a lookahead is sufficient to determine
         that there is no unexpected or expected token to report.  In that
         case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is a
         consistent state with a default action.  There might have been a
         previous inconsistent state, consistent state with a non-default
         action, or user semantic action that manipulated yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (yytoken != YYEMPTY)
    {
        int yyn = yypact[*yyssp];
        yyarg[yycount++] = yytname[yytoken];
        if (!yypact_value_is_default(yyn))
        {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = YYLAST - yyn + 1;
            int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
            int yyx;

            for (yyx = yyxbegin; yyx < yyxend; ++yyx)
                if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                    && !yytable_value_is_error(yytable[yyx + yyn]))
                {
                    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                        yycount = 1;
                        yysize = yysize0;
                        break;
                    }
                    yyarg[yycount++] = yytname[yyx];
                    {
                        YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);
                        if (!(yysize <= yysize1
                            && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                            return 2;
                        yysize = yysize1;
                    }
                }
        }
    }

    switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

    {
        YYSIZE_T yysize1 = yysize + yystrlen(yyformat);
        if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
            return 2;
        yysize = yysize1;
    }

    if (*yymsg_alloc < yysize)
    {
        *yymsg_alloc = 2 * yysize;
        if (!(yysize <= *yymsg_alloc
            && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
            *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
        return 1;
    }

    /* Avoid sprintf, as that infringes on the user's name space.
       Don't have undefined behavior even if the translation
       produced a string with the wrong number of "%s"s.  */
    {
        char* yyp = *yymsg;
        int yyi = 0;
        while ((*yyp = *yyformat) != '\0')
            if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
                yyp += yytnamerr(yyp, yyarg[yyi++]);
                yyformat += 2;
            }
            else
            {
                yyp++;
                yyformat++;
            }
    }
    return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct(const char* yymsg, int yytype, YYSTYPE* yyvaluep)
{
    YYUSE(yyvaluep);
    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        YYUSE(yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse(void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

       /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16* yyss;
    yytype_int16* yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE* yyvs;
    YYSTYPE* yyvsp;

    YYSIZE_T yystacksize;

    int yyn;
    int yyresult;
    /* Lookahead token as an internal (translated) token number.  */
    int yytoken = 0;
    /* The variables used to return semantic value and location from the
       action routines.  */
    YYSTYPE yyval;

#if YYERROR_VERBOSE
    /* Buffer for error messages, and its allocated size.  */
    char yymsgbuf[128];
    char* yymsg = yymsgbuf;
    YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

    /* The number of symbols on the RHS of the reduced rule.
       Keep to zero when no symbol should be popped.  */
    int yylen = 0;

    yyssp = yyss = yyssa;
    yyvsp = yyvs = yyvsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */
    goto yysetstate;

    /*------------------------------------------------------------.
    | yynewstate -- Push a new state, which is found in yystate.  |
    `------------------------------------------------------------*/
yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;

yysetstate:
    *yyssp = yystate;

    if (yyss + yystacksize - 1 <= yyssp)
    {
        /* Get the current used size of the three stacks, in elements.  */
        YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
        {
            /* Give user a chance to reallocate the stack.  Use copies of
               these so that the &'s don't force the real ones into
               memory.  */
            YYSTYPE* yyvs1 = yyvs;
            yytype_int16* yyss1 = yyss;

            /* Each stack pointer address is followed by the size of the
               data in use in that stack, in bytes.  This used to be a
               conditional around just the two extra args, but that might
               be undefined if yyoverflow is a macro.  */
            yyoverflow(YY_("memory exhausted"),
                &yyss1, yysize * sizeof(*yyssp),
                &yyvs1, yysize * sizeof(*yyvsp),
                &yystacksize);

            yyss = yyss1;
            yyvs = yyvs1;
        }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
        goto yyexhaustedlab;
# else
        /* Extend the stack our own way.  */
        if (YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;
        yystacksize *= 2;
        if (YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yytype_int16* yyss1 = yyss;
            union yyalloc* yyptr =
                (union yyalloc*)YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
            if (!yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE(yyss_alloc, yyss);
            YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
            if (yyss1 != yyssa)
                YYSTACK_FREE(yyss1);
        }
# endif
#endif /* no yyoverflow */

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;

        YYDPRINTF((stderr, "Stack size increased to %lu\n",
            (unsigned long int) yystacksize));

        if (yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }

    YYDPRINTF((stderr, "Entering state %d\n", yystate));

    if (yystate == YYFINAL)
        YYACCEPT;

    goto yybackup;

    /*-----------.
    | yybackup.  |
    `-----------*/
yybackup:

    /* Do appropriate processing given the current state.  Read a
       lookahead token if we need one and don't already have one.  */

       /* First try to decide what to do without reference to lookahead token.  */
    yyn = yypact[yystate];
    if (yypact_value_is_default(yyn))
        goto yydefault;

    /* Not known => get a lookahead token if don't already have one.  */

    /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
    if (yychar == YYEMPTY)
    {
        YYDPRINTF((stderr, "Reading a token: "));
        yychar = yylex();
    }

    if (yychar <= YYEOF)
    {
        yychar = yytoken = YYEOF;
        YYDPRINTF((stderr, "Now at end of input.\n"));
    }
    else
    {
        yytoken = YYTRANSLATE(yychar);
        YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;
    yyn = yytable[yyn];
    if (yyn <= 0)
    {
        if (yytable_value_is_error(yyn))
            goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
    }

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus)
        yyerrstatus--;

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the shifted token.  */
    yychar = YYEMPTY;

    yystate = yyn;
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        * ++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END

        goto yynewstate;


    /*-----------------------------------------------------------.
    | yydefault -- do the default action for the current state.  |
    `-----------------------------------------------------------*/
yydefault:
    yyn = yydefact[yystate];
    if (yyn == 0)
        goto yyerrlab;
    goto yyreduce;


    /*-----------------------------.
    | yyreduce -- Do a reduction.  |
    `-----------------------------*/
yyreduce:
    /* yyn is the number of a rule to reduce with.  */
    yylen = yyr2[yyn];

    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1 - yylen];


    YY_REDUCE_PRINT(yyn);
    switch (yyn)
    {
    case 5:
#line 407 "ntp_parser.y" /* yacc.c:1646  */
    {
        /* I will need to incorporate much more fine grained
         * error messages. The following should suffice for
         * the time being.
         */
        struct FILE_INFO* ip_ctx = lex_current();
        msyslog(LOG_ERR,
            "syntax error in %s line %d, column %d",
            ip_ctx->fname,
            ip_ctx->errpos.nline,
            ip_ctx->errpos.ncol);
    }
#line 2007 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 21:
#line 444 "ntp_parser.y" /* yacc.c:1646  */
    {
        peer_node* my_node;

        my_node = create_peer_node((yyvsp[-2].Integer), (yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
        APPEND_G_FIFO(cfgt.peers, my_node);
    }
#line 2018 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 28:
#line 463 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = create_address_node((yyvsp[0].String), (yyvsp[-1].Integer)); }
#line 2024 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 29:
#line 468 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = create_address_node((yyvsp[0].String), AF_UNSPEC); }
#line 2030 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 30:
#line 473 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = AF_INET; }
#line 2036 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 31:
#line 475 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = AF_INET6; }
#line 2042 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 32:
#line 480 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2048 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 33:
#line 482 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2057 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 37:
#line 496 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2063 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 48:
#line 514 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2069 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 49:
#line 516 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_uval((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2075 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 56:
#line 530 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2081 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 58:
#line 544 "ntp_parser.y" /* yacc.c:1646  */
    {
        unpeer_node* my_node;

        my_node = create_unpeer_node((yyvsp[0].Address_node));
        if (my_node)
            APPEND_G_FIFO(cfgt.unpeers, my_node);
    }
#line 2093 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 61:
#line 565 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.broadcastclient = 1; }
#line 2099 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 62:
#line 567 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.manycastserver, (yyvsp[0].Address_fifo)); }
#line 2105 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 63:
#line 569 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.multicastclient, (yyvsp[0].Address_fifo)); }
#line 2111 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 64:
#line 571 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.mdnstries = (yyvsp[0].Integer); }
#line 2117 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 65:
#line 582 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* atrv;

        atrv = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
        APPEND_G_FIFO(cfgt.vars, atrv);
    }
#line 2128 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 66:
#line 589 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.control_key = (yyvsp[0].Integer); }
#line 2134 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 67:
#line 591 "ntp_parser.y" /* yacc.c:1646  */
    {
        cfgt.auth.cryptosw++;
        CONCAT_G_FIFOS(cfgt.auth.crypto_cmd_list, (yyvsp[0].Attr_val_fifo));
    }
#line 2143 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 68:
#line 596 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.keys = (yyvsp[0].String); }
#line 2149 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 69:
#line 598 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.keysdir = (yyvsp[0].String); }
#line 2155 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 70:
#line 600 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.request_key = (yyvsp[0].Integer); }
#line 2161 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 71:
#line 602 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.revoke = (yyvsp[0].Integer); }
#line 2167 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 72:
#line 604 "ntp_parser.y" /* yacc.c:1646  */
    {
        /* [Bug 948] leaves it open if appending or
         * replacing the trusted key list is the right
         * way. In any case, either alternative should
         * be coded correctly!
         */
        DESTROY_G_FIFO(cfgt.auth.trusted_key_list, destroy_attr_val); /* remove for append */
        CONCAT_G_FIFOS(cfgt.auth.trusted_key_list, (yyvsp[0].Attr_val_fifo));
    }
#line 2181 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 73:
#line 614 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.ntp_signd_socket = (yyvsp[0].String); }
#line 2187 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 74:
#line 619 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2193 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 75:
#line 621 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2202 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 76:
#line 629 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2208 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 77:
#line 631 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val) = NULL;
        cfgt.auth.revoke = (yyvsp[0].Integer);
        msyslog(LOG_WARNING,
            "'crypto revoke %d' is deprecated, "
            "please use 'revoke %d' instead.",
            cfgt.auth.revoke, cfgt.auth.revoke);
    }
#line 2221 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 83:
#line 656 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.orphan_cmds, (yyvsp[0].Attr_val_fifo)); }
#line 2227 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 84:
#line 661 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2236 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 85:
#line 666 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2245 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 86:
#line 674 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (double)(yyvsp[0].Integer)); }
#line 2251 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 87:
#line 676 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2257 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 88:
#line 678 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (double)(yyvsp[0].Integer)); }
#line 2263 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 89:
#line 680 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Basedate, (yyvsp[0].Integer)); }
#line 2269 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 101:
#line 707 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.stats_list, (yyvsp[0].Int_fifo)); }
#line 2275 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 102:
#line 709 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            cfgt.stats_dir = (yyvsp[0].String);
        }
        else {
            YYFREE((yyvsp[0].String));
            yyerror("statsdir remote configuration ignored");
        }
    }
#line 2288 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 103:
#line 718 "ntp_parser.y" /* yacc.c:1646  */
    {
        filegen_node* fgn;

        fgn = create_filegen_node((yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo));
        APPEND_G_FIFO(cfgt.filegen_opts, fgn);
    }
#line 2299 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 104:
#line 728 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Int_fifo) = (yyvsp[-1].Int_fifo);
        APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 2308 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 105:
#line 733 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Int_fifo) = NULL;
        APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 2317 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 114:
#line 752 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2323 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 115:
#line 754 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2332 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 116:
#line 762 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
        }
        else {
            (yyval.Attr_val) = NULL;
            YYFREE((yyvsp[0].String));
            yyerror("filegen file remote config ignored");
        }
    }
#line 2346 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 117:
#line 772 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
        }
        else {
            (yyval.Attr_val) = NULL;
            yyerror("filegen type remote config ignored");
        }
    }
#line 2359 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 118:
#line 781 "ntp_parser.y" /* yacc.c:1646  */
    {
        const char* err;

        if (lex_from_file()) {
            (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer));
        }
        else {
            (yyval.Attr_val) = NULL;
            if (T_Link == (yyvsp[0].Integer))
                err = "filegen link remote config ignored";
            else
                err = "filegen nolink remote config ignored";
            yyerror(err);
        }
    }
#line 2378 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 119:
#line 796 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2384 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 131:
#line 826 "ntp_parser.y" /* yacc.c:1646  */
    {
        CONCAT_G_FIFOS(cfgt.discard_opts, (yyvsp[0].Attr_val_fifo));
    }
#line 2392 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 132:
#line 830 "ntp_parser.y" /* yacc.c:1646  */
    {
        CONCAT_G_FIFOS(cfgt.mru_opts, (yyvsp[0].Attr_val_fifo));
    }
#line 2400 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 133:
#line 834 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        rn = create_restrict_node((yyvsp[-3].Address_node), (yyvsp[-2].Address_node), (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2413 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 134:
#line 843 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        rn = create_restrict_node(NULL, NULL, (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2426 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 135:
#line 852 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        rn = create_restrict_node(
            create_address_node(
                estrdup("0.0.0.0"),
                AF_INET),
            create_address_node(
                estrdup("0.0.0.0"),
                AF_INET),
            (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2446 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 136:
#line 868 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        rn = create_restrict_node(
            create_address_node(
                estrdup("::"),
                AF_INET6),
            create_address_node(
                estrdup("::"),
                AF_INET6),
            (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2466 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 137:
#line 884 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        APPEND_G_FIFO((yyvsp[0].Attr_val_fifo), create_attr_ival((yyvsp[-2].Integer), 1));
        rn = create_restrict_node(NULL, NULL, (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2480 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 138:
#line 894 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;

        rn = create_restrict_node((yyvsp[-1].Address_node), (yyvsp[0].Address_node), -1, NULL, TRUE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2493 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 139:
#line 903 "ntp_parser.y" /* yacc.c:1646  */
    {
        restrict_node* rn;
        attr_val_fifo* avf;

        avf = NULL;
        APPEND_G_FIFO(avf, create_attr_ival((yyvsp[-1].Integer), 1));
        rn = create_restrict_node((yyvsp[0].Address_node), NULL, -1, avf, TRUE,
            lex_current()->curpos.nline,
            lex_current()->curpos.ncol);
        APPEND_G_FIFO(cfgt.restrict_opts, rn);
    }
#line 2509 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 140:
#line 918 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = NULL; }
#line 2515 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 141:
#line 920 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Address_node) = (yyvsp[0].Address_node);
    }
#line 2523 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 142:
#line 927 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = -1; }
#line 2529 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 143:
#line 929 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (((yyvsp[0].Integer) < -1) || ((yyvsp[0].Integer) > 100)) {
            struct FILE_INFO* ip_ctx;

            ip_ctx = lex_current();
            msyslog(LOG_ERR,
                "Unreasonable ippeerlimit value (%d) in %s line %d, column %d.  Using 0.",
                (yyvsp[0].Integer),
                ip_ctx->fname,
                ip_ctx->curpos.nline,
                ip_ctx->curpos.ncol);
            (yyvsp[0].Integer) = 0;
        }
        (yyval.Integer) = (yyvsp[0].Integer);
    }
#line 2549 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 144:
#line 948 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2555 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 145:
#line 950 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        av = create_attr_ival((yyvsp[0].Integer), 1);
        APPEND_G_FIFO((yyval.Attr_val_fifo), av);
    }
#line 2567 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 146:
#line 958 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        (yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
        av = create_attr_ival(T_ServerresponseFuzz, 1);
        APPEND_G_FIFO((yyval.Attr_val_fifo), av);
    }
#line 2579 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 164:
#line 989 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2588 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 165:
#line 994 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2597 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 166:
#line 1002 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2603 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 170:
#line 1013 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2612 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 171:
#line 1018 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2621 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 172:
#line 1026 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2627 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 181:
#line 1046 "ntp_parser.y" /* yacc.c:1646  */
    {
        addr_opts_node* aon;

        aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
        APPEND_G_FIFO(cfgt.fudge, aon);
    }
#line 2638 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 182:
#line 1056 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2647 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 183:
#line 1061 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2656 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 184:
#line 1069 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2662 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 185:
#line 1071 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2668 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 186:
#line 1073 "ntp_parser.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].Integer) >= 0 && (yyvsp[0].Integer) <= 16) {
            (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
        }
        else {
            (yyval.Attr_val) = NULL;
            yyerror("fudge factor: stratum value not in [0..16], ignored");
        }
    }
#line 2681 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 187:
#line 1082 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2687 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 188:
#line 1084 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2693 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 196:
#line 1106 "ntp_parser.y" /* yacc.c:1646  */
    {
        addr_opts_node* aon;

        aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
        APPEND_G_FIFO(cfgt.device, aon);
    }
#line 2704 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 197:
#line 1116 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2713 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 198:
#line 1121 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2722 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 199:
#line 1129 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2728 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 202:
#line 1143 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.rlimit, (yyvsp[0].Attr_val_fifo)); }
#line 2734 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 203:
#line 1148 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2743 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 204:
#line 1153 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2752 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 205:
#line 1161 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2758 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 209:
#line 1177 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.enable_opts, (yyvsp[0].Attr_val_fifo)); }
#line 2764 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 210:
#line 1179 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.disable_opts, (yyvsp[0].Attr_val_fifo)); }
#line 2770 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 211:
#line 1184 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2779 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 212:
#line 1189 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2788 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 213:
#line 1197 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2794 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 214:
#line 1199 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer));
        }
        else {
            char err_str[128];

            (yyval.Attr_val) = NULL;
            snprintf(err_str, sizeof(err_str),
                "enable/disable %s remote configuration ignored",
                keyword((yyvsp[0].Integer)));
            yyerror(err_str);
        }
    }
#line 2812 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 227:
#line 1238 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.tinker, (yyvsp[0].Attr_val_fifo)); }
#line 2818 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 228:
#line 1243 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2827 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 229:
#line 1248 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 2836 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 230:
#line 1256 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2842 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 243:
#line 1281 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        av = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double));
        APPEND_G_FIFO(cfgt.vars, av);
    }
#line 2853 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 244:
#line 1288 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        av = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
        APPEND_G_FIFO(cfgt.vars, av);
    }
#line 2864 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 245:
#line 1295 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        av = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
        APPEND_G_FIFO(cfgt.vars, av);
    }
#line 2875 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 246:
#line 1302 "ntp_parser.y" /* yacc.c:1646  */
    {
        char error_text[64];
        attr_val* av;

        if (lex_from_file()) {
            av = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
            APPEND_G_FIFO(cfgt.vars, av);
        }
        else {
            YYFREE((yyvsp[0].String));
            snprintf(error_text, sizeof(error_text),
                "%s remote config ignored",
                keyword((yyvsp[-1].Integer)));
            yyerror(error_text);
        }
    }
#line 2895 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 247:
#line 1318 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (!lex_from_file()) {
            YYFREE((yyvsp[-1].String)); /* avoid leak */
            yyerror("remote includefile ignored");
            break;
        }
        if (lex_level() > MAXINCLUDELEVEL) {
            fprintf(stderr, "getconfig: Maximum include file level exceeded.\n");
            msyslog(LOG_ERR, "getconfig: Maximum include file level exceeded.");
        }
        else {
            const char* path = FindConfig((yyvsp[-1].String)); /* might return $2! */
            if (!lex_push_file(path, "r")) {
                fprintf(stderr, "getconfig: Couldn't open <%s>\n", path);
                msyslog(LOG_ERR, "getconfig: Couldn't open <%s>", path);
            }
        }
        YYFREE((yyvsp[-1].String)); /* avoid leak */
    }
#line 2918 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 248:
#line 1337 "ntp_parser.y" /* yacc.c:1646  */
    {
        attr_val* av;

        av = create_attr_sval((yyvsp[-2].Integer), (yyvsp[-1].String));
        av->flag = (yyvsp[0].Integer);
        APPEND_G_FIFO(cfgt.vars, av);
    }
#line 2930 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 249:
#line 1345 "ntp_parser.y" /* yacc.c:1646  */
    { lex_flush_stack(); }
#line 2936 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 250:
#line 1347 "ntp_parser.y" /* yacc.c:1646  */
    { /* see drift_parm below for actions */ }
#line 2942 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 251:
#line 1349 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.logconfig, (yyvsp[0].Attr_val_fifo)); }
#line 2948 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 252:
#line 1351 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.phone, (yyvsp[0].String_fifo)); }
#line 2954 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 253:
#line 1353 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.pollskewlist, (yyvsp[0].Attr_val_fifo)); }
#line 2960 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 254:
#line 1355 "ntp_parser.y" /* yacc.c:1646  */
    { APPEND_G_FIFO(cfgt.setvar, (yyvsp[0].Set_var)); }
#line 2966 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 255:
#line 1357 "ntp_parser.y" /* yacc.c:1646  */
    {
        addr_opts_node* aon;

        aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
        APPEND_G_FIFO(cfgt.trap, aon);
    }
#line 2977 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 256:
#line 1364 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.ttl, (yyvsp[0].Attr_val_fifo)); }
#line 2983 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 261:
#line 1379 "ntp_parser.y" /* yacc.c:1646  */
    {
#ifndef LEAP_SMEAR
        yyerror("Built without LEAP_SMEAR support.");
#endif
    }
#line 2993 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 262:
#line 1388 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = FALSE; }
#line 2999 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 263:
#line 1390 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = TRUE; }
#line 3005 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 264:
#line 1392 "ntp_parser.y" /* yacc.c:1646  */
    {  (yyval.Integer) = TRUE; }
#line 3011 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 269:
#line 1407 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            attr_val* av;
            av = create_attr_sval(T_Driftfile, (yyvsp[0].String));
            APPEND_G_FIFO(cfgt.vars, av);
        }
        else {
            YYFREE((yyvsp[0].String));
            yyerror("driftfile remote configuration ignored");
        }
    }
#line 3026 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 270:
#line 1418 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            attr_val* av;
            av = create_attr_sval(T_Driftfile, (yyvsp[-1].String));
            APPEND_G_FIFO(cfgt.vars, av);
            av = create_attr_dval(T_WanderThreshold, (yyvsp[0].Double));
            APPEND_G_FIFO(cfgt.vars, av);
            msyslog(LOG_WARNING,
                "'driftfile FILENAME WanderValue' is deprecated, "
                "please use separate 'driftfile FILENAME' and "
                "'nonvolatile WanderValue' lines instead.");
        }
        else {
            YYFREE((yyvsp[-1].String));
            yyerror("driftfile remote configuration ignored");
        }
    }
#line 3047 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 271:
#line 1435 "ntp_parser.y" /* yacc.c:1646  */
    {
        if (lex_from_file()) {
            attr_val* av;
            av = create_attr_sval(T_Driftfile, estrdup(""));
            APPEND_G_FIFO(cfgt.vars, av);
        }
        else {
            yyerror("driftfile remote configuration ignored");
        }
    }
#line 3061 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 272:
#line 1448 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 3067 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 273:
#line 1450 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = append_gen_fifo((yyvsp[-1].Attr_val_fifo), (yyvsp[0].Attr_val)); }
#line 3073 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 274:
#line 1455 "ntp_parser.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-2].Integer) < 0 || (yyvsp[0].Integer) < 0) {
            /* bad numbers */
            yyerror("pollskewlist: skew values must be >=0");
            destroy_attr_val((yyvsp[-3].Attr_val));
            (yyvsp[-3].Attr_val) = NULL;
        }
        else if ((yyvsp[-3].Attr_val) == NULL) {
            yyerror("pollskewlist: poll value must be 3-17, inclusive");
        }
        else if ((yyvsp[-3].Attr_val)->attr <= 0) {
            /* process default range */
            (yyvsp[-3].Attr_val)->value.r.first = (yyvsp[-2].Integer);
            (yyvsp[-3].Attr_val)->value.r.last = (yyvsp[0].Integer);
        }
        else if ((yyvsp[-2].Integer) < (1 << ((yyvsp[-3].Attr_val)->attr - 1)) && (yyvsp[0].Integer) < (1 << ((yyvsp[-3].Attr_val)->attr - 1))) {
            (yyvsp[-3].Attr_val)->value.r.first = (yyvsp[-2].Integer);
            (yyvsp[-3].Attr_val)->value.r.last = (yyvsp[0].Integer);
        }
        else {
            yyerror("pollskewlist: randomization limit must be <= half the poll interval");
            destroy_attr_val((yyvsp[-3].Attr_val));
            (yyvsp[-3].Attr_val) = NULL;
        }
        (yyval.Attr_val) = (yyvsp[-3].Attr_val);
    }
#line 3100 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 275:
#line 1481 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val) = ((yyvsp[0].Integer) >= NTP_MINPOLL && (yyvsp[0].Integer) <= NTP_MAXPOLL)
            ? create_attr_rval((yyvsp[0].Integer), 0, 0)
            : NULL;
    }
#line 3110 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 276:
#line 1486 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_rval(-1, 0, 0); }
#line 3116 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 277:
#line 1492 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Set_var) = create_setvar_node((yyvsp[-3].String), (yyvsp[-1].String), (yyvsp[0].Integer)); }
#line 3122 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 279:
#line 1498 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 0; }
#line 3128 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 280:
#line 1503 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 3134 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 281:
#line 1505 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 3143 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 282:
#line 1513 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 3149 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 283:
#line 1515 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), estrdup((yyvsp[0].Address_node)->address));
        destroy_address_node((yyvsp[0].Address_node));
    }
#line 3158 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 284:
#line 1523 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 3167 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 285:
#line 1528 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 3176 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 286:
#line 1536 "ntp_parser.y" /* yacc.c:1646  */
    {
        char	prefix;
        char* type;

        switch ((yyvsp[0].String)[0]) {

        case '+':
        case '-':
        case '=':
            prefix = (yyvsp[0].String)[0];
            type = (yyvsp[0].String) + 1;
            break;

        default:
            prefix = '=';
            type = (yyvsp[0].String);
        }

        (yyval.Attr_val) = create_attr_sval(prefix, estrdup(type));
        YYFREE((yyvsp[0].String));
    }
#line 3202 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 287:
#line 1561 "ntp_parser.y" /* yacc.c:1646  */
    {
        nic_rule_node* nrn;

        nrn = create_nic_rule_node((yyvsp[0].Integer), NULL, (yyvsp[-1].Integer));
        APPEND_G_FIFO(cfgt.nic_rules, nrn);
    }
#line 3213 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 288:
#line 1568 "ntp_parser.y" /* yacc.c:1646  */
    {
        nic_rule_node* nrn;

        nrn = create_nic_rule_node(0, (yyvsp[0].String), (yyvsp[-1].Integer));
        APPEND_G_FIFO(cfgt.nic_rules, nrn);
    }
#line 3224 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 298:
#line 1596 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.reset_counters, (yyvsp[0].Int_fifo)); }
#line 3230 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 299:
#line 1601 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Int_fifo) = (yyvsp[-1].Int_fifo);
        APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 3239 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 300:
#line 1606 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Int_fifo) = NULL;
        APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 3248 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 308:
#line 1630 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 3257 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 309:
#line 1635 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), create_int_node((yyvsp[0].Integer)));
    }
#line 3266 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 310:
#line 1643 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 3275 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 311:
#line 1648 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
    }
#line 3284 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 312:
#line 1656 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival('i', (yyvsp[0].Integer)); }
#line 3290 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 314:
#line 1662 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_rval('-', (yyvsp[-3].Integer), (yyvsp[-1].Integer)); }
#line 3296 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 315:
#line 1667 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.String_fifo) = (yyvsp[-1].String_fifo);
        APPEND_G_FIFO((yyval.String_fifo), create_string_node((yyvsp[0].String)));
    }
#line 3305 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 316:
#line 1672 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.String_fifo) = NULL;
        APPEND_G_FIFO((yyval.String_fifo), create_string_node((yyvsp[0].String)));
    }
#line 3314 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 317:
#line 1680 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Address_fifo) = (yyvsp[-1].Address_fifo);
        APPEND_G_FIFO((yyval.Address_fifo), (yyvsp[0].Address_node));
    }
#line 3323 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 318:
#line 1685 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Address_fifo) = NULL;
        APPEND_G_FIFO((yyval.Address_fifo), (yyvsp[0].Address_node));
    }
#line 3332 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 319:
#line 1693 "ntp_parser.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].Integer) != 0 && (yyvsp[0].Integer) != 1) {
            yyerror("Integer value is not boolean (0 or 1). Assuming 1");
            (yyval.Integer) = 1;
        }
        else {
            (yyval.Integer) = (yyvsp[0].Integer);
        }
    }
#line 3345 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 320:
#line 1701 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 1; }
#line 3351 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 321:
#line 1702 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 0; }
#line 3357 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 322:
#line 1706 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Double) = (double)(yyvsp[0].Integer); }
#line 3363 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 324:
#line 1712 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = basedate_eval_string((yyvsp[0].String)); YYFREE((yyvsp[0].String)); }
#line 3369 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 325:
#line 1720 "ntp_parser.y" /* yacc.c:1646  */
    {
        sim_node* sn;

        sn = create_sim_node((yyvsp[-2].Attr_val_fifo), (yyvsp[-1].Sim_server_fifo));
        APPEND_G_FIFO(cfgt.sim_details, sn);

        /* Revert from ; to \n for end-of-command */
        old_config_style = 1;
    }
#line 3383 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 326:
#line 1737 "ntp_parser.y" /* yacc.c:1646  */
    { old_config_style = 0; }
#line 3389 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 327:
#line 1742 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
    }
#line 3398 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 328:
#line 1747 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
    }
#line 3407 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 329:
#line 1755 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-2].Integer), (yyvsp[0].Double)); }
#line 3413 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 332:
#line 1765 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Sim_server_fifo) = (yyvsp[-1].Sim_server_fifo);
        APPEND_G_FIFO((yyval.Sim_server_fifo), (yyvsp[0].Sim_server));
    }
#line 3422 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 333:
#line 1770 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Sim_server_fifo) = NULL;
        APPEND_G_FIFO((yyval.Sim_server_fifo), (yyvsp[0].Sim_server));
    }
#line 3431 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 334:
#line 1778 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Sim_server) = ONLY_SIM(create_sim_server((yyvsp[-4].Address_node), (yyvsp[-2].Double), (yyvsp[-1].Sim_script_fifo))); }
#line 3437 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 335:
#line 1783 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Double) = (yyvsp[-1].Double); }
#line 3443 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 336:
#line 1788 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = (yyvsp[0].Address_node); }
#line 3449 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 337:
#line 1793 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Sim_script_fifo) = (yyvsp[-1].Sim_script_fifo);
        APPEND_G_FIFO((yyval.Sim_script_fifo), (yyvsp[0].Sim_script));
    }
#line 3458 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 338:
#line 1798 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Sim_script_fifo) = NULL;
        APPEND_G_FIFO((yyval.Sim_script_fifo), (yyvsp[0].Sim_script));
    }
#line 3467 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 339:
#line 1806 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Sim_script) = ONLY_SIM(create_sim_script_info((yyvsp[-3].Double), (yyvsp[-1].Attr_val_fifo))); }
#line 3473 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 340:
#line 1811 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
    }
#line 3482 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 341:
#line 1816 "ntp_parser.y" /* yacc.c:1646  */
    {
        (yyval.Attr_val_fifo) = NULL;
        APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
    }
#line 3491 "ntp_parser.c" /* yacc.c:1646  */
    break;

    case 342:
#line 1824 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-2].Integer), (yyvsp[0].Double)); }
#line 3497 "ntp_parser.c" /* yacc.c:1646  */
    break;


#line 3501 "ntp_parser.c" /* yacc.c:1646  */
    default: break;
    }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action invokes
       YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
       if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
       incorrect destructor might then be invoked immediately.  In the
       case of YYERROR or YYBACKUP, subsequent parser actions might lead
       to an incorrect destructor call or verbose syntax error message
       before the lookahead is translated.  */
    YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);

    *++yyvsp = yyval;

    /* Now 'shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


    /*--------------------------------------.
    | yyerrlab -- here on detecting error.  |
    `--------------------------------------*/
yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus)
    {
        ++yynerrs;
#if ! YYERROR_VERBOSE
        yyerror(YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
        {
            char const* yymsgp = YY_("syntax error");
            int yysyntax_error_status;
            yysyntax_error_status = YYSYNTAX_ERROR;
            if (yysyntax_error_status == 0)
                yymsgp = yymsg;
            else if (yysyntax_error_status == 1)
            {
                if (yymsg != yymsgbuf)
                    YYSTACK_FREE(yymsg);
                yymsg = (char*)YYSTACK_ALLOC(yymsg_alloc);
                if (!yymsg)
                {
                    yymsg = yymsgbuf;
                    yymsg_alloc = sizeof yymsgbuf;
                    yysyntax_error_status = 2;
                }
                else
                {
                    yysyntax_error_status = YYSYNTAX_ERROR;
                    yymsgp = yymsg;
                }
            }
            yyerror(yymsgp);
            if (yysyntax_error_status == 2)
                goto yyexhaustedlab;
        }
# undef YYSYNTAX_ERROR
#endif
    }



    if (yyerrstatus == 3)
    {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        if (yychar <= YYEOF)
        {
            /* Return failure if at end of input.  */
            if (yychar == YYEOF)
                YYABORT;
        }
        else
        {
            yydestruct("Error: discarding",
                yytoken, &yylval);
            yychar = YYEMPTY;
        }
    }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


    /*---------------------------------------------------.
    | yyerrorlab -- error raised explicitly by YYERROR.  |
    `---------------------------------------------------*/
yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (/*CONSTCOND*/ 0)
        goto yyerrorlab;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);
    yystate = *yyssp;
    goto yyerrlab1;


    /*-------------------------------------------------------------.
    | yyerrlab1 -- common code for both syntax error and YYERROR.  |
    `-------------------------------------------------------------*/
yyerrlab1:
    yyerrstatus = 3;      /* Each real token shifted decrements this.  */

    for (;;)
    {
        yyn = yypact[yystate];
        if (!yypact_value_is_default(yyn))
        {
            yyn += YYTERROR;
            if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
                yyn = yytable[yyn];
                if (0 < yyn)
                    break;
            }
        }

        /* Pop the current state because it cannot handle the error token.  */
        if (yyssp == yyss)
            YYABORT;


        yydestruct("Error: popping",
            yystos[yystate], yyvsp);
        YYPOPSTACK(1);
        yystate = *yyssp;
        YY_STACK_PRINT(yyss, yyssp);
    }

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
        * ++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END


        /* Shift the error token.  */
        YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

    yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
    /*-------------------------------------------------.
    | yyexhaustedlab -- memory exhaustion comes here.  |
    `-------------------------------------------------*/
yyexhaustedlab:
    yyerror(YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

yyreturn:
    if (yychar != YYEMPTY)
    {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE(yychar);
        yydestruct("Cleanup: discarding lookahead",
            yytoken, &yylval);
    }
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK(yylen);
    YY_STACK_PRINT(yyss, yyssp);
    while (yyssp != yyss)
    {
        yydestruct("Cleanup: popping",
            yystos[*yyssp], yyvsp);
        YYPOPSTACK(1);
    }
#ifndef yyoverflow
    if (yyss != yyssa)
        YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
    if (yymsg != yymsgbuf)
        YYSTACK_FREE(yymsg);
#endif
    return yyresult;
}
#line 1835 "ntp_parser.y" /* yacc.c:1906  */


void
yyerror(
    const char* msg
)
{
    int retval;
    struct FILE_INFO* ip_ctx;

    ip_ctx = lex_current();
    ip_ctx->errpos = ip_ctx->tokpos;

    msyslog(LOG_ERR, "line %d column %d %s",
        ip_ctx->errpos.nline, ip_ctx->errpos.ncol, msg);
    if (!lex_from_file()) {
        /* Save the error message in the correct buffer */
        retval = snprintf(remote_config.err_msg + remote_config.err_pos,
            sizeof remote_config.err_msg - remote_config.err_pos,
            "column %d %s",
            ip_ctx->errpos.ncol, msg);

        /* Increment the value of err_pos */
        if (retval > 0)
            remote_config.err_pos += retval;

        /* Increment the number of errors */
        ++remote_config.no_errors;
    }
}


/*
 * token_name - convert T_ token integers to text
 *		example: token_name(T_Server) returns "T_Server"
 */
const char*
token_name(
    int token
)
{
    return yytname[YYTRANSLATE(token)];
}


/* Initial Testing function -- ignore */
#if 0
int main(int argc, char* argv[])
{
    ip_file = FOPEN(argv[1], "r");
    if (!ip_file)
        fprintf(stderr, "ERROR!! Could not open file: %s\n", argv[1]);
    yyparse();
    return 0;
}
#endif
