large-numbers
=============

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Filename:	LargeNumber.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Provide a memory effecient number system that can hold an infinitly large
 |				    number, and functions that can manipulate it.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		January 6th 2013
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdio.h,	stdlib.h,	inttypes.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 
/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	init_segment
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise function for a segment in a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		value_segment		  The value the head segment will be set to.
 |	@return:	segment_making,		The initialisation was a success.
 |				    NULL,			      	Allocation of memory failed, intialisation unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Subroutine:	free_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  To free all allocated memory used in a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:	  	deleting_largenumber	The large number which will be deleted.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	  init_largenumber
 -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  Initialise function for a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  value_number		The value the number will be set to.
 |	@return:	  largenumber_making	The initialisation was a success.
 |			    	  NULL,				Allocation of memory failed, intialisation unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Subroutine:	fprint_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  Initialise print the contents of a large number to a stream in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  toprint_number,		The large number to be displayed to the given stream.
 |			      	stream,				    Where the number will be displayed to.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Subroutine:	copy_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  Initialise print the contents of a large number to screen in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  tocopy			The number whos values will be copied into another number.
 |	@return:	  copied,			The copied number.
 |				      NULL,			  An error had occured.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Subroutine:	stolargenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:  	Initialise print the contents of a large number to screen in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  number_string		The character representation of the large number.
 |	@return:	  number,				  The characters converted into a large number.
 |			    	  NULL,				    An error had occured.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 === === === === === === === === === === === === === === === === === === === === === === ===
 *  MATH FUNCTIONS FOR LARGE NUMBERS
 === === === === === === === === === === === === === === === === === === === === === === ===
 */

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	add_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Add a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				  The number that will be added to.
 |			    	value_adding,		The value that will be added to the number.
 |	@return:	sum,				    The number of the value and large number added together.
 |			    	0,				    	An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	add_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Add a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number_one,			The first part of the addition.
 |				    number_two,			The second part of the addition.
 |	@return:	sum,				    The value of the two large numbers added.
 |				    NULL,				    An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	sub_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Subtracts a value from a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be minused from.
 |				    value_negate,		The value that will be negated from the large number.
 |	@return:	negated,			The negated value.
 |				    NULL,				  An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	  sub_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:  	Gets the value of a number negated by another negated number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:	  	value_number,		The number that will be minused from.
 |				      value_negate,		The value that will be negated from the large number.
 |	@return:	  negated,			  The negated value.
 |			      	NULL,				    An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	div_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Gets the value of a number negated by another negated number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				  The number that will be minused from.
 |				    value_negate,		The value that will be negated from the large number.
 |	@return:	negated,			  The negated value.
 |				    NULL,				    An error occured whilst adding a segment.
 |			    	0,					    A divide by zero was attempted.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Note:		  This operation has a long runtime. If it is possible to complete it using
 |				    conventional means, it will do it in place.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function: 	multiply_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  Multiplies a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  number,				The number that will be multiplied.
 |				      value_multiplying,	The value that will be multiplied to the number.
 |	@return:  	product,			The value of the large number multiplied by given value.
 |			      	NULL,				  An error occured whilst allocating
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 /*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |  Function:	  multiply_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	  Multiplies two large numbers together.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		  number,				The number that will be multiplied.
 |				      value_multiplying,	The value that will be multiplied to the number.
 |	@return:	  product,			The value of the two numbers multiplied together.
 |				      NULL,				  An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
 
 
