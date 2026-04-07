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
  void yyerror(const char *msg);

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
    T_Ntsdumpdir = 294,
    T_Ntsrefresh = 295,
    T_Drop = 296,
    T_Dscp = 297,
    T_Ellipsis = 298,
    T_Enable = 299,
    T_End = 300,
    T_Epeer = 301,
    T_False = 302,
    T_File = 303,
    T_Filegen = 304,
    T_Filenum = 305,
    T_Flag1 = 306,
    T_Flag2 = 307,
    T_Flag3 = 308,
    T_Flag4 = 309,
    T_Flake = 310,
    T_Floor = 311,
    T_Freq = 312,
    T_Fudge = 313,
    T_Fuzz = 314,
    T_Host = 315,
    T_Huffpuff = 316,
    T_Iburst = 317,
    T_Nts = 318,
    T_Ident = 319,
    T_Ignore = 320,
    T_Ignorehash = 321,
    T_Incalloc = 322,
    T_Incmem = 323,
    T_Initalloc = 324,
    T_Initmem = 325,
    T_Includefile = 326,
    T_Integer = 327,
    T_Interface = 328,
    T_Intrange = 329,
    T_Io = 330,
    T_Ippeerlimit = 331,
    T_Ipv4 = 332,
    T_Ipv4_flag = 333,
    T_Ipv6 = 334,
    T_Ipv6_flag = 335,
    T_Kernel = 336,
    T_Key = 337,
    T_Keys = 338,
    T_Keysdir = 339,
    T_Kod = 340,
    T_Leapfile = 341,
    T_Leapsmearinterval = 342,
    T_Limited = 343,
    T_Link = 344,
    T_Listen = 345,
    T_Logconfig = 346,
    T_Logfile = 347,
    T_Loopstats = 348,
    T_Lowpriotrap = 349,
    T_Manycastclient = 350,
    T_Manycastserver = 351,
    T_Mask = 352,
    T_Maxage = 353,
    T_Maxclock = 354,
    T_Maxdepth = 355,
    T_Maxdist = 356,
    T_Maxmem = 357,
    T_Maxpoll = 358,
    T_Mdnstries = 359,
    T_Mem = 360,
    T_Memlock = 361,
    T_Minclock = 362,
    T_Mindepth = 363,
    T_Mindist = 364,
    T_Minimum = 365,
    T_Minjitter = 366,
    T_Minpoll = 367,
    T_Minsane = 368,
    T_Mode = 369,
    T_Mode7 = 370,
    T_Monitor = 371,
    T_Month = 372,
    T_Mru = 373,
    T_Mssntp = 374,
    T_Multicastclient = 375,
    T_Nic = 376,
    T_Nolink = 377,
    T_Nomodify = 378,
    T_Nomrulist = 379,
    T_None = 380,
    T_Nonvolatile = 381,
    T_Noepeer = 382,
    T_Nopeer = 383,
    T_Noquery = 384,
    T_Noselect = 385,
    T_Noserve = 386,
    T_Notrap = 387,
    T_Notrust = 388,
    T_Ntp = 389,
    T_Ntpport = 390,
    T_NtpSignDsocket = 391,
    T_Orphan = 392,
    T_Orphanwait = 393,
    T_PCEdigest = 394,
    T_Panic = 395,
    T_Peer = 396,
    T_Peerstats = 397,
    T_Phone = 398,
    T_Pid = 399,
    T_Pidfile = 400,
    T_Poll = 401,
    T_PollSkewList = 402,
    T_Pool = 403,
    T_Port = 404,
    T_PpsData = 405,
    T_Preempt = 406,
    T_Prefer = 407,
    T_Protostats = 408,
    T_Pw = 409,
    T_Randfile = 410,
    T_Rawstats = 411,
    T_Refid = 412,
    T_Requestkey = 413,
    T_Reset = 414,
    T_Restrict = 415,
    T_Revoke = 416,
    T_Rlimit = 417,
    T_Saveconfigdir = 418,
    T_Server = 419,
    T_Serverresponse = 420,
    T_ServerresponseFuzz = 421,
    T_Setvar = 422,
    T_Source = 423,
    T_Stacksize = 424,
    T_Statistics = 425,
    T_Stats = 426,
    T_Statsdir = 427,
    T_Step = 428,
    T_Stepback = 429,
    T_Stepfwd = 430,
    T_Stepout = 431,
    T_Stratum = 432,
    T_String = 433,
    T_Sys = 434,
    T_Sysstats = 435,
    T_Tick = 436,
    T_Time1 = 437,
    T_Time2 = 438,
    T_TimeData = 439,
    T_Timer = 440,
    T_Timingstats = 441,
    T_Tinker = 442,
    T_Tos = 443,
    T_Trap = 444,
    T_True = 445,
    T_Trustedkey = 446,
    T_Ttl = 447,
    T_Type = 448,
    T_U_int = 449,
    T_UEcrypto = 450,
    T_UEcryptonak = 451,
    T_UEdigest = 452,
    T_Unconfig = 453,
    T_Unpeer = 454,
    T_Version = 455,
    T_WanderThreshold = 456,
    T_Week = 457,
    T_Wildcard = 458,
    T_Xleave = 459,
    T_Xmtnonce = 460,
    T_Year = 461,
    T_Flag = 462,
    T_EOC = 463,
    T_Simulate = 464,
    T_Beep_Delay = 465,
    T_Sim_Duration = 466,
    T_Server_Offset = 467,
    T_Duration = 468,
    T_Freq_Offset = 469,
    T_Wander = 470,
    T_Jitter = 471,
    T_Prop_Delay = 472,
    T_Proc_Delay = 473
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "ntp_parser.y" /* yacc.c:355  */

	char *			String;
	double			Double;
	int			Integer;
	unsigned		U_int;
	gen_fifo *		Generic_fifo;
	attr_val *		Attr_val;
	attr_val_fifo *		Attr_val_fifo;
	int_fifo *		Int_fifo;
	string_fifo *		String_fifo;
	address_node *		Address_node;
	address_fifo *		Address_fifo;
	setvar_node *		Set_var;
	server_info *		Sim_server;
	server_info_fifo *	Sim_server_fifo;
	script_info *		Sim_script;
	script_info_fifo *	Sim_script_fifo;

