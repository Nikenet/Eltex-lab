/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to enable background file operations */
#define ENABLE_BACKGROUND 1

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Define to enable subshell support */
#define ENABLE_SUBSHELL 1

/* Define to enable VFS support */
#define ENABLE_VFS 1

/* Support for cpio filesystem */
#define ENABLE_VFS_CPIO 1

/* Support for extfs */
#define ENABLE_VFS_EXTFS 1

/* Support for FISH vfs */
#define ENABLE_VFS_FISH 1

/* Support for FTP (classic) */
#define ENABLE_VFS_FTP 1

/* Support for sfs */
#define ENABLE_VFS_SFS 1

/* Support for SFTP filesystem */
/* #undef ENABLE_VFS_SFTP */

/* Define to enable VFS over SMB */
/* #undef ENABLE_VFS_SMB */

/* Support for tar filesystem */
#define ENABLE_VFS_TAR 1

/* Support for ext2 undelfs */
/* #undef ENABLE_VFS_UNDELFS */

/* Define if the file command accepts the -L option */
#define FILE_L 1

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <argz.h> header file. */
#define HAVE_ARGZ_H 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to enable aspell support */
/* #undef HAVE_ASPELL */

/* Define to 1 if you have the <aspell.h> header file. */
/* #undef HAVE_ASPELL_H */

/* Define to 1 if you have the `asprintf' function. */
#define HAVE_ASPRINTF 1

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to enable charset selection and conversion */
#define HAVE_CHARSET 1

/* Define to 1 if you have the <curses.h> header file. */
/* #undef HAVE_CURSES_H */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `feof_unlocked', and to 0 if you
   don't. */
#define HAVE_DECL_FEOF_UNLOCKED 1

/* Define to 1 if you have the declaration of `fgets_unlocked', and to 0 if
   you don't. */
#define HAVE_DECL_FGETS_UNLOCKED 1

/* Define to 1 if you have the declaration of `getc_unlocked', and to 0 if you
   don't. */
#define HAVE_DECL_GETC_UNLOCKED 1

/* Define to 1 if you have the declaration of `_snprintf', and to 0 if you
   don't. */
#define HAVE_DECL__SNPRINTF 0

/* Define to 1 if you have the declaration of `_snwprintf', and to 0 if you
   don't. */
#define HAVE_DECL__SNWPRINTF 0

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <dustat.h> header file. */
/* #undef HAVE_DUSTAT_H */

/* Define if ncursesw has ESCDELAY variable */
#define HAVE_ESCDELAY 1

/* Define to 1 if you have the <ext2fs/ext2fs.h> header file. */
/* #undef HAVE_EXT2FS_EXT2FS_H */

/* Define to 1 if you have the <ext2fs/ext2_fs.h> header file. */
/* #undef HAVE_EXT2FS_EXT2_FS_H */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <fs_info.h> header file. */
/* #undef HAVE_FS_INFO_H */

/* Define to 1 if you have the `fs_stat_dev' function. */
/* #undef HAVE_FS_STAT_DEV */

/* Define to 1 if you have the `fwprintf' function. */
#define HAVE_FWPRINTF 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `getegid' function. */
#define HAVE_GETEGID 1

/* Define to 1 if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define to 1 if you have the `getgid' function. */
#define HAVE_GETGID 1

/* Define to 1 if you have the `getmntent' function. */
#define HAVE_GETMNTENT 1

/* Define to 1 if you have the `getmntinfo' function. */
/* #undef HAVE_GETMNTINFO */

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpt' function. */
/* #undef HAVE_GETPT */

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define if you have function `get_process_stats' and have to use that
   instead of gettimeofday */
/* #undef HAVE_GET_PROCESS_STATS */

/* Defined if gmodule functionality is supported */
#define HAVE_GMODULE 1

/* Define to 1 if you have the `grantpt' function. */
#define HAVE_GRANTPT 1

/* Define to 1 if you have the `hasmntopt' function. */
#define HAVE_HASMNTOPT 1

/* Define if you have the iconv() function. */
#define HAVE_ICONV 1

/* Define if the list of mounted filesystems can be determined */
#define HAVE_INFOMOUNT_LIST 1

/* Define if you have the 'intmax_t' type in <stdint.h> or <inttypes.h>. */
#define HAVE_INTMAX_T 1

