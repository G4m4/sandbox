#!/usr/bin/env python
'''
@file create_project.py
@brief Simple renaming script, create a project from the sandbox template
@author gm
@copyright gm 2014

This file is part of SandBox

SandBox is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SandBox is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SandBox.  If not, see <http://www.gnu.org/licenses/>.
'''

import os
import shutil
import string

kIgnoredDirectories = ('build',
                       '.git',
                       'scripts',
                       'gtest',
                       'juce'
                       )

def CopyRequiredFolders(sandbox_root, dest, name_lower):
    '''
    Recursive copy of everything found in "sandbox_root" into "dest",
    except file containing any of the element in kIgnoredDirectories

    @param    sandbox_root        Root of the template SandBox project
    @param    location        Destination of the created project
    @param    name_lower        Name (lower case) of the created project
    '''
    if os.path.exists(os.path.join(dest, name_lower)):
        return
    shutil.copytree(src = sandbox_root,
                    dst = os.path.join(dest, name_lower),
                    ignore = shutil.ignore_patterns(*kIgnoredDirectories))

def ScanFileAndRename(filepath, name, name_lower, name_upper):
    '''
    Scan through the input file and replace all occurrences of "SandBox"
    by the desired name

    Note that the name is case sensitive, e.g. these replacement will occur:
    SandBox -> NewProject (the given name)
    sandbox -> newproject
    SANDBOX -> NEWPROJECT

    @param    filepath        Path of the file  to scan through
    @param    name        Name (case sensitive) of the created project
    @param    name_lower        Lower-case version (may be different) of the created project
    @param    name_upper        Upper-case version (may be different) of the created project
    '''
    current_file = open(filepath, 'r+')
    temp_renamed = string.replace(current_file.read(),
                                  "SandBox", name).replace("sandbox", name_lower).replace("SANDBOX", name_upper)
    # Empty current file content and replace it
    current_file.seek(0)
    current_file.truncate()
    current_file.write(temp_renamed)

def WalkDirectoriesAndRename(root_dir, name, name_lower, name_upper):
    '''
    Walks through the copied project and rename all occurrences of "SandBox"
    to the desired name

    Note that the name is case sensitive, e.g. these replacement will occur:
    SandBox -> NewProject (the given name)
    sandbox -> newproject
    SANDBOX -> NEWPROJECT

    @param    root_dir        Root directory to walk into
    @param    name        Name (case sensitive) of the created project
    @param    name_lower        Lower-case version (may be different) of the created project
    @param    name_upper        Upper-case version (may be different) of the created project
    '''
    files_list = []
    for dir_head, filenames in [(dir_head, filenames) for dir_head, _, filenames in os.walk(root_dir)]:
        files_list.extend([os.path.join(dir_head, filename) for filename in filenames])
    # Two iterations done because os.walk gives list of lists...
    # TODO(gm): A better handling of that
    for filename in files_list:
        ScanFileAndRename(filename, name, name_lower, name_upper)

def RenameDirectories(root_dir, name_lower):
    '''
    Walks through the copied project and rename all folders named "SandBox"

    @param    root_dir        Root directory to walk into
    @param    name_lower        Name to replace folders with
    '''
    # This is hardcoded for now
    # TODO(gm): find something better
    shutil.move(os.path.join(root_dir, "sandbox"),
                os.path.join(root_dir, name_lower))

def SetupProject(sandbox_root, dest_dir, name):
    '''
    Create the entire directory hierarchy with all properly renamed
    file content from the SandBox template.

    @param    sandbox_root        Root directory to get the template from
    @param    dest_dir        Destination directory
    @param    name        Name (case sensitive) of the created project
    '''
    name_lower = name.lower()
    name_upper = name.upper()
    CopyRequiredFolders(sandbox_root, dest_dir, name_lower)
    project_path = os.path.join(dest_dir, name_lower)
    # Update files content
    WalkDirectoriesAndRename(project_path, name, name_lower, name_upper)
    # rename the folders themselves
    RenameDirectories(project_path, name_lower)

if __name__ == "__main__":
    import sys

    if len(sys.argv) < 4:
      raise Exception("Not enough arguments!")

    root_path = sys.argv[1]
    target_path = sys.argv[2]
    target_name = sys.argv[3]

    SetupProject(root_path, target_path, target_name)
