#
# Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

########## Make rule for test fe87  ########


fe87: fe87.$(OBJX)
	

fe87.$(OBJX):  $(SRC)/fe87.f90
	-$(RM) fe87.$(EXESUFFIX) core *.d *.mod FOR*.DAT FTN* ftn* fort.*
	@echo ------------------------------------ building test $@
	-$(CC) -c $(CFLAGS) $(SRC)/check.c -o check.$(OBJX)
	-$(FC) -c $(FFLAGS) $(LDFLAGS) $(SRC)/fe87.f90 -o fe87.$(OBJX)
	-$(FC) $(FFLAGS) $(LDFLAGS) fe87.$(OBJX) check.$(OBJX) $(LIBS) -o fe87.$(EXESUFFIX)


fe87.run: fe87.$(OBJX)
	@echo ------------------------------------ executing test fe87
	fe87.$(EXESUFFIX)

run: fe87.$(OBJX)
	@echo ------------------------------------ executing test fe87
	fe87.$(EXESUFFIX)
build:	fe87.$(OBJX)
verify:	;