/* Define if <inttypes.h> exists and doesn't clash with <sys/types.h>. */
#define HAVE_INTTYPES_H 1

/* Define if <inttypes.h> exists, doesn't clash with <sys/types.h>, and
   declares uintmax_t. */
#define HAVE_INTTYPES_H_WITH_UINTMAX 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to enable gpm mouse support on Linux */
/* #undef HAVE_LIBGPM */

/* Define to 1 if you have the `pcre' library (-lpcre). */
/* #undef HAVE_LIBPCRE */

/* Define to 1 if you have the `pt' library (-lpt). */
/* #undef HAVE_LIBPT */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/ext2_fs.h> header file. */
/* #undef HAVE_LINUX_EXT2_FS_H */

/* Define to 1 if you have the `listmntent' function. */
/* #undef HAVE_LISTMNTENT */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define if you have the 'long double' type. */
#define HAVE_LONG_DOUBLE 1

/* Define if you have the 'long long' type. */
#define HAVE_LONG_LONG 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mempcpy' function. */
#define HAVE_MEMPCPY 1

/* Define to 1 if you have a working `mmap' system call. */
/* #undef HAVE_MMAP */

/* Define to 1 if you have the <mntent.h> header file. */
#define HAVE_MNTENT_H 1

/* Define to 1 if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* Define to use ncurses library for screen management */
#define HAVE_NCURSES 1

/* Define to 1 if you have the <ncursesw/curses.h> header file. */
/* #undef HAVE_NCURSESW_CURSES_H */

/* Define to 1 if you have the <ncurses/curses.h> header file. */
/* #undef HAVE_NCURSES_CURSES_H */

/* Define to 1 if you have the <ncurses.h> header file. */
/* #undef HAVE_NCURSES_H */

/* Define to 1 if you have the <ncurses/ncurses.h> header file. */
#define HAVE_NCURSES_NCURSES_H 1

/* Define to 1 if you have the <ncurses/term.h> header file. */
#define HAVE_NCURSES_TERM_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the `next_dev' function. */
/* #undef HAVE_NEXT_DEV */

/* Define to 1 if you have the <nfs/nfs_client.h> header file. */
/* #undef HAVE_NFS_NFS_CLIENT_H */

/* Define to 1 if you have the <nfs/vfs.h> header file. */
/* #undef HAVE_NFS_VFS_H */

/* Define to 1 if you have the <nl_types.h> header file. */
#define HAVE_NL_TYPES_H 1

/* Define to 1 if you have the <OS.h> header file. */
/* #undef HAVE_OS_H */

/* Define to 1 if you have the `pmap_getmaps' function. */
#define HAVE_PMAP_GETMAPS 1

/* Define to 1 if you have the `pmap_getport' function. */
#define HAVE_PMAP_GETPORT 1

/* Define to 1 if you have the `pmap_set' function. */
#define HAVE_PMAP_SET 1

/* Define if you have a working posix_fallocate() */
#define HAVE_POSIX_FALLOCATE 1

/* Define to 1 if you have the `posix_openpt' function. */
#define HAVE_POSIX_OPENPT 1

/* Define if your printf() function supports format strings with positions. */
#define HAVE_POSIX_PRINTF 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if you have the `resizeterm' function. */
#define HAVE_RESIZETERM 1

/* Define to 1 if you have the <rpc/pmap_clnt.h> header file. */
#define HAVE_RPC_PMAP_CLNT_H 1

/* Define to 1 if you have the `rresvport' function. */
#define HAVE_RRESVPORT 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to use S-Lang library for screen management */
/* #undef HAVE_SLANG */

/* Define to use slang.h */
/* #undef HAVE_SLANG_H */

/* Define to use slang.h */
/* #undef HAVE_SLANG_SLANG_H */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the `statlstat' function. */
/* #undef HAVE_STATLSTAT */

/* Define to 1 if you have the `statvfs' function. */
/* #undef HAVE_STATVFS */

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if <stdint.h> exists, doesn't clash with <sys/types.h>, and declares
   uintmax_t. */
#define HAVE_STDINT_H_WITH_UINTMAX 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpcpy' function. */
#define HAVE_STPCPY 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the <stropts.h> header file. */
#define HAVE_STROPTS_H 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if `f_fstypename' is a member of `struct fsstat'. */
/* #undef HAVE_STRUCT_FSSTAT_F_FSTYPENAME */

