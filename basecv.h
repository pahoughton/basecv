#ifndef _basecv_h_
#define _basecv_h_
/*********************************************************************
 *
 * Title:       basecv.h
 * Project:	basecv
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	05/07/99 06:55
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 * $Id$
 *
 *********************************************************************/

#define PACKAGE	"basecv"
#define VERSION "1.0"
#define STDC_HEADERS	1

/* max base value is number of digits and alpha characters */
#define MAX_BASE         36
#define MAX_BASE_STRING	"36"


struct BasecvParam
{
  char *    inBase;
  char *    outBase;
  char *    number;
  int	    raw;
};

int
process_options( int * argc, char *** argv, struct BasecvParam * param );


#if defined( __cplusplus )
extern "C" {
#endif

#if defined( __cplusplus )
};
#endif

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 1.1  1999/05/07 15:58:46  houghton
 * Initial Version.
 *
 *
 */

#endif /* ! def _basecv_h_ */
