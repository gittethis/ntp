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
/* Tokens.  */
#define T_Abbrev 258
#define T_Age 259
#define T_All 260
#define T_Allan 261
#define T_Allpeers 262
#define T_Auth 263
#define T_Autokey 264
#define T_Automax 265
#define T_Average 266
#define T_Basedate 267
#define T_Bclient 268
#define T_Bcpollbstep 269
#define T_Beacon 270
#define T_Broadcast 271
#define T_Broadcastclient 272
#define T_Broadcastdelay 273
#define T_Burst 274
#define T_Calibrate 275
#define T_Ceiling 276
#define T_Checkhash 277
#define T_Clockstats 278
#define T_Cohort 279
#define T_ControlKey 280
#define T_Crypto 281
#define T_Cryptostats 282
#define T_Ctl 283
#define T_Day 284
#define T_Default 285
#define T_Delrestrict 286
#define T_Device 287
#define T_Digest 288
#define T_Disable 289
#define T_Discard 290
#define T_Dispersion 291
#define T_Double 292
#define T_Driftfile 293
#define T_Drop 294
#define T_Dscp 295
#define T_Ellipsis 296
#define T_Enable 297
#define T_End 298
#define T_Epeer 299
#define T_False 300
#define T_File 301
#define T_Filegen 302
#define T_Filenum 303
#define T_Flag1 304
#define T_Flag2 305
#define T_Flag3 306
#define T_Flag4 307
#define T_Flake 308
#define T_Floor 309
#define T_Freq 310
#define T_Fudge 311
#define T_Fuzz 312
#define T_Host 313
#define T_Huffpuff 314
#define T_Iburst 315
#define T_Nts 316
#define T_Ident 317
#define T_Ignore 318
#define T_Ignorehash 319
#define T_Incalloc 320
#define T_Incmem 321
#define T_Initalloc 322
#define T_Initmem 323
#define T_Includefile 324
#define T_Integer 325
#define T_Interface 326
#define T_Intrange 327
#define T_Io 328
#define T_Ippeerlimit 329
#define T_Ipv4 330
#define T_Ipv4_flag 331
#define T_Ipv6 332
#define T_Ipv6_flag 333
#define T_Kernel 334
#define T_Key 335
#define T_Keys 336
#define T_Keysdir 337
#define T_Kod 338
#define T_Leapfile 339
#define T_Leapsmearinterval 340
#define T_Limited 341
#define T_Link 342
#define T_Listen 343
#define T_Logconfig 344
#define T_Logfile 345
#define T_Loopstats 346
#define T_Lowpriotrap 347
#define T_Manycastclient 348
#define T_Manycastserver 349
#define T_Mask 350
#define T_Maxage 351
#define T_Maxclock 352
#define T_Maxdepth 353
#define T_Maxdist 354
#define T_Maxmem 355
#define T_Maxpoll 356
#define T_Mdnstries 357
#define T_Mem 358
#define T_Memlock 359
#define T_Minclock 360
#define T_Mindepth 361
#define T_Mindist 362
#define T_Minimum 363
#define T_Minjitter 364
#define T_Minpoll 365
#define T_Minsane 366
#define T_Mode 367
#define T_Mode7 368
#define T_Monitor 369
#define T_Month 370
#define T_Mru 371
#define T_Mssntp 372
#define T_Multicastclient 373
#define T_Nic 374
#define T_Nolink 375
#define T_Nomodify 376
#define T_Nomrulist 377
#define T_None 378
#define T_Nonvolatile 379
#define T_Noepeer 380
#define T_Nopeer 381
#define T_Noquery 382
#define T_Noselect 383
#define T_Noserve 384
#define T_Notrap 385
#define T_Notrust 386
#define T_Ntp 387
#define T_Ntpport 388
#define T_NtpSignDsocket 389
#define T_Orphan 390
#define T_Orphanwait 391
#define T_PCEdigest 392
#define T_Panic 393
#define T_Peer 394
#define T_Peerstats 395
#define T_Phone 396
#define T_Pid 397
#define T_Pidfile 398
#define T_Poll 399
#define T_PollSkewList 400
#define T_Pool 401
#define T_Port 402
#define T_PpsData 403
#define T_Preempt 404
#define T_Prefer 405
#define T_Protostats 406
#define T_Pw 407
#define T_Randfile 408
#define T_Rawstats 409
#define T_Refid 410
#define T_Requestkey 411
#define T_Reset 412
#define T_Restrict 413
#define T_Revoke 414
#define T_Rlimit 415
#define T_Saveconfigdir 416
#define T_Server 417
#define T_Serverresponse 418
#define T_ServerresponseFuzz 419
#define T_Setvar 420
#define T_Source 421
#define T_Stacksize 422
#define T_Statistics 423
#define T_Stats 424
#define T_Statsdir 425
#define T_Step 426
#define T_Stepback 427
#define T_Stepfwd 428
#define T_Stepout 429
#define T_Stratum 430
#define T_String 431
#define T_Sys 432
#define T_Sysstats 433
#define T_Tick 434
#define T_Time1 435
#define T_Time2 436
#define T_TimeData 437
#define T_Timer 438
#define T_Timingstats 439
#define T_Tinker 440
#define T_Tos 441
#define T_Trap 442
#define T_True 443
#define T_Trustedkey 444
#define T_Ttl 445
#define T_Type 446
#define T_U_int 447
#define T_UEcrypto 448
#define T_UEcryptonak 449
#define T_UEdigest 450
#define T_Unconfig 451
#define T_Unpeer 452
#define T_Version 453
#define T_WanderThreshold 454
#define T_Week 455
#define T_Wildcard 456
#define T_Xleave 457
#define T_Xmtnonce 458
#define T_Year 459
#define T_Flag 460
#define T_EOC 461
#define T_Simulate 462
#define T_Beep_Delay 463
#define T_Sim_Duration 464
#define T_Server_Offset 465
#define T_Duration 466
#define T_Freq_Offset 467
#define T_Wander 468
#define T_Jitter 469
#define T_Prop_Delay 470
#define T_Proc_Delay 471

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

#line 505 "ntp_parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NTP_PARSER_H_INCLUDED  */
