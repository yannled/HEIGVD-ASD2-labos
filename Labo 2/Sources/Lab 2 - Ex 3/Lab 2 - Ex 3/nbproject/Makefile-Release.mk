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
	${OBJECTDIR}/_ext/2060835113/GraphUsingAdjacencyLists.o \
	${OBJECTDIR}/_ext/2060835113/Util.o \
	${OBJECTDIR}/_ext/2060835113/ex3.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_3.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_3.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2060835113/GraphUsingAdjacencyLists.o: ../Lab\ 2\ -\ Ex\ 3/GraphUsingAdjacencyLists.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2060835113
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2060835113/GraphUsingAdjacencyLists.o ../Lab\ 2\ -\ Ex\ 3/GraphUsingAdjacencyLists.cpp

${OBJECTDIR}/_ext/2060835113/Util.o: ../Lab\ 2\ -\ Ex\ 3/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2060835113
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2060835113/Util.o ../Lab\ 2\ -\ Ex\ 3/Util.cpp

${OBJECTDIR}/_ext/2060835113/ex3.o: ../Lab\ 2\ -\ Ex\ 3/ex3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2060835113
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2060835113/ex3.o ../Lab\ 2\ -\ Ex\ 3/ex3.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lab_2_-_ex_3.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
