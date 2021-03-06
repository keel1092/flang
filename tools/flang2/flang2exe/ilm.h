/*
 * Copyright (c) 1993-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* ***  ILM Area  *****/

/* ILM_T is defined in gbldefs.h */

typedef struct {
  ILM_T *ilm_base; /* base pointer for ILM area */
  int ilm_size;    /* size in ILM_Ts of ILM area */
  int ilmavl;      /* relative ptr to next available word */
  int globalilmstart, globalilmcount;
} ILMB;

typedef struct {
  ILM_T *ilm_base;
  int ilm_size;
  int ilmavl;
  int ilmpos;
  int globalilmcount, globalilmstart, globalilmtotal, globalilmfirst;
} GILMB;

/* ***  ILM Attributes Declarations  *****/

typedef struct {
  char *name;
  char type;
  short oprs;
  unsigned int oprflag;
  short temps;
  short pattern;
  short ilict;
} ILMINFO;

#define BOS_SIZE 4

#define IMTY_ARTH 'a'
#define IMTY_BRANCH 'b'
#define IMTY_CONS 'c'
#define IMTY_FSTR 'f'
#define IMTY_LOAD 'l'
#define IMTY_MISC 'm'
#define IMTY_PROC 'p'
#define IMTY_REF 'r'
#define IMTY_STORE 's'
#define IMTY_TRANS 't'
#define IMTY_INTR 'i'
#define IMTY_SMP 'S'

#define ILMO_NULL 0
#define ILMO_R 1
#define ILMO_RR 2
#define ILMO_IR 3
#define ILMO_KR 4
#define ILMO_T 5
#define ILMO_V 6
#define ILMO_IV 7
#define ILMO_ISYM 8
#define ILMO_RSYM 9
#define ILMO_DSYM 10
#define ILMO_ESYM 11
#define ILMO_DR 12
#define ILMO_AR 13
#define ILMO_SP 14
#define ILMO_DP 15
#define ILMO_SZ 16
#define ILMO_SCZ 17
#define ILMO_SCF 18
#define ILMO_ISP 19
#define ILMO_IDP 20
#define ILMO_XRSYM 21
#define ILMO_XDSYM 22
#define ILMO__ESYM 23
#define ILMO_LSYM 24
#define ILMO_LLSYM 25
#define ILMO_DRRET 26
#define ILMO_ARRET 27
#define ILMO_SPRET 28
#define ILMO_DPRET 29
#define ILMO_KRRET 30
#define ILMO_DRPOS 31
#define ILMO_ARPOS 32
#define ILMO_SPPOS 33
#define ILMO_DPPOS 34

#define ILMO_P 1
#define ILMO_RP 2
#define ILMO_IP 3

#define OPR_LNK 0
#define OPR_SYM 1
#define OPR_STC 2
#define OPR_N 3

#define IM_TYPE(i) ilms[i].type
#define IM_OPRFLAG(i, opn) ((ilms[i].oprflag >> (opn - 1) * 2) & 3)
#define IM_SPEC(i) (ilms[i].oprflag & 0x80000000)
#define IM_TRM(i) (ilms[i].oprflag & 0x40000000)
#define IM_VAR(i) (ilms[i].oprflag & 0x20000000)
#define IM_VEC(i) (ilms[i].oprflag & 0x10000000)
#define IM_DCPLX(i) (ilms[i].oprflag & 0x08000000)
#define IM_I8(i) (ilms[i].oprflag & 0x04000000)
#define IM_X87CPLX(i) (ilms[i].oprflag & 0x02000000)
#define IM_NOINLC(i) (ilms[i].oprflag & 0x01000000)
#define IM_DOUBLEDOUBLECPLX(i) (ilms[i].oprflag & 0x00800000)
#define IM_FLOAT128CPLX(i) (ilms[i].oprflag & 0x00400000)

/* ***  ILM Template Declarations  *****/

typedef struct {
  short opc;
  short result;
  short opnd[1];
} ILMMAC;

typedef struct {
  short type;
  short aux;
} ILMOPND;

/* ***  ILM External Data Declarations  *****/

extern ILMB ilmb;       /*  defined in ilmutil.c  */
extern ILMINFO ilms[];  /*  defined in ilmtpdf.h  */
extern short ilmtp[];   /*  defined in ilmtpdf.h  */
extern short ilmopnd[]; /*  defined in ilmtpdf.h  */
extern char *ilmaux[];  /*  defined in ilmtpdf.h  */

/* for non array parameters, default set by attributes of the function
 */
#define BYVALDEFAULT(func) \
  (!(PASSBYREFG(func)) && (PASSBYVALG(func) | STDCALLG(func) | CFUNCG(func)))

void SaveGilms(FILE *fil);
void RestoreGilms(FILE *fil);
void init_global_ilm_position(void);
void reset_global_ilm_position(void);
void addlabel(int sptr);
void init_global_ilm_mode(void);
int rdgilms(int mode);

#ifdef ST_UNKNOWN /* Use ST_UNKNOWN to detect if SYMTYPE is defined. */

/** If a function returning a value of type ret_type needs
    to have a pointer to a temporary for possible use as
    as return slot, return the SYMTYPE for that temporary.
    Otherwise return ST_UNKNOWN.

    The result is a property of ILM, not the ABI. */
SYMTYPE
ilm_symtype_of_return_slot(DTYPE ret_type);

/** Determine if the ILM performs a call and the call has a
    pointer to a return slot.  If so, return the operand index
    of the slot.  Otherwise return 0.  Returns 0 for non-call ILMs. */
int ilm_return_slot_index(ILM_T *ilmp);

#endif

#ifdef N_ILM /* Use N_ILM to detect whether ILM_OP is defined */
/** Return index of callee for given operation, which must have type IMTY_PROC.
    index+k is the index for the kth argument.
    index-1 is the index of the dtype for the function signature if there is
   one.
  */
int ilm_callee_index(ILM_OP opc);

/** Check that ilmptr is plausibly a valid ILM index, and issue internal error
    with text if it is not.  Active only in DEBUG mode. */
#define ASSERT_IS_LNK(ilmptr, text)                                   \
  DEBUG_ASSERT((unsigned)(ilmptr)-1 < (unsigned)ilmb.ilmavl - 1 &&    \
                   (unsigned)(ilmb.ilm_base[ilmptr]) - 1 < N_ILM - 1, \
               (text))

#define ASSERT_IS_LABEL(labelptr, text) \
  DEBUG_ASSERT(STYPEG(labelptr) == ST_LABEL, (text))
#endif

void set_gilmb_mode(int mode);
