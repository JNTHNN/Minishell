# 19_Minishell

*Création d'un shell minimaliste - Shell/Bash / Processus / Descripteur de fichier*

## Principe de base

### Plan d'action

1. Réception de la commande
2. Tokenisation
3. Parsing
4. Expand
5. Execution
6. Success / Gestion d'erreur
7. Repeat


<details>
    <summary>Valgrind</summary>
    
### Ignorer les leaks de readline + fork
    
```
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
```

### Commande pour executer Valgrind durant l'utilisation du Minishell + logfile

```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --track-fds=yes \
         --verbose \
         --keep-debuginfo=yes \
         --suppressions=readline.supp \
         --log-file=valgrind-out.txt \
        ./minishell
```

</details>
