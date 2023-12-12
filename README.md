ALX SIMPLE SHELL PROJECT
collaborators:
>Lewis Mutiso
>Sharon Kawira

Man document
d_typeinfo - struct that has all info that'll help me find builtin commands
search_builtin - looks for a builtin command within the shell or program; function call 
search_cmd - looks for builtin command from user input from predet list in dtypeinfo struct; function call
ret_def - refers to the feedback of computer, if success or fail in finding commands, keeps track using values 0, -1, -2 providing corresponding outputs based on exit status
FLUSH_INDICATOR - tells shell system to handle any pending thing it has without waiting
putoutchar(FLUSH_INDICATOR) - with the putout it means display any information you have to the display asap
getSysInput - this collects new user input
modsys - function call to check if system mode is modified or altered based on info provided in the d_typeinfo struct
memfrinfo - deals with memory mngt, freeing to prevent leaking and manage memory resources, this doesnt mean deleting the command, it just means clearing the resources that were allocated to that process for memry mngt
wrhist - call that enables or saves/store history of user so they scroll and see what they searched for without necessarily reentering the command afresh of course from d_typeinfo struct
status - variable that stores exit status based on whether it is a signal status(non 0 val) or a normal termination(0)
error_no - number that denotes the exit protocol an error follows, tracks errors that occur durinc code execution

Handler Functions - blocks of code that process certain tasks within the entire shell program. my function calls eg search_builtin when it searches and identifies cmd like exit, it calls the exitbin handler func to enable the exit command. A search for builtin cmds is established, eg exit, help, env; when found, a crspndng handler function is called which references to file that execs command.

strtoken file 
the custom function to split a string into tokens; strtok

