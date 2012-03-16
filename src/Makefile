#
# OMNeT++/OMNEST Makefile for n_radix_switch
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = n_radix_switch$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IHost \
    -IHost/TrafficPatterns \
    -Iresults \
    -ISwitch \
    -ISwitch/RoutingAlgorithms

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = /src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Host/Host.o \
    $O/Host/TrafficPatterns/BitComplement.o \
    $O/Host/TrafficPatterns/BitReversal.o \
    $O/Host/TrafficPatterns/HotSpot.o \
    $O/Host/TrafficPatterns/Neighbour.o \
    $O/Host/TrafficPatterns/OtherTraffic.o \
    $O/Host/TrafficPatterns/Tornado.o \
    $O/Host/TrafficPatterns/TrafficPatterns.o \
    $O/Host/TrafficPatterns/Transpose.o \
    $O/Host/TrafficPatterns/Uniform.o \
    $O/Switch/Buffer.o \
    $O/Switch/inCtl.o \
    $O/Switch/inRegister.o \
    $O/Switch/Mux.o \
    $O/Switch/outCtl.o \
    $O/Switch/outPort.o \
    $O/Switch/RoutingAlgorithms/DOR.o \
    $O/Switch/RoutingAlgorithms/OtherRouting.o \
    $O/Switch/RoutingAlgorithms/RoutingAlgorithm.o \
    $O/Switch/RoutingAlgorithms/SourceTag.o \
    $O/Credit_m.o \
    $O/Flit_m.o \
    $O/Switch/Control_m.o

# Message files
MSGFILES = \
    Credit.msg \
    Flit.msg \
    Switch/Control.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f n_radix_switch n_radix_switch.exe libn_radix_switch.so libn_radix_switch.a libn_radix_switch.dll libn_radix_switch.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f Host/*_m.cc Host/*_m.h
	-rm -f Host/TrafficPatterns/*_m.cc Host/TrafficPatterns/*_m.h
	-rm -f results/*_m.cc results/*_m.h
	-rm -f Switch/*_m.cc Switch/*_m.h
	-rm -f Switch/RoutingAlgorithms/*_m.cc Switch/RoutingAlgorithms/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Host/*.cc Host/TrafficPatterns/*.cc results/*.cc Switch/*.cc Switch/RoutingAlgorithms/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Host/Host.o: Host/Host.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  Host/Host.h \
  ./Flit_m.h \
  ./Credit_m.h \
  Switch/common.h
$O/Host/TrafficPatterns/BitComplement.o: Host/TrafficPatterns/BitComplement.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/BitComplement.h
$O/Host/TrafficPatterns/BitReversal.o: Host/TrafficPatterns/BitReversal.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/BitReversal.h
$O/Host/TrafficPatterns/HotSpot.o: Host/TrafficPatterns/HotSpot.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/HotSpot.h
$O/Host/TrafficPatterns/Neighbour.o: Host/TrafficPatterns/Neighbour.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/Neighbour.h
$O/Host/TrafficPatterns/OtherTraffic.o: Host/TrafficPatterns/OtherTraffic.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/OtherTraffic.h
$O/Host/TrafficPatterns/Tornado.o: Host/TrafficPatterns/Tornado.cc \
  Host/TrafficPatterns/TrafficPatterns.h \
  ./Flit_m.h \
  Host/TrafficPatterns/Tornado.h
$O/Host/TrafficPatterns/TrafficPatterns.o: Host/TrafficPatterns/TrafficPatterns.cc \
  ./Flit_m.h \
  Host/TrafficPatterns/Transpose.h \
  Host/TrafficPatterns/BitComplement.h \
  Host/TrafficPatterns/BitReversal.h \
  Host/TrafficPatterns/HotSpot.h \
  Host/TrafficPatterns/OtherTraffic.h \
  Host/TrafficPatterns/TrafficPatterns.h \
  Host/TrafficPatterns/Uniform.h \
  Host/TrafficPatterns/Neighbour.h \
  Host/TrafficPatterns/Tornado.h
$O/Host/TrafficPatterns/Transpose.o: Host/TrafficPatterns/Transpose.cc \
  ./Flit_m.h \
  Host/TrafficPatterns/Transpose.h \
  Host/TrafficPatterns/TrafficPatterns.h
$O/Host/TrafficPatterns/Uniform.o: Host/TrafficPatterns/Uniform.cc \
  ./Flit_m.h \
  Host/TrafficPatterns/TrafficPatterns.h \
  Host/TrafficPatterns/Uniform.h
$O/Switch/Buffer.o: Switch/Buffer.cc \
  ./Flit_m.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/Buffer.h
$O/Switch/Mux.o: Switch/Mux.cc \
  ./Flit_m.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/Mux.h
$O/Switch/inCtl.o: Switch/inCtl.cc \
  ./Credit_m.h \
  ./Flit_m.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h \
  Switch/inCtl.h
$O/Switch/inRegister.o: Switch/inRegister.cc \
  ./Flit_m.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h \
  Switch/inRegister.h
$O/Switch/outCtl.o: Switch/outCtl.cc \
  ./Credit_m.h \
  ./Flit_m.h \
  Switch/outCtl.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h
$O/Switch/outPort.o: Switch/outPort.cc \
  ./Flit_m.h \
  Switch/common.h \
  Switch/Control_m.h \
  Switch/outPort.h
$O/Switch/RoutingAlgorithms/DOR.o: Switch/RoutingAlgorithms/DOR.cc \
  ./Flit_m.h \
  Switch/RoutingAlgorithms/DOR.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h
$O/Switch/RoutingAlgorithms/OtherRouting.o: Switch/RoutingAlgorithms/OtherRouting.cc \
  ./Flit_m.h \
  Switch/RoutingAlgorithms/OtherRouting.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h
$O/Switch/RoutingAlgorithms/RoutingAlgorithm.o: Switch/RoutingAlgorithms/RoutingAlgorithm.cc \
  ./Flit_m.h \
  Switch/RoutingAlgorithms/OtherRouting.h \
  Switch/RoutingAlgorithms/SourceTag.h \
  Switch/RoutingAlgorithms/DOR.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h
$O/Switch/RoutingAlgorithms/SourceTag.o: Switch/RoutingAlgorithms/SourceTag.cc \
  ./Flit_m.h \
  Switch/RoutingAlgorithms/SourceTag.h \
  Switch/RoutingAlgorithms/RoutingAlgorithm.h
