# Entry-parser
A C library to parse a text entry for selecting which type (float or integer) is needed and for rejecting any alphabetic character

Example with GTK :

#include <fsjslib.h>

pWrite_value=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"Write_value"));

// Get entry characters
pcharValueEntry=gtk_entry_get_text(GTK_ENTRY(pWrite_value));		
		
// Parse characters
EntryParser.pcharEntry=pcharValueEntry;
EntryParser.type=typeInteger;
EntryParser.min=0; // min
EntryParser.max=9999; // max
fEntryIsIntOrFloat(&EntryParser);
if (EntryParser.errNumber!=0)
{
	sprintf(pcharMessage,EntryParser.pcharErrMessage);
	fMessage(pcharMessage);
	return;
}
else
{
	sprintf(pcharMessage," ");
	fMessage(pcharMessage);
	RegValue=EntryParser.intResult;
}


For floating data :

EntryParser.type=typeFloat;
EntryParser.min=-DBL_MAX; // min
EntryParser.max=DBL_MAX; // max
..
RegValue=EntryParser.floatResult;
