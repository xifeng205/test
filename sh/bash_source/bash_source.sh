 #!/bin/bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-05-14 15:08
# * Last modified : 2020-05-14 15:08
# * Filename      : bash_source.sh
# * Description   : 
# *******************************************************************
# echo ${BASH_SOURCE[0]}
#
# function test_func()
# {
#     echo "Current $FUNCNAME, \$FUNCNAME => (${FUNCNAME[@]})"
#     another_func
#    echo "Current $FUNCNAME, \$FUNCNAME => (${FUNCNAME[@]})"
# }

# function another_func()
#  {
#      echo "Current $FUNCNAME, \$FUNCNAME => (${FUNCNAME[@]})"
#  }
#
# echo "Out of function, \$FUNCNAME => (${FUNCNAME[@]})"
# test_func
# echo "Out of # If the script is sourced by another script
#  function, \$FUNCNAME => (${FUNCNAME[@]})"

# if [ -n "$BASH_SOURCE" -a "$BASH_SOURCE" != "$0" ]
# then
#     echo    $BASH_SOURCE 
# else # Otherwise, run directly in the shell
#     echo do_other
#     echo    $BASH_SOURCE 
# fi
#
# if [ -n "" -o "2d" ]
# then
#     echo   idsfif  
# else # Otherwise, run directly in the shell
#     echo do_other
# fi

# echo ${BASH_SOURCE[0]}
 DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../" && pwd )"
 echo $DIR
 echo "ok"

