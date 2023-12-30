/**
 * free_array - free array memory
 * @arr: buffer
 *
 * Return - nothing
 */
 void free_array(char **arr)
{
	int i;
	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
