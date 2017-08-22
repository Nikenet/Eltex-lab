# Don't define aliases in plain Bourne shell
[ -n "${BASH_VERSION}${KSH_VERSION}${ZSH_VERSION}" ] || return 0
alias mc='. /tmp/mc_build/builds/build_mc-4.8.14/libexec/mc/mc-wrapper.sh'
