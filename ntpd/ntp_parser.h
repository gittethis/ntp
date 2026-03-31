/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 52 "ntp_parser.y" /* yacc.c:1909  */

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

#line 290 "ntp_parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_NTP_PARSER_H_INCLUDED  */
