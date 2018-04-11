# @see http://google.github.io/styleguide/shell.xml
# @see http://tiswww.case.edu/php/chet/bash/FAQ
# @note Indent 2 spaces. No tabs.

# @note Start each file with a description of its contents.
#!/bin/bash

export PATH='/usr/xpg4/bin:/usr/bin:/opt/csw/bin:/opt/goog/bin'

# @note All caps, separated with underscores, declared at the top of the file.
#   Constants and anything exported to the environment should be capitalized.
readonly PATH_TO_FILES='/dir'   # constant
declare -xr ORCALE_SID='PROD'   # both constant and environment




# @note Use process substitution or for loops in preference to piping to while. 
#   Variables modified in a while loop do not propagate to the parent because the 
#   loop's commands run in a subshell.
#   The implicit subshell in a pipe to while can make it difficult to track down bugs.




# @note Any function that is not both obvious and short must be commented. 
#   Any function in a library must be commented regardless of length or complexity.
#   It should be possible for someone else to learn how to use your program or 
#   to use a function in your library by reading the comments (and self-help, 
#   if provided) without reading the code. All function comments should contain:
#       Description of the function
#       Global variables used and modified
#       Arguments taken
#       Returned values other than the default exit status of the last command run

#######################################
# Clean Tmp files
# Globals:
#   BACKUP_DIR
#   ORACLE_SID
# Arguments:
#   None
# Returns:
#   None
#######################################

# @note Lower-case, with underscores to separate words. Separate libraries with ::. 
#   Parentheses are required after the function name. The keyword function is 
#   optional, but must be used consistently throughout a project.
mypackage::clean_tmp() {
  while read f; do
    echo "file=${f}"
  done < <(ls -l /tmp)
}
#######################################
# Cleanup files from the backup dir
# Globals:
#   BACKUP_DIR
#   ORACLE_SID
# Arguments:
#   None
# Returns:
#   None
#######################################
cleanup() {
  for dir in ${dirs_to_cleanup}; do
    if [[ -d "${dir}/${ORACLE_SID}" ]]; then
      log_date "Cleaning up old files in ${dir}/${ORACLE_SID}"
      rm "${dir}/${ORACLE_SID}/"*
      if [[ "$?" -ne 0 ]]; then
        error_message
      fi
    else
      mkdir -p "${dir}/${ORACLE_SID}"
      if [[ "$?" -ne 0 ]]; then
        error_message
      fi
    fi
  done
}

# @note Use TODO comments for code that is temporary, a short-term solution, or good-enough but not perfect.
# TODO(mrmonkey): Handle the unlikely edge cases (bug ####)


# @note Pipelines should be split one per line if they don't all fit on one line.
# All fits on one line
command1 | command2

# Long commands
command1 \
  | command2 \
  | command3 \
  | command4


# @note all error messages should go to STDERR
err() {
  echo "[$(date + '%Y-%m-%dT%H:%S%z')]: $@" >&2
}

if [ ! mv "${file_list}" "${dest_dir}/" ]; then
  err "Unable to move $(file_list} to ${dest_dir}"
  # Always check return values and give informative return values.
  exit "${E_BAD_MOVE}"
fi