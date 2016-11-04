# Copyright AllSeen Alliance. All rights reserved.
#
#    Permission to use, copy, modify, and/or distribute this software for any
#    purpose with or without fee is hereby granted, provided that the above
#    copyright notice and this permission notice appear in all copies.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
# 

# This python file contains all the utility functions used by SConstruct and SConscript.

import os

def enum(**enums):
    return type('Enum', (), enums)

EventLevel = enum(error = 'ERROR', 
                  warning = 'WARNING', 
                  info = 'INFO', 
                  verbose = 'VERBOSE')
                  
utilityName = 'Utility'
    
def PrintOneLineLog(eventLevel, sconComponent, logStr):
    print '[{0}] {1}: {2}'.format(eventLevel, sconComponent, logStr)

def GetDefaultPathFromEnvironVar(component, envName):
    defaultPath = os.environ.get(envName)
    if defaultPath:
        PrintOneLineLog(EventLevel.info, utilityName, 
            'The default {0} path is given by {1}: {2}.'.format(component, envName, defaultPath))
    else:
        PrintOneLineLog(EventLevel.error, utilityName, 
            'The default {0} path is not found because the environment variable {1} is not defined.'.format(component, envName))
    return defaultPath

def PrintBuildArguments(component, argumentType, argumentValueList):
    PrintOneLineLog(EventLevel.info, utilityName, 
        'The {0} for {1} are:'.format(argumentType, component))
    for argumentValue in argumentValueList:
        PrintOneLineLog(EventLevel.info, utilityName, '\t{0}'.format(str(argumentValue)))

def ReplacePathSeparators(path):
    return path.replace('/', os.sep)
                
def PrintAlljoynEnv(env):
    PrintOneLineLog(EventLevel.info, utilityName, 'Related AllJoyn core build options:')
    PrintOneLineLog(EventLevel.info, utilityName, 'OS = {0}'.format(str(env['OS'])))
    PrintOneLineLog(EventLevel.info, utilityName, 'CPU = {0}'.format(str(env['CPU'])))
    PrintOneLineLog(EventLevel.info, utilityName, 'TARGET_ARCH = {0}'.format(str(env['TARGET_ARCH'])))
    if env['OS'] == 'win7':
        PrintOneLineLog(EventLevel.info, utilityName, 'MSVC_VERSION = {0}'.format(str(env['MSVC_VERSION'])))
    PrintOneLineLog(EventLevel.info, utilityName, 'VARIANT = {0}'.format(str(env['VARIANT'])))
    PrintOneLineLog(EventLevel.info, utilityName, 'WS = {0}'.format(str(env['WS'])))
    PrintOneLineLog(EventLevel.info, utilityName, 'CPPDEFINES = ')
    for defineMacro in env['CPPDEFINES']:
        PrintOneLineLog(EventLevel.info, utilityName, '\t{0}'.format(str(defineMacro)))
    
def IsBuildSupported(env):
    # Currently we only support the 64-bit build on Linux and Windows.
    if (env['OS'] == 'linux') or (env['OS'] == 'win7'):
        return env['CPU'] == 'x86_64'
    else:
        return False
