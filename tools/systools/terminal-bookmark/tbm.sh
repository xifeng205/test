#!/usr/bin/env bash
# *******************************************************************
# * Author        : cuiyunpeng
# * Email         : @163.com
# * Create time   : 2020-08-02 06:29
# * Last modified : 2020-08-02 06:29
# * Filename      : tbm.sh
# * Description   : 
# *******************************************************************
bookmark_help() {
    echo [eg:[add], [del], [list], [move] [fuzzy]] 
}
add_bookmark_help() {
    echo [eg:[add], [del], [list], [move] [fuzzy]] 
}

del_bookmark_help() {
    echo [arg1:ln from] 
    echo [arg1:ln from] 
    echo [arg2:ln to] 
    echo [arg3:ln bias] 
}

move_bookmark_help() {
    echo [arg1:ln from] 
    echo [arg1:ln from] 
    echo [arg2:ln to] 
    echo [arg3:ln bias] 
   
}

list_bookmark_help() {
    echo [arg1:ln from] 
    echo [arg1:ln from] 
    echo [arg2:ln to] 
    echo [arg3:ln bias] 
}

add_bookmark() {
    if [ $1 \< '9' ] && [ $1 \> '0' ] || [ $1 = '0' ] || [ $1 = '9' ];then
         sed -i "/j$1=*/d" ~/.bash_aliases
         echo "alias j$1='cd $2'" >> /tmp/.bash_aliases 
         # alias c$1="cd $2"   
    elif [ $1 \> 'A' ] && [ $1 \< 'Z' ] || [ $1 = 'A' ] || [ $1 = 'Z' ];then 
        sed -i "/j$1=*/d" ~/.bash_aliases
        echo "alias j$1='cd $2'" >> ~/.bash_aliases  
    else
        echo "alias $1='$2 $3'" >> ~/.bash_boikdir    
    fi
}
del_bookmark() {
    case $1 in
        -p) sed -i "/j$1=*/d" ~/.bash_aliases;;
        -t) sed -i "/j$1=*/d" ~/.bash_aliases;; 
        -a) sed -i "/$1=*/d" ~/.bash_bookdir;; 
        -*) del_bookmark_help
    esac
}

remove_bookmark() {
    case $1 in
        -p) sed -i "/j$1=*/d" ~/.bash_aliases;;
        -t) sed -i "/j$1=*/d" ~/.bash_aliases;; 
        -a) sed -i "/$1=*/d" ~/.bash_bookdir;; 
        -*) del_bookmark_help
    esac

}

move_bookmark() {
    echo "No this function."  
}

list_bookmark() {
    case $1 in
        -p) 
            if [ -f  ~/.bash_aliases ];then
                cat ~/.bash_aliases
            fi
            ;;
        -t) 
            if [ -f  /tmp/.bash_aliases ];then
                cat /tmp/.bash_aliases
            fi
            ;;
        *) 
            if [ -f  ~/.bash_aliases ];then
                cat ~/.bash_aliases
            fi
            if [ -f  /tmp/.bash_aliases ];then
                cat /tmp/.bash_aliases
            fi
            ;;
    esac 
}

fuzzy_bookmark() {
    if [ -f  ~/.bash_aliases ];then
        cat ~/.bash_aliases
    fi
    if [ -f  ~/.bash_aliases ];then
        cat /tmp/.bash_aliases
    fi
}

main() {
    set -e 
    if [ -z $1 ];then 
        bookmark_help
        exit -1
    fi
    cmd=$1
   
    case $cmd in
        add) 
            if [ -z $2 ];then 
                echo Bookmark directory cannot be empty!!  
                exit -1
            fi
            bookdir_to=$2; bookdir_from=$3
            if [ -z $bookdir_from ];then 
                bookdir_from=$PWD
            fi
            add_bookmark $bookdir_to $bookdir_from;;
        del) del_bookmark $bookdir_to;;
        move) move_bookmark;;
        list) list_bookmark $2;;
        fuzzy) fuzzy_bookmark;;
        *)  bookmark_help;;
    esac
}    

#main function
main $1 $2 $3

