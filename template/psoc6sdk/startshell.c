ntshell_t nts_shell;

void nts_task()
{
    printf("Started NT Shell\n");
    setvbuf(stdin, NULL, _IONBF, 0);

    ntshell_init(
	       &nts_shell,
	       ntshell_read,
	       ntshell_write,
	       ntshell_callback,
	       (void *)&nts_shell);
    ntshell_set_prompt(&nts_shell, "AnyCloud $ ");
    vtsend_erase_display(&nts_shell.vtsend);
    ntshell_execute(&nts_shell);
}


xTaskCreate(usrcmd_task, "nt shell task", configMINIMAL_STACK_SIZE*4,0 /* args */ ,0 /* priority */, 0);
