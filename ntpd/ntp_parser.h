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
#line 52 "ntp_parser.y" /* yacc.c:1909  */

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

#line 292 "ntp_parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NTP_PARSER_H_INCLUDED  */