#line 379 "ntp_parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NTP_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 396 "ntp_parser.c" /* yacc.c:358  */

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
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
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
#define YYFINAL  231
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   723

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  225
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  118
/* YYNRULES -- Number of rules.  */
#define YYNRULES  353
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  475

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   473

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
     221,   222,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   220,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   223,   219,   224,     2,     2,     2,     2,
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
     215,   216,   217,   218
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   402,   402,   406,   407,   408,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   445,   455,   456,   457,   458,   459,   463,   464,   469,
     474,   476,   482,   483,   491,   492,   493,   497,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   515,   517,
     522,   523,   524,   525,   526,   527,   531,   536,   545,   555,
     556,   566,   568,   570,   572,   583,   590,   592,   597,   599,
     601,   603,   605,   615,   621,   622,   630,   632,   644,   645,
     646,   647,   648,   657,   662,   667,   675,   677,   679,   681,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   698,
     699,   708,   710,   719,   729,   734,   742,   743,   744,   745,
     746,   747,   748,   749,   754,   755,   763,   773,   782,   797,
     802,   803,   807,   808,   812,   813,   814,   815,   816,   817,
     818,   827,   831,   835,   843,   857,   871,   885,   894,   902,
     917,   918,   926,   927,   947,   948,   956,   967,   968,   969,
     970,   971,   972,   973,   974,   975,   976,   977,   978,   979,
     980,   981,   982,   983,   984,   988,   993,  1001,  1006,  1007,
    1008,  1012,  1017,  1025,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1045,  1055,  1060,  1068,  1070,  1072,  1081,  1083,
    1088,  1089,  1090,  1094,  1095,  1096,  1097,  1105,  1115,  1120,
    1128,  1133,  1134,  1142,  1147,  1152,  1160,  1165,  1166,  1167,
    1176,  1178,  1183,  1188,  1196,  1198,  1215,  1216,  1217,  1218,
    1219,  1220,  1224,  1225,  1226,  1227,  1228,  1229,  1237,  1242,
    1247,  1255,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1278,  1279,  1280,  1287,  1294,  1301,  1317,  1336,
    1344,  1346,  1348,  1350,  1352,  1354,  1356,  1358,  1360,  1367,
    1372,  1373,  1374,  1378,  1382,  1391,  1393,  1396,  1400,  1404,
    1405,  1406,  1410,  1421,  1439,  1452,  1467,  1479,  1492,  1493,
    1498,  1524,  1530,  1535,  1540,  1542,  1547,  1548,  1556,  1558,
    1566,  1571,  1579,  1604,  1611,  1621,  1622,  1626,  1627,  1628,
    1629,  1633,  1634,  1635,  1639,  1644,  1649,  1657,  1658,  1659,
    1660,  1661,  1662,  1663,  1673,  1678,  1686,  1691,  1699,  1701,
    1705,  1710,  1715,  1723,  1728,  1736,  1745,  1746,  1750,  1751,
    1755,  1763,  1781,  1785,  1790,  1798,  1803,  1804,  1808,  1813,
    1821,  1826,  1831,  1836,  1841,  1849,  1854,  1859,  1867,  1872,
    1873,  1874,  1875,  1876
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Abbrev", "T_Age", "T_All", "T_Allan",
  "T_Allpeers", "T_Auth", "T_Autokey", "T_Automax", "T_Average",
  "T_Basedate", "T_Bclient", "T_Bcpollbstep", "T_Beacon", "T_Broadcast",
  "T_Broadcastclient", "T_Broadcastdelay", "T_Burst", "T_Calibrate",
  "T_Ceiling", "T_Checkhash", "T_Clockstats", "T_Cohort", "T_ControlKey",
  "T_Crypto", "T_Cryptostats", "T_Ctl", "T_Day", "T_Default",
  "T_Delrestrict", "T_Device", "T_Digest", "T_Disable", "T_Discard",
  "T_Dispersion", "T_Double", "T_Driftfile", "T_Ntsdumpdir",
  "T_Ntsrefresh", "T_Drop", "T_Dscp", "T_Ellipsis", "T_Enable", "T_End",
  "T_Epeer", "T_False", "T_File", "T_Filegen", "T_Filenum", "T_Flag1",
  "T_Flag2", "T_Flag3", "T_Flag4", "T_Flake", "T_Floor", "T_Freq",
  "T_Fudge", "T_Fuzz", "T_Host", "T_Huffpuff", "T_Iburst", "T_Nts",
  "T_Ident", "T_Ignore", "T_Ignorehash", "T_Incalloc", "T_Incmem",
  "T_Initalloc", "T_Initmem", "T_Includefile", "T_Integer", "T_Interface",
  "T_Intrange", "T_Io", "T_Ippeerlimit", "T_Ipv4", "T_Ipv4_flag", "T_Ipv6",
  "T_Ipv6_flag", "T_Kernel", "T_Key", "T_Keys", "T_Keysdir", "T_Kod",
  "T_Leapfile", "T_Leapsmearinterval", "T_Limited", "T_Link", "T_Listen",
  "T_Logconfig", "T_Logfile", "T_Loopstats", "T_Lowpriotrap",
  "T_Manycastclient", "T_Manycastserver", "T_Mask", "T_Maxage",
  "T_Maxclock", "T_Maxdepth", "T_Maxdist", "T_Maxmem", "T_Maxpoll",
  "T_Mdnstries", "T_Mem", "T_Memlock", "T_Minclock", "T_Mindepth",
  "T_Mindist", "T_Minimum", "T_Minjitter", "T_Minpoll", "T_Minsane",
  "T_Mode", "T_Mode7", "T_Monitor", "T_Month", "T_Mru", "T_Mssntp",
  "T_Multicastclient", "T_Nic", "T_Nolink", "T_Nomodify", "T_Nomrulist",
  "T_None", "T_Nonvolatile", "T_Noepeer", "T_Nopeer", "T_Noquery",
  "T_Noselect", "T_Noserve", "T_Notrap", "T_Notrust", "T_Ntp", "T_Ntpport",
  "T_NtpSignDsocket", "T_Orphan", "T_Orphanwait", "T_PCEdigest", "T_Panic",
  "T_Peer", "T_Peerstats", "T_Phone", "T_Pid", "T_Pidfile", "T_Poll",
  "T_PollSkewList", "T_Pool", "T_Port", "T_PpsData", "T_Preempt",
  "T_Prefer", "T_Protostats", "T_Pw", "T_Randfile", "T_Rawstats",
  "T_Refid", "T_Requestkey", "T_Reset", "T_Restrict", "T_Revoke",
  "T_Rlimit", "T_Saveconfigdir", "T_Server", "T_Serverresponse",
  "T_ServerresponseFuzz", "T_Setvar", "T_Source", "T_Stacksize",
  "T_Statistics", "T_Stats", "T_Statsdir", "T_Step", "T_Stepback",
  "T_Stepfwd", "T_Stepout", "T_Stratum", "T_String", "T_Sys", "T_Sysstats",
  "T_Tick", "T_Time1", "T_Time2", "T_TimeData", "T_Timer", "T_Timingstats",
  "T_Tinker", "T_Tos", "T_Trap", "T_True", "T_Trustedkey", "T_Ttl",
  "T_Type", "T_U_int", "T_UEcrypto", "T_UEcryptonak", "T_UEdigest",
  "T_Unconfig", "T_Unpeer", "T_Version", "T_WanderThreshold", "T_Week",
  "T_Wildcard", "T_Xleave", "T_Xmtnonce", "T_Year", "T_Flag", "T_EOC",
  "T_Simulate", "T_Beep_Delay", "T_Sim_Duration", "T_Server_Offset",
  "T_Duration", "T_Freq_Offset", "T_Wander", "T_Jitter", "T_Prop_Delay",
  "T_Proc_Delay", "'|'", "'='", "'('", "')'", "'{'", "'}'", "$accept",
  "configuration", "command_list", "command", "server_command",
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
  "drift_parm", "refresh_parm", "dumpdir_parm", "pollskew_list",
  "pollskew_spec", "pollskew_cycle", "variable_assign",
  "t_default_or_zero", "trap_option_list", "trap_option",
  "log_config_list", "log_config_command", "interface_command",
  "interface_nic", "nic_rule_class", "nic_rule_action", "reset_command",
  "counter_set_list", "counter_set_keyword", "integer_list",
  "integer_list_range", "integer_list_range_elt", "integer_range",
  "string_list", "address_list", "boolean", "number", "basedate",
  "simulate_command", "sim_conf_start", "sim_init_statement_list",
  "sim_init_statement", "sim_init_keyword", "sim_server_list",
  "sim_server", "sim_server_offset", "sim_server_name", "sim_act_list",
  "sim_act", "sim_act_stmt_list", "sim_act_stmt", "sim_act_keyword", YY_NULLPTR
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
     465,   466,   467,   468,   469,   470,   471,   472,   473,   124,
      61,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF -255

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-255)))

