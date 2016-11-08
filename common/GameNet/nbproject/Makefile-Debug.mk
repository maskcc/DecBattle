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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DataBuffer.o \
	${OBJECTDIR}/IOComponent.o \
	${OBJECTDIR}/IOStream.o \
	${OBJECTDIR}/NetWork.o \
	${OBJECTDIR}/ServerSocket.o \
	${OBJECTDIR}/Socket.o \
	${OBJECTDIR}/Thread.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=-lutils -lpthread

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a

${OBJECTDIR}/DataBuffer.o: DataBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataBuffer.o DataBuffer.cpp

${OBJECTDIR}/IOComponent.o: IOComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IOComponent.o IOComponent.cpp

${OBJECTDIR}/IOStream.o: IOStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IOStream.o IOStream.cpp

${OBJECTDIR}/NetWork.o: NetWork.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NetWork.o NetWork.cpp

${OBJECTDIR}/ServerSocket.o: ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServerSocket.o ServerSocket.cpp

${OBJECTDIR}/Socket.o: Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Socket.o Socket.cpp

${OBJECTDIR}/Thread.o: Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Utils -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Thread.o Thread.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgamenet.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
