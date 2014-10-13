#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2060835112/GraphFromImage.o \
	${OBJECTDIR}/_ext/2060835112/ex2.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_2.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_2.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2060835112/GraphFromImage.o: ../Lab\ 2\ -\ Ex\ 2/GraphFromImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2060835112
	${RM} $@.d
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2060835112/GraphFromImage.o ../Lab\ 2\ -\ Ex\ 2/GraphFromImage.cpp

${OBJECTDIR}/_ext/2060835112/ex2.o: ../Lab\ 2\ -\ Ex\ 2/ex2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2060835112
	${RM} $@.d
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2060835112/ex2.o ../Lab\ 2\ -\ Ex\ 2/ex2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_2.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
