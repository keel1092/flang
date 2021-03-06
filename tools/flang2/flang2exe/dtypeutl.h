/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
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

#ifndef DTYPEUTL_H_
#define DTYPEUTL_H_

#include "gbldefs.h"
#include "error.h"
#include "global.h"
#include "symtab.h"
#include <stdio.h>

/**
   \brief ...
 */
ISZ_T ad_val_of(int sym);

/**
   \brief ...
 */
ISZ_T extent_of(DTYPE dtype);

/// \brief Given a constant symbol, return its numerical value.
ISZ_T get_bnd_cval(int con);

/**
   \brief ...
 */
ISZ_T size_of(DTYPE dtype);

/**
   \brief ...
 */
ISZ_T size_of_sym(SPTR sym);

/**
   \brief ...
 */
ISZ_T zsize_of(DTYPE dtype);

/**
 * \brief Return true if the data types for two functions are compatible.
 *
 * Two functions are compatible if a single local variable can be used to hold
 * their return values and therefore implying that the same return mechanism can
 * be used for the functions.
 *
 */
bool cmpat_func(int d1, int d2);

/**
   \brief ...
 */
bool is_array_dtype(DTYPE dtype);

/** Check for special case of empty typedef which has a size of 0
 * but one member of type DT_NONE to indicate that the type is
 * empty and not incomplete, a forward reference, etc.
 */
bool is_empty_typedef(DTYPE dtype);

/**
   \brief ...
 */
bool no_data_components(DTYPE dtype);

/**
   \brief ...
 */
DTYPE array_element_dtype(DTYPE dtype);

/**
   \brief ...
 */
DTYPE get_array_dtype(int numdim, DTYPE eltype);

/**
   \brief ...
 */
DTYPE get_type(int n, TY_KIND v1, int v2);

/**
   \brief ...
 */
DTYPE get_vector_dtype(DTYPE dtype, int n);

/**
   \brief ...
 */
int alignment(DTYPE dtype);

/**
   \brief ...
 */
int alignment_sym(SPTR sym);

/**
   \brief Support the alignof operator
   \param dtype
 */
int align_of(int dtype);

/**
   \brief ...
 */
int align_unconstrained(DTYPE dtype);

/**
   \brief Return the length
   \param dty
   Length, in stb.dt_base words, of each type of datatype entry
 */
int dlen(TY_KIND dty);

/**
   \brief ...
 */
int dmp_dent(int dtypeind);

/**
   \brief ...
 */
int _dmp_dent(int dtypeind, FILE *outfile);

/**
 * \brief Get FVAL field of a data type
 * \return 0 if reg, 1 if mem.
 */
int fval_of(DTYPE dtype);

/**
   \brief Create a constant sym entry which reflects the type of an array
   bound/extent.
 */
int get_bnd_con(ISZ_T v);

/**
   \brief Extract necessary bytes from character string in order to return
   integer (16-bit) representation of one kanji char.
   \param p the character string
   \param len number of bytes in string p
   \return number of EUC bytes used up
 */
int kanji_char(unsigned char *p, int len, int *bytes);

/**
   \brief Get number of kanji characters
   \param length Length in bytes of character string
 */
int kanji_len(unsigned char *p, int len);

/**
 * \brief Get number of bytes needed for kanji characters in string prefix
 * \param p ptr to EUC string
 * \param newlen number of kanji chars required from string prefix
 * \param len total number of bytes in string
 * \return number of bytes required for newlen chars
 */
int kanji_prefix(unsigned char *p, int newlen, int len);

/**
 * \brief Compute the size of a data type
 * \param dtype
 * \param size    number of elements in the data type [output]
 * \return number of bytes in each element, expressed as a power of two (scale)
 *
 * This machine dependent routine computes the size of a data type in terms of
 * two quantities: the size and the scale
 *
 *  This routine will be used to take advantage of the machines that
 *  have the ability to add a scaled expression (multiplied by a power
 *  of two) to an address.  This is particularly useful for incrementing
 *  a pointer variable and array subscripting.
 *
 *  Note that for those machines that do not have this feature, scale_of
 *  returns a scale of 0 and size_of for size.
 */
int Scale_Of(DTYPE dtype, ISZ_T *size);

/**
   \brief ...
 */
int scale_of(int dtype, INT *size);

/**
   \brief ...
 */
void dmp_dtype(void);

/**
 * \brief Put into the character array pointed to by ptr, the print
 * representation of dtype.
 */
void getdtype(DTYPE dtype, char *ptr);

/**
   \brief ...
 */
void init_chartab(void);

/**
   \brief ...
 */
void Restore_Chartab(FILE *fil);

/**
   \brief ...
 */
void Save_Chartab(FILE *fil);

#endif
