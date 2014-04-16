/* http://mydomain.com/webservice.php?id=thesecretid&data=012012012012012... */
if( isset($_GET['id']) && isset($_GET['data']) )
{
	/* securely check if the id is valid (using a hidden php script, out of public html or with .htacces restrictions) */

	/* check if data is valid: 600 integers being 0,1 or 2 */
	//...
	
	/* write the file */
	//...
	
}