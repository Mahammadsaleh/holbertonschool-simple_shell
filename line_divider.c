 /**
 * line_devider - devide the line
 * @buffer: string
 *
 * Return: char ptr to ptr
 */
 char **line_devider(char *buffer, char **arr)
{
	char *token;
	int i = 0;

	token = strtok(buffer, " \n\t");
	while (token != NULL && i < 63)
	{
		arr[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	arr[i++] = NULL;
	return (arr);
}