#define YYTABLE_NINF -7

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,  -175,   -31,  -255,  -255,  -255,   -29,  -255,  -144,   -53,
     127,     6,  -126,  -123,    32,  -255,   127,  -255,   -12,   -53,
    -255,  -107,  -255,   -91,   -87,   -81,  -255,   -78,  -255,  -255,
     -53,    30,   430,   -53,  -255,  -255,   -68,  -255,   -51,  -255,
    -255,  -255,    37,     0,     2,    56,   -32,  -255,  -255,   -49,
     -12,   -44,  -255,   312,   585,   -42,   -69,    67,  -255,  -255,
    -255,   142,   246,   -65,  -255,   -53,  -255,   -53,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,   -15,
      78,   -22,   -19,  -255,    23,  -255,  -255,   -62,  -255,  -255,
    -255,    57,   -42,  -255,    65,  -255,  -255,  -119,  -255,   -11,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,   127,  -255,  -255,  -255,  -255,  -255,  -255,     6,
    -255,    91,   129,  -255,  -255,  -255,  -255,  -255,   127,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,   130,   431,
    -255,  -255,    18,  -255,   -78,  -255,  -255,   -53,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,   430,  -255,   100,
     -53,  -255,  -255,    15,    21,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,     0,  -255,   102,   166,   167,   102,    65,
    -255,  -255,  -255,  -255,   -32,  -255,   132,   -21,  -255,   -12,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,   312,  -255,   -15,    27,  -255,  -255,  -255,   -35,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,   585,  -255,
     134,   -15,  -255,  -255,  -255,   138,   -69,  -255,  -255,  -255,
     141,  -255,    20,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,    -1,  -103,  -255,  -255,  -255,
    -255,  -255,   157,  -255,    36,  -255,   -42,  -255,  -255,  -255,
    -119,  -255,    52,  -255,  -255,  -255,  -255,  -255,   -28,    54,
    -255,  -255,  -255,  -255,  -255,    55,   162,  -255,  -255,   130,
    -255,   -15,   -35,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,   163,  -255,   168,  -255,   102,
     102,  -255,   102,  -255,  -255,    60,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,   -60,   158,  -255,
    -255,  -255,   316,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -115,    31,    24,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,    68,  -255,  -255,     1,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,    26,  -255,   520,  -255,  -255,   520,
    -255,   217,   -42,   178,  -255,   179,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,   -63,  -255,    74,
      34,    47,  -141,  -255,    35,  -255,   -15,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,   185,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,   200,  -255,  -255,   520,   520,   520,
    -255,  -255,  -255,  -255,    38,  -255,  -255,  -255,   -53,  -255,
    -255,  -255,    53,  -255,  -255,  -255,  -255,  -255,    48,    61,
     -15,    49,  -174,  -255,    59,   -15,  -255,  -255,  -255,    50,
      85,  -255,  -255,  -255,  -255,  -255,     7,    71,    62,  -255,
      75,  -255,   -15,  -255,  -255
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,    25,    61,   260,     0,    74,     0,     0,
       0,     0,   274,   277,     0,   263,     0,   250,     0,     0,
     268,     0,   295,     0,     0,     0,   264,     0,   269,    26,
       0,     0,     0,     0,   296,   261,     0,    24,     0,   270,
     278,    23,     0,     0,     0,     0,     0,   271,    22,     0,
       0,     0,   262,     0,     0,     0,     0,     0,    59,    60,
     332,     0,     2,     0,     7,     0,     8,     0,     9,    10,
      13,    11,    12,    14,    20,    15,    16,    17,    18,     0,
       0,     0,     0,   242,     0,   243,    19,     0,     5,    65,
      66,    67,     0,    29,   140,    30,    31,     0,    27,     0,
     216,   217,   218,   219,   222,   220,   221,   223,   224,   225,
     226,   227,   211,   213,   214,   215,   168,   169,   170,   131,
     166,     0,   272,   251,   276,   253,   275,   252,   210,   106,
     107,   108,   109,   113,   110,   111,   112,   114,     0,     6,
      68,    69,   267,   292,   254,   291,   324,    62,    64,   174,
     175,   176,   177,   178,   179,   180,   181,   132,   172,     0,
      63,    73,   322,   255,   256,    70,   307,   308,   309,   310,
     311,   312,   313,   304,   306,   142,    30,    31,   142,   140,
      71,   209,   207,   208,   203,   205,     0,     0,   257,   101,
     105,   102,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   228,   230,     0,     0,    90,    91,    92,     0,
      93,    94,   100,    95,    99,    96,    97,    98,    83,    85,
       0,     0,    89,   286,   318,     0,    72,   317,   319,   315,
     259,     1,     0,     4,    32,    58,   329,   328,   244,   245,
     246,   247,   303,   302,   301,     0,     0,    82,    78,    79,
      80,    81,     0,    75,     0,   139,     0,   138,   202,   201,
     197,   199,     0,    28,   212,   165,   167,   273,   103,     0,
     193,   194,   195,   196,   192,     0,     0,   190,   191,   182,
     184,     0,     0,   248,   266,   265,   249,   290,   323,   171,
     173,   321,   282,   281,   279,     0,   305,     0,   144,   142,
     142,   144,   142,   204,   206,     0,   104,   229,   231,   330,
     327,   325,   326,    88,    84,    86,    87,   258,     0,   316,
     314,     3,    21,   297,   298,   299,   294,   300,   293,   336,
     337,     0,     0,     0,    77,    76,   141,   198,   200,   123,
     122,     0,   120,   121,     0,   115,   118,   119,   188,   189,
     187,   183,   185,   186,     0,   143,   134,   144,   144,   137,
     144,   285,     0,     0,   287,     0,    38,    39,    40,    41,
      57,    50,    52,    51,    54,    42,    43,    44,    45,    53,
      55,    46,    47,    33,    34,    37,    35,     0,    36,     0,
       0,     0,     0,   339,     0,   334,     0,   116,   130,   126,
     128,   124,   125,   127,   129,   117,     0,   164,   147,   148,
     149,   150,   151,   152,   153,   155,   156,   154,   157,   158,
     159,   160,   161,   162,     0,   163,   145,   135,   136,   133,
     284,   283,   289,   288,     0,    48,    49,    56,     0,   333,
     331,   338,     0,   335,   280,   146,   320,   342,     0,     0,
       0,     0,     0,   344,     0,     0,   340,   343,   341,     0,
       0,   349,   350,   351,   352,   353,     0,     0,     0,   345,
       0,   347,     0,   346,   348
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -255,  -255,  -255,   -41,  -255,  -255,    -9,    -7,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,    58,  -255,  -255,  -255,
    -255,   -36,  -255,  -255,  -255,  -255,  -255,  -255,    96,  -142,
    -254,  -255,  -255,   170,  -255,  -255,   135,  -255,  -255,  -255,
      14,  -255,  -255,  -255,  -255,    45,  -255,  -255,  -255,   110,
    -255,  -255,   280,   -86,  -255,  -255,  -255,  -255,    95,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,   164,  -255,  -255,
    -255,  -255,  -255,  -255,   133,  -255,  -255,    83,  -255,  -255,
     278,    33,  -202,  -255,  -255,  -255,  -255,   -17,  -255,  -255,
     -76,  -255,  -255,  -255,  -132,  -255,  -145,  -255
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    61,    62,    63,    64,    65,   146,    98,    99,   322,
     383,   384,   385,   386,   387,   388,   389,    66,    67,    68,
      69,    91,   253,   254,    70,   218,   219,   220,   221,    71,
     189,   137,   268,   345,   346,   347,   405,    72,   257,   298,
     356,   426,   119,   120,   121,   157,   158,   159,    73,   279,
     280,   281,   282,    74,   260,   261,   262,    75,   184,   185,
     186,    76,   112,   113,   114,   115,    77,   202,   203,   204,
      78,    79,    80,   286,    81,    82,   123,   127,   125,   164,
     294,   295,   188,   431,   317,   364,   144,   145,    83,    84,
     328,   245,    85,   173,   174,   230,   226,   227,   228,   163,
     147,   313,   238,   222,    86,    87,   331,   332,   333,   392,
     393,   449,   394,   452,   453,   466,   467,   468
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      97,    94,   308,   224,   323,   398,   339,   166,   167,   435,
     138,   129,   310,   362,   190,   130,   340,   116,   181,   316,
     341,   232,   236,   390,    92,    95,   264,    96,   168,     1,
     399,   258,   175,    88,    93,   179,   301,   311,     2,   451,
     284,    89,   264,    90,     3,     4,     5,   359,   223,   390,
     456,   292,   122,     6,     7,   124,   234,   237,   235,     8,
       9,   342,    10,    11,   242,   259,    12,    13,    14,   126,
      15,   139,    16,    17,   182,   169,   324,    18,   325,   352,
     176,   131,   177,   440,   285,   255,    19,   140,   243,   363,
     247,   141,    20,   293,   343,   329,   330,   142,   283,    21,
     143,    22,   148,   427,   428,   170,   429,   329,   330,   165,
     161,    23,    24,   244,    25,    26,   117,   248,   400,    27,
      28,   249,   118,    29,    30,    93,   401,   162,   180,   187,
     132,   436,    31,   269,   191,   100,    93,   183,   288,   229,
     101,   133,   231,   233,   134,   402,    32,   102,    33,    34,
     239,   288,   225,   306,    35,   312,   240,   357,   358,   241,
     360,   246,   256,   266,    36,   344,   267,   263,   135,    37,
     178,    38,   290,    39,   136,    40,    41,   326,   297,   171,
      93,   270,   271,   272,   273,   172,    42,    43,    44,    45,
      46,    47,    48,   291,   443,    49,   299,   300,    50,   305,
      51,   365,   327,   403,   304,   309,   315,   404,   103,    52,
     318,   250,   251,   320,   335,    53,    54,    55,   252,    56,
      57,   461,   462,   463,   464,   465,    58,    59,   321,   334,
     338,   469,   348,   349,   350,   354,    -6,    60,   361,   395,
     355,   274,   104,   105,   396,   406,   397,   430,   454,   336,
     433,   434,   437,   459,   438,   439,     2,   444,   442,   445,
     446,   106,     3,     4,     5,   448,   107,   458,   450,   455,
     474,     6,     7,   460,   451,   302,   314,     8,     9,   471,
      10,    11,   472,   473,    12,    13,    14,   275,    15,   265,
      16,    17,   289,   351,   303,    18,   128,   307,   108,   461,
     462,   463,   464,   465,    19,   337,   296,   276,   287,   319,
      20,   160,   277,   278,   391,   353,   441,    21,   192,    22,
     457,   470,   109,   110,   111,   366,     0,     0,     0,    23,
      24,     0,    25,    26,     0,   367,     0,    27,    28,     0,
       0,    29,    30,     0,     0,     0,     0,     0,   193,     0,
      31,     0,     0,     0,     0,   432,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,    33,    34,     0,   194,
       0,     0,    35,   195,     0,     0,     0,     0,   368,   369,
     370,     0,    36,     0,     0,     0,     0,    37,     0,    38,
       0,    39,     0,    40,    41,     0,     0,     0,   371,     0,
       0,     0,     0,     0,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,    50,     0,    51,   372,
       0,     0,     0,     0,     0,     0,     0,    52,   373,   447,
     374,     0,     0,    53,    54,    55,     0,    56,    57,     0,
       0,     2,     0,     0,    58,    59,   375,     3,     4,     5,
       0,     0,   196,     0,    -6,    60,     6,     7,     0,     0,
       0,     0,     8,     9,     0,    10,    11,   376,   377,    12,
      13,    14,     0,    15,     0,    16,    17,     0,     0,     0,
      18,     0,     0,     0,     0,   197,   198,   199,   200,    19,
       0,     0,     0,   201,     0,    20,     0,   149,   150,   151,
     152,     0,    21,     0,    22,     0,   378,     0,   379,     0,
       0,     0,     0,     0,    23,    24,   380,    25,    26,     0,
     381,   382,    27,    28,     0,     0,    29,    30,   153,     0,
     154,     0,   155,     0,     0,    31,     0,     0,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,    33,    34,     0,     0,     0,     0,    35,     0,     0,
     407,     0,     0,     0,     0,     0,   408,    36,     0,     0,
       0,     0,    37,     0,    38,   409,    39,     0,    40,    41,
       0,     0,     0,     0,     0,   410,     0,     0,     0,    42,
      43,    44,    45,    46,    47,    48,     0,   205,    49,   206,
     207,    50,     0,    51,     0,   411,   208,     0,   412,   209,
       0,     0,    52,     0,   413,     0,     0,     0,    53,    54,
      55,     0,    56,    57,     0,     0,     0,     0,     0,    58,
      59,     0,     0,     0,     0,     0,     0,     0,     0,   414,
      60,   210,     0,   415,   416,     0,     0,   417,   418,   419,
       0,   420,   421,   422,     0,   423,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   211,   424,   212,     0,     0,     0,
       0,     0,   213,     0,   214,     0,     0,     0,   215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     425,     0,   216,   217
};