/* Define to 1 if `l_linger' is a member of `struct linger'. */
#define HAVE_STRUCT_LINGER_L_LINGER 1

/* Define to 1 if `f_frsize' is a member of `struct statfs'. */
#define HAVE_STRUCT_STATFS_F_FRSIZE 1

/* Define to 1 if `f_fstypename' is a member of `struct statfs'. */
/* #undef HAVE_STRUCT_STATFS_F_FSTYPENAME */

/* Define to 1 if `f_namelen' is a member of `struct statfs'. */
#define HAVE_STRUCT_STATFS_F_NAMELEN 1

/* Define to 1 if `f_type' is a member of `struct statfs'. */
#define HAVE_STRUCT_STATFS_F_TYPE 1

/* Define to 1 if `f_basetype' is a member of `struct statvfs'. */
/* #undef HAVE_STRUCT_STATVFS_F_BASETYPE */

/* Define to 1 if `f_fstypename' is a member of `struct statvfs'. */
/* #undef HAVE_STRUCT_STATVFS_F_FSTYPENAME */

/* Define to 1 if `f_namemax' is a member of `struct statvfs'. */
/* #undef HAVE_STRUCT_STATVFS_F_NAMEMAX */

/* Define to 1 if `f_type' is a member of `struct statvfs'. */
/* #undef HAVE_STRUCT_STATVFS_F_TYPE */

/* Define to 1 if `st_blksize' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1

/* Define to 1 if `st_blocks' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_BLOCKS 1

/* Define to 1 if `st_rdev' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_RDEV 1

/* Define to 1 if you have the `strverscmp' function. */
#define HAVE_STRVERSCMP 1

/* Define to 1 if your `struct stat' has `st_blocks'. Deprecated, use
   `HAVE_STRUCT_STAT_ST_BLOCKS' instead. */
#define HAVE_ST_BLOCKS 1

/* Define to 1 if you have the <sys/filsys.h> header file. */
/* #undef HAVE_SYS_FILSYS_H */

/* Define to 1 if you have the <sys/fs/s5param.h> header file. */
/* #undef HAVE_SYS_FS_S5PARAM_H */

/* Define to 1 if you have the <sys/fs_types.h> header file. */
/* #undef HAVE_SYS_FS_TYPES_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/mntent.h> header file. */
/* #undef HAVE_SYS_MNTENT_H */

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/statfs.h> header file. */
#define HAVE_SYS_STATFS_H 1

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#define HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/ucred.h> header file. */
/* #undef HAVE_SYS_UCRED_H */

/* Define to 1 if you have the <sys/vfs.h> header file. */
#define HAVE_SYS_VFS_H 1

/* Define to enable getting events from X Window System */
/* #undef HAVE_TEXTMODE_X11_SUPPORT */

/* Define to 1 if you have the `tsearch' function. */
#define HAVE_TSEARCH 1

/* Define if you have the 'uintmax_t' type in <stdint.h> or <inttypes.h>. */
#define HAVE_UINTMAX_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the 'unsigned long long' type. */
#define HAVE_UNSIGNED_LONG_LONG 1

/* Define to 1 if the system has the type `unsigned long long int'. */
#define HAVE_UNSIGNED_LONG_LONG_INT 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define if you have the 'wchar_t' type. */
#define HAVE_WCHAR_T 1

/* Define to 1 if you have the `wcslen' function. */
#define HAVE_WCSLEN 1

/* Define if you have the 'wint_t' type. */
#define HAVE_WINT_T 1

/* Define to 1 if you have the `__argz_count' function. */
#define HAVE___ARGZ_COUNT 1

/* Define to 1 if you have the `__argz_next' function. */
#define HAVE___ARGZ_NEXT 1

/* Define to 1 if you have the `__argz_stringify' function. */
#define HAVE___ARGZ_STRINGIFY 1

/* Define to 1 if you have the `__fsetlocking' function. */
#define HAVE___FSETLOCKING 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Define if integer division by zero raises signal SIGFPE. */
#define INTDIV0_RAISES_SIGFPE 0

/* Define if compiling for AIX */
/* #undef IS_AIX */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if `major', `minor', and `makedev' are declared in <mkdev.h>.
   */
/* #undef MAJOR_IN_MKDEV */

