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
	${OBJECTDIR}/ConfigMgr.o \
	${OBJECTDIR}/ConnectionMgr.o \
	${OBJECTDIR}/ContextMap.o \
	${OBJECTDIR}/ContextMgr.o \
	${OBJECTDIR}/Dispatch.o \
	${OBJECTDIR}/Gate.o \
	${OBJECTDIR}/GlobalQueue.o \
	${OBJECTDIR}/LobbyServer.o \
	${OBJECTDIR}/MQueue.o \
	${OBJECTDIR}/MutexLock.o \
	${OBJECTDIR}/NameService.o \
	${OBJECTDIR}/ParseQueue.o \
	${OBJECTDIR}/SockServer.o \
	${OBJECTDIR}/SockStream.o \
	${OBJECTDIR}/Socket.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/ThreadBase.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pg
CXXFLAGS=-pg

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-llua

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../libs/Lobby

../libs/Lobby: ${OBJECTFILES}
	${MKDIR} -p ../libs
	${LINK.cc} -o ../libs/Lobby ${OBJECTFILES} ${LDLIBSOPTIONS} -lpthread -ldl -Wl,-E

${OBJECTDIR}/ConfigMgr.o: ConfigMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigMgr.o ConfigMgr.cpp

${OBJECTDIR}/ConnectionMgr.o: ConnectionMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConnectionMgr.o ConnectionMgr.cpp

${OBJECTDIR}/ContextMap.o: ContextMap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ContextMap.o ContextMap.cpp

${OBJECTDIR}/ContextMgr.o: ContextMgr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ContextMgr.o ContextMgr.cpp

${OBJECTDIR}/Dispatch.o: Dispatch.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Dispatch.o Dispatch.cpp

${OBJECTDIR}/Gate.o: Gate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gate.o Gate.cpp

${OBJECTDIR}/GlobalQueue.o: GlobalQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GlobalQueue.o GlobalQueue.cpp

${OBJECTDIR}/LobbyServer.o: LobbyServer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LobbyServer.o LobbyServer.cpp

${OBJECTDIR}/MQueue.o: MQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQueue.o MQueue.cpp

${OBJECTDIR}/MutexLock.o: MutexLock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MutexLock.o MutexLock.cpp

${OBJECTDIR}/NameService.o: NameService.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NameService.o NameService.cpp

${OBJECTDIR}/ParseQueue.o: ParseQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ParseQueue.o ParseQueue.cpp

${OBJECTDIR}/SockServer.o: SockServer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SockServer.o SockServer.cpp

${OBJECTDIR}/SockStream.o: SockStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SockStream.o SockStream.cpp

${OBJECTDIR}/Socket.o: Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Socket.o Socket.cpp

${OBJECTDIR}/Thread.o: Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/ThreadBase.o: ThreadBase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ThreadBase.o ThreadBase.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/utils.o: utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../LobbyLib -I../third -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils.o utils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../libs/Lobby

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