static const yytype_int16 yycheck[] =
{
       9,     8,   204,    72,     5,     4,    34,     7,     8,    72,
      19,    23,    47,    73,    50,    27,    44,    11,    50,   221,
      48,    62,    37,   164,   168,    78,   112,    80,    28,     1,
      29,   150,    30,   208,   178,    44,   178,    72,    10,   213,
      22,    72,   128,    72,    16,    17,    18,   301,    55,   164,
     224,    30,   178,    25,    26,   178,    65,    72,    67,    31,
      32,    89,    34,    35,    41,   184,    38,    39,    40,    37,
      42,   178,    44,    45,   106,    75,    77,    49,    79,   281,
      78,    93,    80,   224,    66,    92,    58,   178,    65,   149,
      33,   178,    64,    72,   122,   210,   211,   178,   139,    71,
     178,    73,    72,   357,   358,   105,   360,   210,   211,    72,
     178,    83,    84,    90,    86,    87,   110,    60,   117,    91,
      92,    64,   116,    95,    96,   178,   125,   178,    72,   178,
     142,   194,   104,     3,   178,     8,   178,   169,   147,    72,
      13,   153,     0,   208,   156,   144,   118,    20,   120,   121,
      72,   160,   221,   189,   126,   190,   178,   299,   300,   178,
     302,   223,    97,    72,   136,   193,    37,   178,   180,   141,
     168,   143,    72,   145,   186,   147,   148,   178,    76,   179,
     178,    51,    52,    53,    54,   185,   158,   159,   160,   161,
     162,   163,   164,   178,   396,   167,    30,    30,   170,   220,
     172,    43,   203,   202,    72,   178,    72,   206,    81,   181,
      72,   154,   155,    72,   178,   187,   188,   189,   161,   191,
     192,   214,   215,   216,   217,   218,   198,   199,   208,    72,
     178,   224,   178,   178,    72,    72,   208,   209,   178,   208,
      72,   111,   115,   116,   220,   219,   178,    30,   450,   256,
      72,    72,   178,   455,   220,   208,    10,    72,   223,    59,
     222,   134,    16,    17,    18,   212,   139,   208,   220,   220,
     472,    25,    26,   223,   213,   179,   218,    31,    32,   208,
      34,    35,   220,   208,    38,    39,    40,   157,    42,   119,
      44,    45,   157,   279,   184,    49,    16,   202,   171,   214,
     215,   216,   217,   218,    58,   260,   173,   177,   144,   226,
      64,    33,   182,   183,   331,   282,   392,    71,     6,    73,
     452,   466,   195,   196,   197,     9,    -1,    -1,    -1,    83,
      84,    -1,    86,    87,    -1,    19,    -1,    91,    92,    -1,
      -1,    95,    96,    -1,    -1,    -1,    -1,    -1,    36,    -1,
     104,    -1,    -1,    -1,    -1,   362,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,    -1,   120,   121,    -1,    57,
      -1,    -1,   126,    61,    -1,    -1,    -1,    -1,    62,    63,
      64,    -1,   136,    -1,    -1,    -1,    -1,   141,    -1,   143,
      -1,   145,    -1,   147,   148,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,   158,   159,   160,   161,   162,   163,
     164,    -1,    -1,   167,    -1,    -1,   170,    -1,   172,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   181,   112,   438,
     114,    -1,    -1,   187,   188,   189,    -1,   191,   192,    -1,
      -1,    10,    -1,    -1,   198,   199,   130,    16,    17,    18,
      -1,    -1,   140,    -1,   208,   209,    25,    26,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,   151,   152,    38,
      39,    40,    -1,    42,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,   173,   174,   175,   176,    58,
      -1,    -1,    -1,   181,    -1,    64,    -1,    67,    68,    69,
      70,    -1,    71,    -1,    73,    -1,   190,    -1,   192,    -1,
      -1,    -1,    -1,    -1,    83,    84,   200,    86,    87,    -1,
     204,   205,    91,    92,    -1,    -1,    95,    96,    98,    -1,
     100,    -1,   102,    -1,    -1,   104,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
      -1,   120,   121,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,   136,    -1,    -1,
      -1,    -1,   141,    -1,   143,    55,   145,    -1,   147,   148,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,   158,
     159,   160,   161,   162,   163,   164,    -1,    12,   167,    14,
      15,   170,    -1,   172,    -1,    85,    21,    -1,    88,    24,
      -1,    -1,   181,    -1,    94,    -1,    -1,    -1,   187,   188,
     189,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     209,    56,    -1,   123,   124,    -1,    -1,   127,   128,   129,
      -1,   131,   132,   133,    -1,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   165,   101,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   109,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,    -1,   137,   138
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    10,    16,    17,    18,    25,    26,    31,    32,
      34,    35,    38,    39,    40,    42,    44,    45,    49,    58,
      64,    71,    73,    83,    84,    86,    87,    91,    92,    95,
      96,   104,   118,   120,   121,   126,   136,   141,   143,   145,
     147,   148,   158,   159,   160,   161,   162,   163,   164,   167,
     170,   172,   181,   187,   188,   189,   191,   192,   198,   199,
     209,   226,   227,   228,   229,   230,   242,   243,   244,   245,
     249,   254,   262,   273,   278,   282,   286,   291,   295,   296,
     297,   299,   300,   313,   314,   317,   329,   330,   208,    72,
      72,   246,   168,   178,   232,    78,    80,   231,   232,   233,
       8,    13,    20,    81,   115,   116,   134,   139,   171,   195,
     196,   197,   287,   288,   289,   290,    11,   110,   116,   267,
     268,   269,   178,   301,   178,   303,    37,   302,   287,    23,
      27,    93,   142,   153,   156,   180,   186,   256,   231,   178,
     178,   178,   178,   178,   311,   312,   231,   325,    72,    67,
      68,    69,    70,    98,   100,   102,   108,   270,   271,   272,
     325,   178,   178,   324,   304,    72,     7,     8,    28,    75,
     105,   179,   185,   318,   319,    30,    78,    80,   168,   231,
      72,    50,   106,   169,   283,   284,   285,   178,   307,   255,
     256,   178,     6,    36,    57,    61,   140,   173,   174,   175,
     176,   181,   292,   293,   294,    12,    14,    15,    21,    24,
      56,    99,   101,   107,   109,   113,   137,   138,   250,   251,
     252,   253,   328,   232,    72,   221,   321,   322,   323,    72,
     320,     0,   228,   208,   231,   231,    37,    72,   327,    72,
     178,   178,    41,    65,    90,   316,   223,    33,    60,    64,
     154,   155,   161,   247,   248,   232,    97,   263,   150,   184,
     279,   280,   281,   178,   288,   268,    72,    37,   257,     3,
      51,    52,    53,    54,   111,   157,   177,   182,   183,   274,
     275,   276,   277,   228,    22,    66,   298,   312,   231,   271,
      72,   178,    30,    72,   305,   306,   319,    76,   264,    30,
      30,   264,   263,   284,    72,   220,   256,   293,   327,   178,
      47,    72,   190,   326,   251,    72,   327,   309,    72,   322,
      72,   208,   234,     5,    77,    79,   178,   203,   315,   210,
     211,   331,   332,   333,    72,   178,   232,   280,   178,    34,
      44,    48,    89,   122,   193,   258,   259,   260,   178,   178,
      72,   275,   327,   326,    72,    72,   265,   264,   264,   265,
     264,   178,    73,   149,   310,    43,     9,    19,    62,    63,
      64,    82,   103,   112,   114,   130,   151,   152,   190,   192,
     200,   204,   205,   235,   236,   237,   238,   239,   240,   241,
     164,   332,   334,   335,   337,   208,   220,   178,     4,    29,
     117,   125,   144,   202,   206,   261,   219,    40,    46,    55,
      65,    85,    88,    94,   119,   123,   124,   127,   128,   129,
     131,   132,   133,   135,   165,   200,   266,   265,   265,   265,
      30,   308,   232,    72,    72,    72,   194,   178,   220,   208,
     224,   335,   223,   327,    72,    59,   222,   231,   212,   336,
     220,   213,   338,   339,   327,   220,   224,   339,   208,   327,
     223,   214,   215,   216,   217,   218,   340,   341,   342,   224,
     341,   208,   220,   208,   327
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   225,   226,   227,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   229,   230,   230,   230,   230,   230,   231,   231,   232,
     233,   233,   234,   234,   235,   235,   235,   236,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   238,   238,
     239,   239,   239,   239,   239,   239,   240,   241,   242,   243,
     243,   244,   244,   244,   244,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   246,   246,   247,   247,   248,   248,
     248,   248,   248,   249,   250,   250,   251,   251,   251,   251,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   253,
     253,   254,   254,   254,   255,   255,   256,   256,   256,   256,
     256,   256,   256,   256,   257,   257,   258,   258,   258,   258,
     259,   259,   260,   260,   261,   261,   261,   261,   261,   261,
     261,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     263,   263,   264,   264,   265,   265,   265,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   267,   267,   268,   269,   269,
     269,   270,   270,   271,   272,   272,   272,   272,   272,   272,
     272,   272,   273,   274,   274,   275,   275,   275,   275,   275,
     276,   276,   276,   277,   277,   277,   277,   278,   279,   279,
     280,   281,   281,   282,   283,   283,   284,   285,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   289,   289,
     289,   289,   290,   290,   290,   290,   290,   290,   291,   292,
     292,   293,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     296,   296,   296,   297,   297,   298,   298,   298,   299,   300,
     300,   300,   301,   301,   301,   302,   303,   303,   304,   304,
     305,   306,   306,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   313,   313,   314,   314,   315,   315,   315,
     315,   316,   316,   316,   317,   318,   318,   319,   319,   319,
     319,   319,   319,   319,   320,   320,   321,   321,   322,   322,
     323,   324,   324,   325,   325,   326,   326,   326,   327,   327,
     328,   329,   330,   331,   331,   332,   333,   333,   334,   334,
     335,   336,   337,   338,   338,   339,   340,   340,   341,   342,
     342,   342,   342,   342
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
       1,     1,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     1,
       2,     1,     1,     2,     2,     1,     2,     1,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     3,     3,
       1,     2,     2,     2,     2,     2,     2,     2,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     2,     0,     1,     1,     0,     0,     2,
       4,     1,     1,     4,     1,     0,     0,     2,     2,     2,
       2,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     1,     1,     1,
       5,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     5,     1,     3,     2,     3,     1,     1,     2,     1,
       5,     4,     3,     2,     1,     6,     3,     2,     3,     1,
       1,     1,     1,     1
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
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
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

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
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
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
      if (!yypact_value_is_default (yyn))
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
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
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
yyparse (void)
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
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

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
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 409 "ntp_parser.y" /* yacc.c:1646  */
    {
			/* I will need to incorporate much more fine grained
			 * error messages. The following should suffice for
			 * the time being.
			 */
			struct FILE_INFO * ip_ctx = lex_current();
			msyslog(LOG_ERR,
				"syntax error in %s line %d, column %d",
				ip_ctx->fname,
				ip_ctx->errpos.nline,
				ip_ctx->errpos.ncol);
		}
#line 2004 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 446 "ntp_parser.y" /* yacc.c:1646  */
    {
			peer_node *my_node;

			my_node = create_peer_node((yyvsp[-2].Integer), (yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
			APPEND_G_FIFO(cfgt.peers, my_node);
		}
#line 2015 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 465 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = create_address_node((yyvsp[0].String), (yyvsp[-1].Integer)); }
#line 2021 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 470 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = create_address_node((yyvsp[0].String), AF_UNSPEC); }
#line 2027 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 475 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = AF_INET; }
#line 2033 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 477 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = AF_INET6; }
#line 2039 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 482 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2045 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 484 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2054 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 498 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2060 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 516 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2066 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 518 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_uval((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2072 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 532 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2078 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 546 "ntp_parser.y" /* yacc.c:1646  */
    {
			unpeer_node *my_node;

			my_node = create_unpeer_node((yyvsp[0].Address_node));
			if (my_node)
				APPEND_G_FIFO(cfgt.unpeers, my_node);
		}
#line 2090 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 567 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.broadcastclient = 1; }
#line 2096 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 569 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.manycastserver, (yyvsp[0].Address_fifo)); }
#line 2102 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 571 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.multicastclient, (yyvsp[0].Address_fifo)); }
#line 2108 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 573 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.mdnstries = (yyvsp[0].Integer); }
#line 2114 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 584 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *atrv;

			atrv = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
			APPEND_G_FIFO(cfgt.vars, atrv);
		}
#line 2125 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 591 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.control_key = (yyvsp[0].Integer); }
#line 2131 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 593 "ntp_parser.y" /* yacc.c:1646  */
    {
			cfgt.auth.cryptosw++;
			CONCAT_G_FIFOS(cfgt.auth.crypto_cmd_list, (yyvsp[0].Attr_val_fifo));
		}
#line 2140 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 598 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.keys = (yyvsp[0].String); }
#line 2146 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 600 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.keysdir = (yyvsp[0].String); }
#line 2152 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 602 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.request_key = (yyvsp[0].Integer); }
#line 2158 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 604 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.revoke = (yyvsp[0].Integer); }
#line 2164 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 606 "ntp_parser.y" /* yacc.c:1646  */
    {
			/* [Bug 948] leaves it open if appending or
			 * replacing the trusted key list is the right
			 * way. In any case, either alternative should
			 * be coded correctly!
			 */
			DESTROY_G_FIFO(cfgt.auth.trusted_key_list, destroy_attr_val); /* remove for append */
			CONCAT_G_FIFOS(cfgt.auth.trusted_key_list, (yyvsp[0].Attr_val_fifo));
		}
#line 2178 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 616 "ntp_parser.y" /* yacc.c:1646  */
    { cfgt.auth.ntp_signd_socket = (yyvsp[0].String); }
#line 2184 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 621 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2190 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 623 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2199 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 631 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2205 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 633 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val) = NULL;
			cfgt.auth.revoke = (yyvsp[0].Integer);
			msyslog(LOG_WARNING,
				"'crypto revoke %d' is deprecated, "
				"please use 'revoke %d' instead.",
				cfgt.auth.revoke, cfgt.auth.revoke);
		}
#line 2218 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 658 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.orphan_cmds, (yyvsp[0].Attr_val_fifo)); }
#line 2224 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 663 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2233 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 668 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2242 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 676 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (double)(yyvsp[0].Integer)); }
#line 2248 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 678 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2254 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 680 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (double)(yyvsp[0].Integer)); }
#line 2260 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 682 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Basedate, (yyvsp[0].Integer)); }
#line 2266 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 709 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.stats_list, (yyvsp[0].Int_fifo)); }
#line 2272 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 711 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				cfgt.stats_dir = (yyvsp[0].String);
			} else {
				YYFREE((yyvsp[0].String));
				yyerror("statsdir remote configuration ignored");
			}
		}