/* Define to 1 if `major', `minor', and `makedev' are declared in
   <sysmacros.h>. */
/* #undef MAJOR_IN_SYSMACROS */

/* MC configure arguments */
#define MC_CONFIGURE_ARGS " 'CHECK_CFLAGS=-I/tmp/mc_build/builds/build_check-0.10.0/include/' 'CHECK_LIBS=-L/tmp/mc_build/builds/build_check-0.10.0/lib/ -lcheck' 'GLIB_CFLAGS=-I/tmp/mc_build/builds/build_glib-2.44.1/include/glib-2.0 -I/tmp/mc_build/builds/build_glib-2.44.1/lib/glib-2.0/include' 'GLIB_LIBS=-L/tmp/mc_build/builds/build_glib-2.44.1/lib -lglib-2.0' 'GMODULE_CFLAGS=-I/tmp/mc_build/builds/build_glib-2.44.1/include/glib-2.0 -I/tmp/mc_build/builds/build_glib-2.44.1/lib/glib-2.0/include' 'GMODULE_LIBS=-L/tmp/mc_build/builds/build_glib-2.44.1/lib/glib-2.0 -lgmodule-2.0' '--host=arm-linux-gnueabi' '--prefix=/tmp/mc_build/builds/build_mc-4.8.14' '--enable-static=yes' '--with-screen=ncurses' '--with-ncurses-includes=/tmp/mc_build/builds/build_ncurses-5.9/include' '--with-ncurses-libs=/tmp/mc_build/builds/build_ncurses-5.9/lib' 'host_alias=arm-linux-gnueabi' 'CC=arm-linux-gnueabi-gcc' 'CPPFLAGS=-P'"

/* Define to enable XDG standard support */
#define MC_HOMEDIR_XDG 1

/* Where configs will be placed relative to $HOME */
/* #undef MC_USERCONF_DIR */

/* Define if there is no specific function for reading the list of mounted
   file systems. fread will be used to read /etc/mnttab. (SVR2) */
/* #undef MOUNTED_FREAD */

/* Define if (like SVR2) there is no specific function for reading the list of
   mounted file systems, and your system has these header files: <sys/fstyp.h>
   and <sys/statfs.h>. (SVR3) */
/* #undef MOUNTED_FREAD_FSTYP */

/* Define if there are functions named next_dev and fs_stat_dev for reading
   the list of mounted file systems. (BeOS) */
/* #undef MOUNTED_FS_STAT_DEV */

/* Define if there is a function named getfsstat for reading the list of
   mounted file systems. (DEC Alpha running OSF/1) */
/* #undef MOUNTED_GETFSSTAT */

/* Define if there is a function named getmnt for reading the list of mounted
   file systems. (Ultrix) */
/* #undef MOUNTED_GETMNT */

/* Define if there is a function named getmntent for reading the list of
   mounted file systems, and that function takes a single argument. (4.3BSD,
   SunOS, HP-UX, Dynix, Irix) */
#define MOUNTED_GETMNTENT1 1

/* Define if there is a function named getmntent for reading the list of
   mounted file systems, and that function takes two arguments. (SVR4) */
/* #undef MOUNTED_GETMNTENT2 */

/* Define if there is a function named getmntinfo for reading the list of
   mounted file systems and it returns an array of 'struct statfs'. (4.4BSD,
   Darwin) */
/* #undef MOUNTED_GETMNTINFO */

/* Define if there is a function named getmntinfo for reading the list of
   mounted file systems and it returns an array of 'struct statvfs'. (NetBSD
   3.0) */
/* #undef MOUNTED_GETMNTINFO2 */

/* Define if we are on interix, and ought to use statvfs plus some special
   knowledge on where mounted filesystems can be found. (Interix) */
/* #undef MOUNTED_INTERIX_STATVFS */

/* Define if there is a function named listmntent that can be used to list all
   mounted file systems. (UNICOS) */
/* #undef MOUNTED_LISTMNTENT */

/* Define if want to use /proc/self/mountinfo on Linux. */
/* #undef MOUNTED_PROC_MOUNTINFO */

/* Define if there is a function named mntctl that can be used to read the
   list of mounted file systems, and there is a system header file that
   declares 'struct vmount.' (AIX) */
/* #undef MOUNTED_VMOUNT */

