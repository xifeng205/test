
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    uid_t my_uid;
    //my_uid =500;
    struct passwd *my_info;
    my_info =getpwuid(0);
    //my_info = getpwnam( "fflg" );
    printf( "my name = [%s]\n", my_info->pw_name );
    printf( "my passwd = [%s]\n", my_info->pw_passwd );
    printf( "my uid = [%d]\n", my_info->pw_uid );
    printf( "my gid = [%d]\n", my_info->pw_gid );
    printf( "my gecos = [%s]\n", my_info->pw_gecos );
    printf( "my dir = [%s]\n", my_info->pw_dir );
    printf( "my shell = [%s]\n", my_info->pw_shell );
    return 0;
}