#line 2285 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 720 "ntp_parser.y" /* yacc.c:1646  */
    {
			filegen_node *fgn;

			fgn = create_filegen_node((yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo));
			APPEND_G_FIFO(cfgt.filegen_opts, fgn);
		}
#line 2296 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 730 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Int_fifo) = (yyvsp[-1].Int_fifo);
			APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 2305 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 735 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Int_fifo) = NULL;
			APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 2314 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 754 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2320 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 756 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2329 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 764 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				(yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
			} else {
				(yyval.Attr_val) = NULL;
				YYFREE((yyvsp[0].String));
				yyerror("filegen file remote config ignored");
			}
		}
#line 2343 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 774 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				(yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
			} else {
				(yyval.Attr_val) = NULL;
				yyerror("filegen type remote config ignored");
			}
		}
#line 2356 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 783 "ntp_parser.y" /* yacc.c:1646  */
    {
			const char *err;

			if (lex_from_file()) {
				(yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer));
			} else {
				(yyval.Attr_val) = NULL;
				if (T_Link == (yyvsp[0].Integer))
					err = "filegen link remote config ignored";
				else
					err = "filegen nolink remote config ignored";
				yyerror(err);
			}
		}
#line 2375 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 798 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2381 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 828 "ntp_parser.y" /* yacc.c:1646  */
    {
			CONCAT_G_FIFOS(cfgt.discard_opts, (yyvsp[0].Attr_val_fifo));
		}