/* Define to 1 if assertions should be disabled. */
/* #undef NDEBUG */

/* Name of package */
#define PACKAGE "mc"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define if <inttypes.h> exists and defines unusable PRI* macros. */
/* #undef PRI_MACROS_BROKEN */

/* Define to select 'glib-regexp' search type */
#define SEARCH_TYPE_GLIB 1

/* Define to select 'pcre' search type */
/* #undef SEARCH_TYPE_PCRE */

/* Some systems declare sig_atomic_t as volatile, some others -- no. This
   define will have value `sig_atomic_t' or `volatile sig_atomic_t'
   accordingly. */
#define SIG_ATOMIC_VOLATILE_T volatile sig_atomic_t

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of `off_t', as computed by sizeof. */
#define SIZEOF_OFF_T 8

/* The size of `uintmax_t', as computed by sizeof. */
#define SIZEOF_UINTMAX_T 8

/* Define as the maximum value of type 'size_t', if the system doesn't define
   it. */
/* #undef SIZE_MAX */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define if the block counts reported by statfs may be truncated to 2GB and
   the correct values may be stored in the f_spare array. (SunOS 4.1.2, 4.1.3,
   and 4.1.3_U1 are reported to have this problem. SunOS 4.1.1 seems not to be
   affected.) */
/* #undef STATFS_TRUNCATES_BLOCK_COUNTS */

/* Define if there is no specific function for reading file systems usage
   information and you have the <sys/filsys.h> header file. (SVR2) */
/* #undef STAT_READ_FILSYS */

/* Define if statfs takes 2 args and struct statfs has a field named f_bsize.
   (4.3BSD, SunOS 4, HP-UX, AIX PS/2) */
/* #undef STAT_STATFS2_BSIZE */

/* Define if statfs takes 2 args and struct statfs has a field named f_frsize.
   (glibc/Linux > 2.6) */
/* #undef STAT_STATFS2_FRSIZE */

/* Define if statfs takes 2 args and struct statfs has a field named f_fsize.
   (4.4BSD, NetBSD) */
/* #undef STAT_STATFS2_FSIZE */

/* Define if statfs takes 2 args and the second argument has type struct
   fs_data. (Ultrix) */
/* #undef STAT_STATFS2_FS_DATA */

/* Define if statfs takes 3 args. (DEC Alpha running OSF/1) */
/* #undef STAT_STATFS3_OSF1 */

/* Define if statfs takes 4 args. (SVR3, Dynix, old Irix, old AIX, Dolphin) */
/* #undef STAT_STATFS4 */

/* Define if there is a function named statvfs. (SVR4) */
#define STAT_STATVFS 1

/* Define if statvfs64 should be preferred over statvfs. */
/* #undef STAT_STATVFS64 */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if the f_fsid member of struct statfs is an integer. */
/* #undef STRUCT_STATFS_F_FSID_IS_INTEGER */

/* Define to 1 if the f_fsid member of struct statvfs is an integer. */
/* #undef STRUCT_STATVFS_F_FSID_IS_INTEGER */

/* Define to make subshell support optional */
/* #undef SUBSHELL_OPTIONAL */

/* Define to enable diff viewer */
#define USE_DIFF_VIEW 1

/* Define to enable internal editor */
#define USE_INTERNAL_EDIT 1

/* Use maintainer mode */
/* #undef USE_MAINTAINER_MODE */

/* Define to use ncurses for screen management */
#define USE_NCURSES 1

/* Define to use ncursesw for screen management */
/* #undef USE_NCURSESW */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define to use termcap database */
/* #undef USE_TERMCAP */

/* Version number of package */
#define VERSION "4.8.14"

/* Define to 1 if the X Window System is missing or not being used. */
#define X_DISPLAY_MISSING 1

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#define _FILE_OFFSET_BITS 64

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to ino_t if undefined. */
/* #undef ext2_ino_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to 'unsigned int' if <sys/types.h> does not define. */
/* #undef nlink_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define as the type of the result of subtracting two pointers, if the system
   doesn't define it. */
/* #undef ptrdiff_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef sig_atomic_t */

/* Define to empty if the C compiler doesn't support this keyword. */
/* #undef signed */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to unsigned long or unsigned long long if <stdint.h> and
   <inttypes.h> don't define. */
/* #undef uintmax_t */
