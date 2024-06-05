# 19_Minishell

{
    ignore_readline_leaks
    Memcheck:Leak
    ...
    fun:readline
}
{
    ignore_rl_history_leaks
    Memcheck:Leak
    ...
    fun:add_history
}
{
    ignore_forks_leaks
    Memcheck:Leak
    ...
    fun:fork
}

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
        --track-fds=yes \
         --verbose \
         --keep-debuginfo=yes \
         --suppressions=readline.supp \
         --log-file=valgrind-out.txt \
        ./minishell