#line 2389 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 832 "ntp_parser.y" /* yacc.c:1646  */
    {
			CONCAT_G_FIFOS(cfgt.mru_opts, (yyvsp[0].Attr_val_fifo));
		}
#line 2397 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 836 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *rn;

			rn = create_restrict_node((yyvsp[-3].Address_node), (yyvsp[-2].Address_node), (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
						  lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2409 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 844 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *rn;

			APPEND_G_FIFO((yyvsp[0].Attr_val_fifo), create_attr_ival((yyvsp[-2].Integer), 1));
			rn = create_restrict_node(
				create_address_node(
					estrdup(keyword((yyvsp[-2].Integer))),
					AF_UNSPEC),
				NULL,
				(yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
				lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2427 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 858 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *rn;

			APPEND_G_FIFO((yyvsp[0].Attr_val_fifo), create_attr_ival((yyvsp[-2].Integer), 1));
			rn = create_restrict_node(
				create_address_node(
					estrdup("-4 default"),
					AF_INET),
				NULL,
				(yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
				lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2445 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 872 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *rn;

			APPEND_G_FIFO((yyvsp[0].Attr_val_fifo), create_attr_ival((yyvsp[-2].Integer), 1));
			rn = create_restrict_node(
				create_address_node(
					estrdup("-6 default"),
					AF_INET6),
				NULL,
				(yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
				lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2463 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 137:
#line 886 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *	rn;

			APPEND_G_FIFO((yyvsp[0].Attr_val_fifo), create_attr_ival((yyvsp[-2].Integer), 1));
			rn = create_restrict_node(NULL, NULL, (yyvsp[-1].Integer), (yyvsp[0].Attr_val_fifo), FALSE,
						  lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2476 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 138:
#line 895 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *	rn;

			rn = create_restrict_node((yyvsp[-1].Address_node), (yyvsp[0].Address_node), -1, NULL, TRUE,
						  lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2488 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 903 "ntp_parser.y" /* yacc.c:1646  */
    {
			restrict_node *	rn;
			attr_val_fifo * avf;

			avf = NULL;
			APPEND_G_FIFO(avf, create_attr_ival((yyvsp[-1].Integer), 1));
			rn = create_restrict_node((yyvsp[0].Address_node), NULL, -1, avf, TRUE,
						  lex_current()->curpos.nline);
			APPEND_G_FIFO(cfgt.restrict_opts, rn);
		}
#line 2503 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 917 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = NULL; }
#line 2509 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 919 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Address_node) = (yyvsp[0].Address_node);
		}
#line 2517 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 142:
#line 926 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = -1; }
#line 2523 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 928 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (((yyvsp[0].Integer) < -1) || ((yyvsp[0].Integer) > 100)) {
				struct FILE_INFO * ip_ctx;

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
#line 2543 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 947 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 2549 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 949 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			av = create_attr_ival((yyvsp[0].Integer), 1);
			APPEND_G_FIFO((yyval.Attr_val_fifo), av);
		}
#line 2561 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 957 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			(yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
			av = create_attr_ival(T_ServerresponseFuzz, 1);
			APPEND_G_FIFO((yyval.Attr_val_fifo), av);
		}
#line 2573 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 989 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2582 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 994 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2591 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1002 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2597 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1013 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2606 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1018 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2615 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1026 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2621 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1046 "ntp_parser.y" /* yacc.c:1646  */
    {
			addr_opts_node *aon;

			aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
			APPEND_G_FIFO(cfgt.fudge, aon);
		}
#line 2632 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1056 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2641 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1061 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2650 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1069 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2656 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1071 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2662 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1073 "ntp_parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].Integer) >= 0 && (yyvsp[0].Integer) <= 16) {
				(yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
			} else {
				(yyval.Attr_val) = NULL;
				yyerror("fudge factor: stratum value not in [0..16], ignored");
			}
		}
#line 2675 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1082 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2681 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1084 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2687 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1106 "ntp_parser.y" /* yacc.c:1646  */
    {
			addr_opts_node *aon;

			aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
			APPEND_G_FIFO(cfgt.device, aon);
		}
#line 2698 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1116 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2707 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1121 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2716 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1129 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String)); }
#line 2722 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1143 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.rlimit, (yyvsp[0].Attr_val_fifo)); }
#line 2728 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1148 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2737 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1153 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2746 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1161 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 2752 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1177 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.enable_opts, (yyvsp[0].Attr_val_fifo)); }
#line 2758 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1179 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.disable_opts, (yyvsp[0].Attr_val_fifo)); }
#line 2764 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1184 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2773 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1189 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2782 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1197 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer)); }
#line 2788 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1199 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				(yyval.Attr_val) = create_attr_ival(T_Flag, (yyvsp[0].Integer));
			} else {
				char err_str[128];

				(yyval.Attr_val) = NULL;
				snprintf(err_str, sizeof(err_str),
					 "enable/disable %s remote configuration ignored",
					 keyword((yyvsp[0].Integer)));
				yyerror(err_str);
			}
		}
#line 2806 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1238 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.tinker, (yyvsp[0].Attr_val_fifo)); }
#line 2812 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1243 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2821 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1248 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 2830 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1256 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double)); }
#line 2836 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1281 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			av = create_attr_dval((yyvsp[-1].Integer), (yyvsp[0].Double));
			APPEND_G_FIFO(cfgt.vars, av);
		}
#line 2847 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1288 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			av = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer));
			APPEND_G_FIFO(cfgt.vars, av);
		}
#line 2858 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1295 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			av = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
			APPEND_G_FIFO(cfgt.vars, av);
		}
#line 2869 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1302 "ntp_parser.y" /* yacc.c:1646  */
    {
			char error_text[64];
			attr_val *av;

			if (lex_from_file()) {
				av = create_attr_sval((yyvsp[-1].Integer), (yyvsp[0].String));
				APPEND_G_FIFO(cfgt.vars, av);
			} else {
				YYFREE((yyvsp[0].String));
				snprintf(error_text, sizeof(error_text),
					 "%s remote config ignored",
					 keyword((yyvsp[-1].Integer)));
				yyerror(error_text);
			}
		}
#line 2889 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 248:
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
			} else {
				const char * path = FindConfig((yyvsp[-1].String)); /* might return $2! */
				if (!lex_push_file(path, "r")) {
					fprintf(stderr, "getconfig: Couldn't open <%s>\n", path);
					msyslog(LOG_ERR, "getconfig: Couldn't open <%s>", path);
				}
			}
			YYFREE((yyvsp[-1].String)); /* avoid leak */
		}
#line 2912 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1337 "ntp_parser.y" /* yacc.c:1646  */
    {
			attr_val *av;

			av = create_attr_sval((yyvsp[-2].Integer), (yyvsp[-1].String));
			av->flag = (yyvsp[0].Integer);
			APPEND_G_FIFO(cfgt.vars, av);
		}
#line 2924 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1345 "ntp_parser.y" /* yacc.c:1646  */
    { lex_flush_stack(); }
#line 2930 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1347 "ntp_parser.y" /* yacc.c:1646  */
    { /* see drift_parm below for actions */ }
#line 2936 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1349 "ntp_parser.y" /* yacc.c:1646  */
    { /* see refresh below for actions */ }
#line 2942 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1351 "ntp_parser.y" /* yacc.c:1646  */
    { /* see dumpdir_parm below for actions */ }
#line 2948 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1353 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.logconfig, (yyvsp[0].Attr_val_fifo)); }
#line 2954 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1355 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.phone, (yyvsp[0].String_fifo)); }
#line 2960 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1357 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.pollskewlist, (yyvsp[0].Attr_val_fifo)); }
#line 2966 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1359 "ntp_parser.y" /* yacc.c:1646  */
    { APPEND_G_FIFO(cfgt.setvar, (yyvsp[0].Set_var)); }
#line 2972 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1361 "ntp_parser.y" /* yacc.c:1646  */
    {
			addr_opts_node *aon;

			aon = create_addr_opts_node((yyvsp[-1].Address_node), (yyvsp[0].Attr_val_fifo));
			APPEND_G_FIFO(cfgt.trap, aon);
		}
#line 2983 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1368 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.ttl, (yyvsp[0].Attr_val_fifo)); }
#line 2989 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1383 "ntp_parser.y" /* yacc.c:1646  */
    {
#ifndef LEAP_SMEAR
			yyerror("Built without LEAP_SMEAR support.");
#endif
		}
#line 2999 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1392 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = FALSE; }
#line 3005 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1394 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = TRUE; }
#line 3011 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1396 "ntp_parser.y" /* yacc.c:1646  */
    {  (yyval.Integer) = TRUE; }
#line 3017 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1411 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				attr_val *av;
				av = create_attr_sval(T_Driftfile, (yyvsp[0].String));
				APPEND_G_FIFO(cfgt.vars, av);
			} else {
				YYFREE((yyvsp[0].String));
				yyerror("driftfile remote configuration ignored");
			}
		}
#line 3032 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1422 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				attr_val *av;
				av = create_attr_sval(T_Driftfile, (yyvsp[-1].String));
				APPEND_G_FIFO(cfgt.vars, av);
				av = create_attr_dval(T_WanderThreshold, (yyvsp[0].Double));
				APPEND_G_FIFO(cfgt.vars, av);
				msyslog(LOG_WARNING,
					"'driftfile FILENAME WanderValue' is deprecated, "
					"please use separate 'driftfile FILENAME' and "
					"'nonvolatile WanderValue' lines instead.");
			} else {
				YYFREE((yyvsp[-1].String));
				yyerror("driftfile remote configuration ignored");
			}
		}
#line 3053 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1439 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				attr_val *av;
				av = create_attr_sval(T_Driftfile, estrdup(""));
				APPEND_G_FIFO(cfgt.vars, av);
			} else {
				yyerror("driftfile remote configuration ignored");
			}
		}
#line 3067 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1453 "ntp_parser.y" /* yacc.c:1646  */
    {
                        if (lex_from_file()) {
                                attr_val *av;
                                av = create_attr_dval(T_Ntsrefresh, (yyvsp[0].Double));
                                APPEND_G_FIFO(cfgt.vars, av);
                        } /*else {
                                YYFREE($1);
                                yyerror("ntsrefresh remote configuration ignored");
                        }*/
                }
#line 3082 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1468 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				attr_val *av;
				av = create_attr_sval(T_Ntsdumpdir, (yyvsp[0].String));
				APPEND_G_FIFO(cfgt.vars, av);
			} else {
				YYFREE((yyvsp[0].String));
				yyerror("ntsdumpdir remote configuration ignored");
			}
		}
#line 3097 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1479 "ntp_parser.y" /* yacc.c:1646  */
    {
			if (lex_from_file()) {
				attr_val *av;
				av = create_attr_sval(T_Ntsdumpdir, estrdup(""));
				APPEND_G_FIFO(cfgt.vars, av);
			} else {
				yyerror("ntsdumpdir remote configuration ignored");
			}
		}
#line 3111 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1492 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 3117 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1494 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = append_gen_fifo((yyvsp[-1].Attr_val_fifo), (yyvsp[0].Attr_val)); }
#line 3123 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1499 "ntp_parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[-2].Integer) < 0 || (yyvsp[0].Integer) < 0) {
				/* bad numbers */
				yyerror("pollskewlist: skew values must be >=0");
				destroy_attr_val((yyvsp[-3].Attr_val));
				(yyvsp[-3].Attr_val) = NULL;
			} else if ((yyvsp[-3].Attr_val) == NULL) {
				yyerror("pollskewlist: poll value must be 3-17, inclusive");
			} else if ((yyvsp[-3].Attr_val)->attr <= 0) {
				/* process default range */
				(yyvsp[-3].Attr_val)->value.r.first = (yyvsp[-2].Integer);
				(yyvsp[-3].Attr_val)->value.r.last  = (yyvsp[0].Integer);
			} else if ((yyvsp[-2].Integer) < (1 << ((yyvsp[-3].Attr_val)->attr - 1)) && (yyvsp[0].Integer) < (1 << ((yyvsp[-3].Attr_val)->attr - 1))) {
				(yyvsp[-3].Attr_val)->value.r.first = (yyvsp[-2].Integer);
				(yyvsp[-3].Attr_val)->value.r.last  = (yyvsp[0].Integer);
			} else {
				yyerror("pollskewlist: randomization limit must be <= half the poll interval");
				destroy_attr_val((yyvsp[-3].Attr_val));
				(yyvsp[-3].Attr_val) = NULL;
			}
			(yyval.Attr_val) = (yyvsp[-3].Attr_val);
		}
#line 3150 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1525 "ntp_parser.y" /* yacc.c:1646  */
    { 
			(yyval.Attr_val) = ((yyvsp[0].Integer) >= NTP_MINPOLL && (yyvsp[0].Integer) <= NTP_MAXPOLL) 
				? create_attr_rval((yyvsp[0].Integer), 0, 0) 
				: NULL;
		}
#line 3160 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1530 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_rval(-1, 0, 0); }
#line 3166 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1536 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Set_var) = create_setvar_node((yyvsp[-3].String), (yyvsp[-1].String), (yyvsp[0].Integer)); }
#line 3172 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1542 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 0; }
#line 3178 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1547 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val_fifo) = NULL; }
#line 3184 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1549 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 3193 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1557 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival((yyvsp[-1].Integer), (yyvsp[0].Integer)); }
#line 3199 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1559 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val) = create_attr_sval((yyvsp[-1].Integer), estrdup((yyvsp[0].Address_node)->address));
			destroy_address_node((yyvsp[0].Address_node));
		}
#line 3208 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1567 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 3217 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1572 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 3226 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1580 "ntp_parser.y" /* yacc.c:1646  */
    {
			char	prefix;
			char *	type;

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
#line 3252 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1605 "ntp_parser.y" /* yacc.c:1646  */
    {
			nic_rule_node *nrn;

			nrn = create_nic_rule_node((yyvsp[-2].Integer), (yyvsp[0].Integer), NULL, (yyvsp[-1].Integer));
			APPEND_G_FIFO(cfgt.nic_rules, nrn);
		}
#line 3263 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1612 "ntp_parser.y" /* yacc.c:1646  */
    {
			nic_rule_node *nrn;

			nrn = create_nic_rule_node((yyvsp[-2].Integer), 0, (yyvsp[0].String), (yyvsp[-1].Integer));
			APPEND_G_FIFO(cfgt.nic_rules, nrn);
		}
#line 3274 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1640 "ntp_parser.y" /* yacc.c:1646  */
    { CONCAT_G_FIFOS(cfgt.reset_counters, (yyvsp[0].Int_fifo)); }
#line 3280 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1645 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Int_fifo) = (yyvsp[-1].Int_fifo);
			APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 3289 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1650 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Int_fifo) = NULL;
			APPEND_G_FIFO((yyval.Int_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 3298 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1674 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 3307 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1679 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), create_int_node((yyvsp[0].Integer)));
		}
#line 3316 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1687 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-1].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 3325 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1692 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[0].Attr_val));
		}
#line 3334 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1700 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_ival('i', (yyvsp[0].Integer)); }
#line 3340 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1706 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_rval('-', (yyvsp[-3].Integer), (yyvsp[-1].Integer)); }
#line 3346 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1711 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.String_fifo) = (yyvsp[-1].String_fifo);
			APPEND_G_FIFO((yyval.String_fifo), create_string_node((yyvsp[0].String)));
		}
#line 3355 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1716 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.String_fifo) = NULL;
			APPEND_G_FIFO((yyval.String_fifo), create_string_node((yyvsp[0].String)));
		}
#line 3364 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1724 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Address_fifo) = (yyvsp[-1].Address_fifo);
			APPEND_G_FIFO((yyval.Address_fifo), (yyvsp[0].Address_node));
		}
#line 3373 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1729 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Address_fifo) = NULL;
			APPEND_G_FIFO((yyval.Address_fifo), (yyvsp[0].Address_node));
		}
#line 3382 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1737 "ntp_parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].Integer) != 0 && (yyvsp[0].Integer) != 1) {
				yyerror("Integer value is not boolean (0 or 1). Assuming 1");
				(yyval.Integer) = 1;
			} else {
				(yyval.Integer) = (yyvsp[0].Integer);
			}
		}
#line 3395 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1745 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 1; }
#line 3401 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1746 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = 0; }
#line 3407 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1750 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Double) = (double)(yyvsp[0].Integer); }
#line 3413 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1756 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Integer) = basedate_eval_string((yyvsp[0].String)); YYFREE((yyvsp[0].String)); }
#line 3419 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1764 "ntp_parser.y" /* yacc.c:1646  */
    {
			sim_node *sn;

			sn =  create_sim_node((yyvsp[-2].Attr_val_fifo), (yyvsp[-1].Sim_server_fifo));
			APPEND_G_FIFO(cfgt.sim_details, sn);

			/* Revert from ; to \n for end-of-command */
			old_config_style = 1;
		}
#line 3433 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1781 "ntp_parser.y" /* yacc.c:1646  */
    { old_config_style = 0; }
#line 3439 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1786 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
		}
#line 3448 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1791 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
		}
#line 3457 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1799 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-2].Integer), (yyvsp[0].Double)); }
#line 3463 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1809 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Sim_server_fifo) = (yyvsp[-1].Sim_server_fifo);
			APPEND_G_FIFO((yyval.Sim_server_fifo), (yyvsp[0].Sim_server));
		}
#line 3472 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1814 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Sim_server_fifo) = NULL;
			APPEND_G_FIFO((yyval.Sim_server_fifo), (yyvsp[0].Sim_server));
		}
#line 3481 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1822 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Sim_server) = ONLY_SIM(create_sim_server((yyvsp[-4].Address_node), (yyvsp[-2].Double), (yyvsp[-1].Sim_script_fifo))); }
#line 3487 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1827 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Double) = (yyvsp[-1].Double); }
#line 3493 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1832 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Address_node) = (yyvsp[0].Address_node); }
#line 3499 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1837 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Sim_script_fifo) = (yyvsp[-1].Sim_script_fifo);
			APPEND_G_FIFO((yyval.Sim_script_fifo), (yyvsp[0].Sim_script));
		}
#line 3508 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1842 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Sim_script_fifo) = NULL;
			APPEND_G_FIFO((yyval.Sim_script_fifo), (yyvsp[0].Sim_script));
		}
#line 3517 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1850 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Sim_script) = ONLY_SIM(create_sim_script_info((yyvsp[-3].Double), (yyvsp[-1].Attr_val_fifo))); }
#line 3523 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1855 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = (yyvsp[-2].Attr_val_fifo);
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
		}
#line 3532 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1860 "ntp_parser.y" /* yacc.c:1646  */
    {
			(yyval.Attr_val_fifo) = NULL;
			APPEND_G_FIFO((yyval.Attr_val_fifo), (yyvsp[-1].Attr_val));
		}
#line 3541 "ntp_parser.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1868 "ntp_parser.y" /* yacc.c:1646  */
    { (yyval.Attr_val) = create_attr_dval((yyvsp[-2].Integer), (yyvsp[0].Double)); }
#line 3547 "ntp_parser.c" /* yacc.c:1646  */
    break;


#line 3551 "ntp_parser.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
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
          yydestruct ("Error: discarding",
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
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1879 "ntp_parser.y" /* yacc.c:1906  */


void
yyerror(
	const char *msg
	)
{
	int retval;
	struct FILE_INFO * ip_ctx;

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
const char *
token_name(
	int token
	)
{
	return yytname[YYTRANSLATE(token)];
}


/* Initial Testing function -- ignore */
#if 0
int main(int argc, char *argv[])
{
	ip_file = FOPEN(argv[1], "r");
	if (!ip_file)
		fprintf(stderr, "ERROR!! Could not open file: %s\n", argv[1]);
	yyparse();
	return 0;
}
#endif

